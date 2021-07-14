#!/bin/bash

echo "delete remap the devices serial port(ttyUSBX) to  rplidar, AHRS, Motordriver"
echo "sudo rm   /etc/udev/rules.d/stella.rules"
sudo rm   /etc/udev/rules.d/stella.rules
echo " "
echo "Restarting udev"
echo ""
sudo udevadm trigger
echo "finish  delete"
