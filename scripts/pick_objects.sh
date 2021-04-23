#!/bin/sh
cd /home/workspace/catkin_ws
xterm -e " source devel/setup.bash && export TURTLEBOT_GAZEBO_WORLD_FILE="/home/workspace/catkin_ws/src/map_my_world/worlds/myworld.world" && roslaunch turtlebot_gazebo turtlebot_world.launch " &
sleep 15
xterm -e " export TURTLEBOT_GAZEBO_MAP_FILE="/home/workspace/catkin_ws/src/maps/map.yaml" && roslaunch turtlebot_gazebo amcl_demo.launch " &
sleep 15
xterm -e " roslaunch turtlebot_rviz_launchers view_navigation.launch " &
sleep 15
xterm -e " roslaunch pick_objects pick_object.launch " &