#!/bin/sh
cd /home/workspace/catkin_ws
xterm -e " source devel/setup.bash && export TURTLEBOT_GAZEBO_WORLD_FILE="/home/workspace/catkin_ws/src/map_my_world/worlds/myworld.world" && roslaunch turtlebot_gazebo turtlebot_world.launch " &
sleep 10
xterm -e " roslaunch turtlebot_gazebo gmapping_demo.launch " &
sleep 10
xterm -e " roslaunch turtlebot_rviz_launchers view_navigation.launch " &
sleep 10
xterm -e " roslaunch turtlebot_teleop keyboard_teleop.launch "