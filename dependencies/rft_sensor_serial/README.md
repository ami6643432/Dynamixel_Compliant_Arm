# RFT Sensor Serial Package

This package provides a ROS2 hardware interface for RFT force/torque sensors. It handles serial communication with the sensor using the `RFT_COM` class and streams continuous force/torque data using the `rqst_FT_Continuous` function.

## Prerequisites

- ROS2 installed on your system
- The sensor connected to a serial port (e.g., /dev/ttyUSB0)
- Proper permissions to access the serial port

## Building the Package

1. Navigate to your ROS2 workspace and build

2. ```run rft_sensor_serial rft_sensor_node```