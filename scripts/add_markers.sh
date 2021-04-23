#!/bin/sh
cd /home/workspace/catkin_ws
xterm -e " source devel/setup.bash && export TURTLEBOT_GAZEBO_WORLD_FILE="/home/workspace/catkin_ws/src/map_my_world/worlds/myworld.world" && roslaunch turtlebot_gazebo turtlebot_world.launch " &
sleep 15
xterm -e " export TURTLEBOT_GAZEBO_MAP_FILE="/home/workspace/catkin_ws/src/maps/map.yaml" && roslaunch turtlebot_gazebo amcl_demo.launch " &
sleep 15
xterm -e " rosrun rviz rviz -d "/home/workspace/catkin_ws/src/rvizConfig/navigation.rviz" " &
sleep 5
xterm -e " roslaunch add_markers marker_simulation.launch " &