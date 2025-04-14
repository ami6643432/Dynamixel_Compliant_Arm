# Check if running as Administrator
if (-NOT ([Security.Principal.WindowsPrincipal][Security.Principal.WindowsIdentity]::GetCurrent()).IsInRole([Security.Principal.WindowsBuiltInRole]::Administrator)) {
    Write-Warning "Please run as Administrator!"
    exit
}

Write-Host "Setting up robot devices for Docker/WSL2..." -ForegroundColor Green

# Verify usbipd is installed
try {
    $usbipd = Get-Command usbipd
    Write-Host "Found usbipd: $($usbipd.Path)" -ForegroundColor Green
} catch {
    Write-Host "Error: usbipd not found. Please install it with: winget install dorssel.usbipd-win" -ForegroundColor Red
    exit
}

# List all USB devices to identify our targets
Write-Host "`nCurrent USB devices:" -ForegroundColor Cyan
usbipd list

# U2D2 and RFT sensor details from your usbipd output
$U2D2_BUSID = "1-1"    # VID:PID 0403:6014 USB Serial Converter
$RFT_BUSID = "1-3"     # VID:PID 0403:6015 USB Serial Converter

# Bind devices for WSL sharing
Write-Host "`nBinding U2D2 controller (BUSID: $U2D2_BUSID)..." -ForegroundColor Yellow
usbipd bind --busid $U2D2_BUSID
Write-Host "Binding RFT sensor (BUSID: $RFT_BUSID)..." -ForegroundColor Yellow
usbipd bind --busid $RFT_BUSID

# Attach devices to WSL
Write-Host "`nAttaching U2D2 controller to WSL..." -ForegroundColor Yellow
usbipd attach --busid $U2D2_BUSID --wsl
Write-Host "Attaching RFT sensor to WSL..." -ForegroundColor Yellow
usbipd attach --busid $RFT_BUSID --wsl

# Create script to run inside Docker container to set up symlinks and latency
$deviceSetupScript = @"
#!/bin/bash

# Create Docker device directory
sudo mkdir -p /dev/docker
sudo chmod 777 /dev/docker

# Create symlinks (adjust ttyUSB numbers if needed)
sudo ln -sf /dev/ttyUSB0 /dev/docker/u2d2
sudo ln -sf /dev/ttyUSB1 /dev/docker/rft_sensor

# Set latency timers for better performance
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
echo "Current latency settings:"
cat /sys/bus/usb-serial/devices/ttyUSB0/latency_timer 2>/dev/null || echo "U2D2 latency timer not available"
cat /sys/bus/usb-serial/devices/ttyUSB1/latency_timer 2>/dev/null || echo "RFT sensor latency timer not available"
"@

# Save the script directly inside Docker container
$scriptPath = "$PWD/device-setup.sh"
$deviceSetupScript | Out-File -FilePath $scriptPath -Encoding utf8 -Force

# Create instructions for user
Write-Host "`nAll devices attached to WSL." -ForegroundColor Green
Write-Host "A setup script has been created at: $scriptPath" -ForegroundColor Green
Write-Host "`nTo use the devices with Docker, you need to:" -ForegroundColor Cyan
Write-Host "1. Copy the script into your Docker container:" -ForegroundColor Yellow
Write-Host "   docker cp $scriptPath rocon_arm_impedance_development:/tmp/device-setup.sh" -ForegroundColor White
Write-Host "2. Make it executable and run it:" -ForegroundColor Yellow
Write-Host "   docker exec -it rocon_arm_impedance_development bash -c 'chmod +x /tmp/device-setup.sh && /tmp/device-setup.sh'" -ForegroundColor White
Write-Host "`nAfter setting up the devices, you can run the impedance controller with:" -ForegroundColor Green
Write-Host "ros2 launch robot_bringup arm_2r.launch.py use_impedance:=true" -ForegroundColor Yellow