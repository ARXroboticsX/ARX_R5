#!/bin/bash
source ~/.bashrc
workspace=$(pwd)

# CAN
gnome-terminal -t "can1" -x bash -c "cd ${workspace}/ARX_CAN/arx_can; ./arx_can1.sh; exec bash;"
# R5
gnome-terminal -t "R5" -x  bash -c "cd ${workspace}; cd ROS2/R5_ws; source install/setup.bash && ros2 launch arx_r5_controller open_single_arm.launch.py; exec bash;"
gnome-terminal -t "R5" -x  bash -c "cd ${workspace}; cd ROS2/R5_ws; source install/setup.bash && rqt; exec bash;"

