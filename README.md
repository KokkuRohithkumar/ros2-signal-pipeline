# ROS 2 Signal Processing Pipeline

A modular signal processing pipeline built using **ROS 2 Jazzy**, **C++17**, **Python**, and **pybind11**. The project demonstrates real-time signal acquisition, digital signal processing (DSP), Python bindings for C++ filters, and communication between ROS 2 nodes.

---

## Project Overview

This project implements a complete signal processing pipeline consisting of:

- A ROS 2 publisher that generates or replays sensor signals.
- A standalone C++ DSP library.
- Python bindings using pybind11.
- A C++ processing node.
- A Python processing node.
- Validation using synthetic and replay modes.

The project is designed to demonstrate reusable software architecture, modular programming, and interoperability between C++ and Python in ROS 2.

---

## Features

### Signal Publisher

- Synthetic signal generation
- Replay mode using CSV data
- Configurable Gaussian noise
- Configurable signal jitter
- Packet drop simulation
- Publishes Integer and Float topics

### Standalone DSP Library (C++)

Implemented using templates where appropriate.

Available filters:

- Moving Average Filter
- Median Filter
- Low Pass Filter
- Ring Buffer
- Q15 Fixed-Point Support

### Python Bindings

Implemented using **pybind11**.

Exposes the complete C++ filtering library to Python.

Available Python classes:

- MovingAverageFloat
- MovingAverageInt
- MedianFilterFloat
- MedianFilterInt
- LowPassFilter
- LowPassFilterQ15

### ROS 2 Processing Nodes

#### C++ Processor

- Subscribes to signal topics
- Applies DSP filters
- Prints processed output

#### Python Processor

- Uses pybind11 bindings
- Runs identical filtering in Python
- Demonstrates C++/Python interoperability

---

# Project Structure

```
signal_pipeline_ws
│
├── src
│   └── signal_pipeline
│       ├── standalone_library
│       ├── python_bindings
│       ├── ros_publisher
│       ├── ros_cpp_processor
│       ├── ros_python_processor
│       ├── report
│       ├── script
│       └── sensor_log.csv
│
├── build
├── install
├── log
└── README.md
```

---

# Technologies Used

- ROS 2 Jazzy
- C++17
- Python 3
- pybind11
- CMake
- Colcon
- NumPy
- CSV Data Processing

---

# Build Instructions

## Clone Repository

```bash
git clone https://github.com/<your-username>/signal_pipeline.git

cd signal_pipeline
```

---

## Build Workspace

```bash
cd ~/signal_pipeline_ws

source /opt/ros/jazzy/setup.bash

colcon build
```

---

## Source Workspace

```bash
source install/setup.bash
```

---

# Running the Project

## Terminal 1

Start Publisher

Synthetic Mode

```bash
ros2 run signal_publisher publisher_node --mode synthetic
```

Replay Mode

```bash
ros2 run signal_publisher publisher_node --mode replay
```

---

## Terminal 2

Run C++ Processor

```bash
ros2 run signal_processor_cpp signal_processor_cpp
```

---

## Terminal 3

Run Python Processor

```bash
ros2 run signal_processor_python processor_node
```

---

# Validation

The project supports validation using:

- Synthetic signal generation
- Replay mode
- Gaussian noise
- Jitter simulation
- Packet drop simulation
- Cross-verification between C++ and Python filters

---

# Example ROS Topics

Published Topics

```
/signal/int
/signal/float
```

Useful ROS Commands

```bash
ros2 topic list

ros2 node list

ros2 topic echo /signal/int

ros2 topic echo /signal/float

ros2 topic hz /signal/int
```

---

# Python Binding Test

```bash
cd python_bindings

python3 test_bindings.py
```

---

# Future Improvements

- FFT analysis
- Frequency-domain filtering
- Dynamic ROS parameters
- Launch files
- Unit testing
- Performance benchmarking
- Visualization using PlotJuggler or rqt_plot

---

# Learning Outcomes

This project demonstrates:

- Modern C++ programming
- Template programming
- Digital Signal Processing
- ROS 2 communication
- pybind11 integration
- Cross-language interoperability
- Software modularity
- Real-time data processing

---

# Author

**Kokku Rohith Kumar**

B.Tech – Electronics and Communication Engineering

Embedded Systems | ROS 2 | C++ | Python | Digital Signal Processing

GitHub:
https://github.com/KokkuRohithkumar

LinkedIn:
(Add your LinkedIn profile URL here)

---

# License

This project was developed for educational and assessment purposes.
