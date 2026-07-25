#!/usr/bin/env python3

import rclpy
from rclpy.node import Node

from std_msgs.msg import Int32
from std_msgs.msg import Float32

import signal_pipeline


class SignalProcessor(Node):

    def __init__(self):
        super().__init__("signal_processor_python")

        # Create filters from C++ bindings
        self.int_filter = signal_pipeline.MovingAverageInt()
        self.float_filter = signal_pipeline.MovingAverageFloat()
        self.lowpass = signal_pipeline.LowPassFilter(2.0)

        # Subscribers
        self.int_sub = self.create_subscription(
            Int32,
            "/signal/int",
            self.int_callback,
            10,
        )

        self.float_sub = self.create_subscription(
            Float32,
            "/signal/float",
            self.float_callback,
            10,
        )

        self.get_logger().info(
            "Python Signal Processor Started"
        )

    def int_callback(self, msg):

        filtered = self.int_filter.update(
            msg.data,
            0.02,
        )

        self.get_logger().info(
            f"INT Raw={msg.data}  Avg={filtered}"
        )

    def float_callback(self, msg):

        average = self.float_filter.update(
            msg.data,
            0.02,
        )

        lowpass = self.lowpass.update(
            average,
            0.02,
        )

        self.get_logger().info(
            f"FLOAT Raw={msg.data:.3f}  "
            f"Avg={average:.3f}  "
            f"LowPass={lowpass:.3f}"
        )


def main(args=None):

    rclpy.init(args=args)

    node = SignalProcessor()

    try:
        rclpy.spin(node)

    except KeyboardInterrupt:
        pass

    finally:
        node.destroy_node()

        if rclpy.ok():
            rclpy.shutdown()


if __name__ == "__main__":
    main()
