# Robotous_FT_RFT60

**Steps to interface RFT60-HA01 sensor to a ROS2 node.**

## Method 1 Local setup

1. **setting up the ros2_ws**:
   ```bash
   mkdir -p /ros2_ws/src
   cd /ros2_ws/src
   ```
2. **Clone the Repo and take the rft_sensor_serial package and move it to /ros2_ws/src**
   ```
   git clone git@github.com:RRC-Control-Lab/rocon_arm_impedance.git
   ```
3. **Build the WS and source**
   ```
   source /ros2_ws/install/setup.bash
   ```
4. **Run the Setup Script**
   ```
   cd /ros2_ws/src/rft_sensor_serial
   chmod +x ft_launch.sh
   ./ft_launch.sh
   ```

## Method 2 Container

1. **Clone the Repo**
   ```
   git clone git@github.com:RRC-Control-Lab/rocon_arm_impedance.git
   ```
2. **Open VSCode and build the container:**
   Press "ctrl+shift+p" and select build and reopen in container
3. **Build the workspace:**
   Import Libs and Build WS
4. **Run the Setup Script**
   ```
   cd /ros2_ws/src/rft_sensor_serial
   chmod +x ft_launch.sh
   ./ft_launch.sh
   ```