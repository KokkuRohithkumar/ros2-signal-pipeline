#!/usr/bin/env python3

import math
import random
import time
import csv
import argparse

import rclpy
from rclpy.node import Node

from std_msgs.msg import Int32, Float32


class SignalPublisher(Node):

    def __init__(self, mode, jitter=0.0, drop_rate=0.0):
        super().__init__("signal_publisher")

        self.mode = mode
        self.jitter = jitter
        self.drop_rate = drop_rate

        # Publishers
        self.int_pub = self.create_publisher(Int32, "/signal/int", 10)
        self.float_pub = self.create_publisher(Float32, "/signal/float", 10)

        # Synthetic mode
        self.start_time = time.time()

        # Replay mode
        self.data = []
        self.index = 0

        if self.mode == "replay":
            self.load_csv()

        # 50 Hz timer
        if self.mode == "synthetic":
            self.timer = self.create_timer(0.02, self.publish_signal)
        else:
            self.timer = self.create_timer(0.02, self.publish_replay)

        self.get_logger().info(
            f"Running in {self.mode} mode | "
            f"Jitter={self.jitter}s | "
            f"Drop Rate={self.drop_rate}"
        )

    def load_csv(self):

        csv_path = "/home/kokkurohithkumar/signal_pipeline_ws/src/signal_pipeline/sensor_log.csv"

        try:
            with open(csv_path, "r") as file:
                reader = csv.DictReader(file)

                for row in reader:
                    self.data.append(row)

            self.get_logger().info(
                f"Loaded {len(self.data)} samples from CSV."
            )

        except FileNotFoundError:
            self.get_logger().error(f"CSV file not found: {csv_path}")

    def apply_drop_rate(self):

        if random.random() < self.drop_rate:
            self.get_logger().info("Message dropped")
            return True

        return False

    def apply_jitter(self):

        if self.jitter > 0.0:
            time.sleep(random.uniform(0.0, self.jitter))

    def publish_signal(self):

        if self.apply_drop_rate():
            return

        t = time.time() - self.start_time

        signal = (
            math.sin(2.0 * math.pi * 0.5 * t)
            + 0.5 * math.sin(2.0 * math.pi * 2.0 * t)
            + 0.25 * math.sin(2.0 * math.pi * 5.0 * t)
        )

        signal += random.gauss(0.0, 0.10)

        float_msg = Float32()
        int_msg = Int32()

        float_msg.data = float(signal)
        int_msg.data = int(signal * 100)

        self.apply_jitter()

        self.float_pub.publish(float_msg)
        self.int_pub.publish(int_msg)

        self.get_logger().info(
            f"[Synthetic] Float={float_msg.data:.3f}  Int={int_msg.data}"
        )

    def publish_replay(self):

        if len(self.data) == 0:
            return

        if self.apply_drop_rate():
            return

        if self.index >= len(self.data):
            self.index = 0

        row = self.data[self.index]

        float_msg = Float32()
        int_msg = Int32()

        float_msg.data = float(row["accel_x_mss"])
        int_msg.data = int(row["encoder_count"])

        self.apply_jitter()

        self.float_pub.publish(float_msg)
        self.int_pub.publish(int_msg)

        self.get_logger().info(
            f"[Replay] Float={float_msg.data:.3f}  Int={int_msg.data}"
        )

        self.index += 1


def main(args=None):

    parser = argparse.ArgumentParser()

    parser.add_argument(
        "--mode",
        default="synthetic",
        choices=["synthetic", "replay"],
        help="Publishing mode"
    )

    parser.add_argument(
        "--jitter",
        type=float,
        default=0.0,
        help="Maximum timing jitter in seconds"
    )

    parser.add_argument(
        "--drop-rate",
        type=float,
        default=0.0,
        help="Probability of dropping a message (0.0 - 1.0)"
    )

    parsed_args, ros_args = parser.parse_known_args()

    rclpy.init(args=ros_args)

    node = SignalPublisher(
        mode=parsed_args.mode,
        jitter=parsed_args.jitter,
        drop_rate=parsed_args.drop_rate
    )

    try:
        rclpy.spin(node)

    except KeyboardInterrupt:
        node.get_logger().info("Stopping Signal Publisher...")

    finally:
        node.destroy_node()

        if rclpy.ok():
            rclpy.shutdown()


if __name__ == "__main__":
    main()
