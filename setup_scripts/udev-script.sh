#!/bin/bash

# Exit on error
set -e

# Define the vendor and product IDs
U2D2_VENDOR_ID="0403"
U2D2_PRODUCT_ID="6014"
RFT_VENDOR_ID="0403"  # Updated to match your FTDI device
RFT_PRODUCT_ID="6015"  # Updated to match your FTDI device

# Define the latency timer value (1ms for better performance)
LATENCY_TIMER_VALUE="1"

# Define paths
RULES_PATH="/etc/udev/rules.d/99-u2d2.rules"
DOCKER_DEV_PATH="/dev/docker"

# Check if running with sudo
if [ "$EUID" -ne 0 ]; then 
    echo "Please run as root or with sudo"
    exit 1
fi

# Create docker device directory if it doesn't exist
if [ ! -d "$DOCKER_DEV_PATH" ]; then
    mkdir -p "$DOCKER_DEV_PATH"
    chmod 777 "$DOCKER_DEV_PATH"
fi

# Define the udev rules
cat << EOF > "$RULES_PATH"
# U2D2 device symlink rule (specific serial)
SUBSYSTEM=="tty", ATTRS{idVendor}=="$U2D2_VENDOR_ID", ATTRS{idProduct}=="$U2D2_PRODUCT_ID", MODE="0666", GROUP="dialout", SYMLINK+="docker/u2d2"

# RFT Force/Torque Sensor (try both /dev/docker and regular /dev paths)
SUBSYSTEM=="tty", ATTRS{idVendor}=="$RFT_VENDOR_ID", ATTRS{idProduct}=="$RFT_PRODUCT_ID", MODE="0666", GROUP="dialout", SYMLINK+="docker/rft_sensor", SYMLINK+="rft_sensor"

# Additional rule to ensure RFT sensor is first USB device
KERNEL=="ttyUSB*", ATTRS{idVendor}=="$RFT_VENDOR_ID", ATTRS{idProduct}=="$RFT_PRODUCT_ID", ATTRS{bcdDevice}=="0600", SYMLINK+="docker/rft_sensor", SYMLINK+="rft_sensor"

# U2D2 latency timer rule
ACTION=="add", SUBSYSTEM=="tty", ATTRS{idVendor}=="$U2D2_VENDOR_ID", ATTRS{idProduct}=="$U2D2_PRODUCT_ID", RUN+="/bin/sh -c 'echo $LATENCY_TIMER_VALUE > /sys\$env{DEVPATH}/device/latency_timer'"

# Set latency timer for RFT sensor as well
ACTION=="add", SUBSYSTEM=="tty", ATTRS{idVendor}=="$RFT_VENDOR_ID", ATTRS{idProduct}=="$RFT_PRODUCT_ID", RUN+="/bin/sh -c 'echo $LATENCY_TIMER_VALUE > /sys\$env{DEVPATH}/device/latency_timer'"

# Additional permissions for USB devices
SUBSYSTEM=="usb", ATTRS{idVendor}=="$U2D2_VENDOR_ID", ATTRS{idProduct}=="$U2D2_PRODUCT_ID", MODE="0666", GROUP="dialout"
SUBSYSTEM=="usb", ATTRS{idVendor}=="$RFT_VENDOR_ID", ATTRS{idProduct}=="$RFT_PRODUCT_ID", MODE="0666", GROUP="dialout"
EOF

# Ensure correct permissions on the rules file
chmod 644 "$RULES_PATH"

# Reload udev rules
udevadm control --reload-rules
udevadm trigger

# Check if dialout group exists and create if it doesn't
getent group dialout > /dev/null || groupadd dialout

# Add current user to dialout group if they aren't already in it
CURRENT_USER=$(who am i | awk '{print $1}')
if [ ! -z "$CURRENT_USER" ]; then
    usermod -a -G dialout "$CURRENT_USER"
    echo "Added user $CURRENT_USER to dialout group"
fi

echo "Udev rules have been updated successfully!"
echo "Please disconnect and reconnect your U2D2 and RFT sensor devices"
echo "Note: You may need to log out and back in for group changes to take effect"

# Verify the rules file exists and show device info
if [ -f "$RULES_PATH" ]; then
    echo "Rules file created successfully at $RULES_PATH"
    echo "Current USB devices:"
    lsusb | grep -E "$U2D2_VENDOR_ID|$RFT_VENDOR_ID"
    echo -e "\nCurrent tty devices:"
    ls -l /dev/ttyUSB*
    echo -e "\nCurrent symlinks:"
    ls -l /dev/docker/* 2>/dev/null || echo "No symlinks created yet"
else
    echo "Error: Rules file creation failed"
    exit 1
fi

# Get detailed device attributes for debugging
echo -e "\nDetailed device information:"
for device in $(ls /sys/bus/usb/devices/*/idVendor 2>/dev/null); do
    dir=$(dirname $device)
    vendor=$(cat $dir/idVendor 2>/dev/null || echo "unknown")
    product=$(cat $dir/idProduct 2>/dev/null || echo "unknown")
    if [ "$vendor" = "$RFT_VENDOR_ID" ] || [ "$vendor" = "$U2D2_VENDOR_ID" ]; then
        echo "Device in $dir:"
        echo "  Vendor ID: $vendor"
        echo "  Product ID: $product"
        echo "  Serial: $(cat $dir/serial 2>/dev/null || echo "unknown")"
        echo "  Manufacturer: $(cat $dir/manufacturer 2>/dev/null || echo "unknown")"
        echo "  Product: $(cat $dir/product 2>/dev/null || echo "unknown")"
    fi
done
