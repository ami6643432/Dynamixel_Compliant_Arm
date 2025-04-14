#!/bin/bash

# Function to set USB latency timer
set_usb_latency() {
    echo "Optimizing USB latency timer..."
    sudo sh -c 'echo 1 > /sys/bus/usb-serial/devices/ttyUSB1/latency_timer'
    # Verify latency timer setting
    latency=$(cat /sys/bus/usb-serial/devices/ttyUSB1/latency_timer)
    echo "USB Latency Timer set to: $latency ms"
}

# Function to set CPU affinity for USB interrupts
set_cpu_affinity() {
    echo "Optimizing CPU affinity for USB interrupts..."
    irq_number=$(cat /proc/interrupts | grep -i usb | head -n 1 | awk '{print $1}' | sed 's/://')
    if [ -n "$irq_number" ]; then
        sudo sh -c "echo 1 > /proc/irq/$irq_number/smp_affinity_list"
        echo "CPU affinity set for IRQ $irq_number to CPU core 0."
    else
        echo "Unable to find USB IRQ for CPU affinity optimization."
    fi
}

# Perform USB optimizations
set_usb_latency
set_cpu_affinity

# Source the ROS2 workspace
echo "Sourcing ROS2 workspace..."
source /ros2_ws/install/setup.bash

# Run the rft_sensor_serial node in the background
echo "Starting RFT sensor node..."
ros2 run rft_sensor_serial rft_sensor_serial_node --ros-args -p RFT_COM_PORT:="/dev/ttyUSB1" &
NODE_PID=$!

# Function to stop the service and clean up
cleanup() {
    echo "Stopping the RFT service and cleaning up..."
    if ps -p $NODE_PID > /dev/null; then
        ros2 service call /rft_serial_op_service rft_sensor_serial/srv/RftOperation "{op_type: 12, param1: 0, param2: 0, param3: 0}" || echo "Service call failed."
        kill $NODE_PID
    fi
    echo "Exiting script..."
    exit 1
}


# Set trap to catch termination signals and run cleanup
trap cleanup SIGINT SIGTERM

# Wait for the node to initialize
sleep 2

# Timeout for service readiness
MAX_RETRIES=10
RETRY_COUNT=0

while ! ros2 service list | grep -q "/rft_serial_op_service"; do
    echo "Waiting for /rft_serial_op_service to become available... (Retry $RETRY_COUNT)"
    sleep 1
    RETRY_COUNT=$((RETRY_COUNT + 1))
    if [ $RETRY_COUNT -ge $MAX_RETRIES ]; then
        echo "Service /rft_serial_op_service not available after $MAX_RETRIES retries. Exiting..."
        cleanup
    fi
done


# Start communication
echo "Starting communication..."
if ! ros2 service call /rft_serial_op_service rft_sensor_serial/srv/RftOperation "{op_type: 11, param1: 0, param2: 0, param3: 0}"; then
    echo "Failed to start communication. Exiting..."
    cleanup
fi

# # Set Bias
# echo "Starting communication..."
# if ! ros2 service call /rft_serial_op_service rft_sensor_serial/srv/RftOperation "{op_type: 17, param1: 0, param2: 0, param3: 0}"; then
#     echo "Failed to set bias. Exiting..."
#     cleanup
# fi

# Echo the topic in a separate background process
echo "Echoing /RFT_FORCE topic..."
ros2 topic echo /RFT_FORCE

# # # Checking the communication frequency in another background process
# echo "Checking topic frequency for /RFT_FORCE..."
# ros2 topic hz /RFT_FORCE

# Wait indefinitely until the script is terminated
wait $NODE_PID
