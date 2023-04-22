# Gazebo + ROS Simulation for Rover

This ROS Package is exclusively a simulation and in no way contributes to the robots actual functions. It was intened as a method to begin ROS development tasks while awaiting the actual rover to be constructed. Latency issues running on a VM meant that message passing between nodes was severely impacted and an averaging approach was used to control effectively the rovers motion in the simulated environment. See class presentation slides for more in depth overview of the simulation results and video demo included in this repo.

## To run simulation:

1. To launch Gazebo world for simulation:

Open new terminal and enter command:

`roslaunch luna_rover world.launch`

2. To start rover driving / control:

Open 2nd terminal and enter:

`rosrun luna_rover avoid_obst.py`


### Required libs / pkgs

1. ROS (melodic / noetic used for testing)
2. Gazebo (10 used for testing)
3. rviz
4. Xacro