#!/bin/bash

echo "remap the devices serial port(ttyUSBX) to  rplidar, AHRS, Motordriver"
echo "devices usb connection as /dev/RPLIDAR, /dev/AHRS, /dev/MW  , check it using the command : ls -l /dev|grep ttyUSB"
echo "start copy stella.rules to  /etc/udev/rules.d/"
echo "`rospack find rplidar_ros`/scripts/rplidar.rules"
sudo cp `rospack find stella_bringup`/stella.rules  /etc/udev/rules.d
echo " "
echo "Restarting udev"
echo ""
sudo udevadm trigger
echo "finish "
