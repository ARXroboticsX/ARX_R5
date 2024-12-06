#!/bin/bash
source ~/.bashrc
gnome-terminal -t "can" -x bash -c "source ~/.bashrc;source /opt/ros/noetic/setup.bash; sudo -S slcand -o -f -s8 /dev/arxcan0 can0;sudo ifconfig can0 up;exec bash;"
sleep 1

gnome-terminal -t "can" -x bash -c "source ~/.bashrc;source /opt/ros/noetic/setup.bash; sudo -S slcand -o -f -s8 /dev/arxcan0 can0;sudo ifconfig can0 up;exec bash;"
sleep 1
gnome-terminal -t "can" -x bash -c "source ~/.bashrc;source /opt/ros/noetic/setup.bash; sudo -S slcand -o -f -s8 /dev/arxcan1 can1;sudo ifconfig can1 up;exec bash;"
sleep 1
gnome-terminal -t "can" -x bash -c "source ~/.bashrc;source /opt/ros/noetic/setup.bash; sudo -S slcand -o -f -s8 /dev/arxcan2 can2;sudo ifconfig can2 up;exec bash;"
sleep 1
gnome-terminal -t "can" -x bash -c "source ~/.bashrc;source /opt/ros/noetic/setup.bash; sudo -S slcand -o -f -s8 /dev/arxcan3 can3;sudo ifconfig can3 up;exec bash;"










