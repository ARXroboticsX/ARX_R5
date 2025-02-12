#!/bin/bash
source ~/.bashrc
workspace=$(pwd)


gnome-terminal -t "R5" -x  bash -c "cd ${workspace}; cd ROS2/R5_ws; colcon build; exec bash;"

