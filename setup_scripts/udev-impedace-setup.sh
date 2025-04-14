# Create the device directory
sudo mkdir -p /dev/docker
sudo chmod 777 /dev/docker

# Create symlinks to the USB devices
sudo ln -sf /dev/ttyUSB0 /dev/docker/u2d2
sudo ln -sf /dev/ttyUSB1 /dev/docker/rft_sensor

# Set latency timers for better performance (if available)
if [ -f "/sys/bus/usb-serial/devices/ttyUSB0/latency_timer" ]; then
    echo "Setting U2D2 latency timer to 1ms"
    sudo sh -c 'echo 1 > /sys/bus/usb-serial/devices/ttyUSB0/latency_timer'
fi

if [ -f "/sys/bus/usb-serial/devices/ttyUSB1/latency_timer" ]; then
    echo "Setting RFT sensor latency timer to 1ms"
    sudo sh -c 'echo 1 > /sys/bus/usb-serial/devices/ttyUSB1/latency_timer'
fi

# Verify device setup
echo "Device setup complete. Current configuration:"
ls -l /dev/docker/