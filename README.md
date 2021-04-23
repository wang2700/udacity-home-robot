# Home Service Robot
This repository contains the code and launch file to simulate a home service robot which picks up and item from one room to another.

# Dependencies
This project dependes on turtlebot and slam_gmapping to compete the simulation
- [SLAM-Gmapping][slam-link]
- [TurtleBot][tb-link]
- [TurtleBot Interactions][tb-int-link]
- [TurtleBot Simulator][tb-sim-link]

[slam-link]:https://github.com/ros-perception/slam_gmapping
[tb-link]:https://github.com/turtlebot/turtlebot
[tb-int-link]:https://github.com/turtlebot/turtlebot_interactions
[tb-sim-link]:https://github.com/turtlebot/turtlebot_simulation

# Build
- Clone all dependecies into '/home/workspace/catkin_ws/src' directory
- Clone this repository to the same 'src' directory
- Build the package using 'catkin_make' command

# Run the Node
- All the necessary script for launching nodes are in the 'script' folder.

# How it works
In the project, the SLAM-Gmapping package is used to the map and localize the robot within the environment. The ROS Navigation stack is used to generate path of the robot in order to reach the desired goal. The algorithm used to find the path is Dijkstra's algorithm which is a greedy Uniform Cost Search algorithm. The 'pick_objects' package sends goal location for picking up and dropping off the object to the ROS Navigation Stack. The 'add_markers' package subscribe the robot odometry topic to monitor the pose and velocity of the robot in order the deteremine if the gaol location has been reached. When the robot is within 1 meter of the goal and the linear and angular velocity is less than 0.0001 the node will determined that the robots has reach its goal, then the approriate action for marker will be performed.