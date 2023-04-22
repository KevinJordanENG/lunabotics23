# NASA Lunabotics 2023 - UND Robotics Team RAPTOR

This repository contains all source code for the 2022/2023 NASA Lunabotics
Competition regolith mining robot. The rover used ROS on an NVIDIA Jetson
as the main control unit and an Arduino as a signal processing and over
current/over voltage protector to the Jetson.

Breakdown of all important directories as follows:

1. arduino - scripts used by the Arduino MEGA 2560
2. ros_framework - main system architecture and all functional rover packages
    - src
        1. autonomy - unused due to lack of time
        2. ctre_motors - Port of CTRE API into ROS and VEX motor control code
            - include - needed header files for CTRE API
            - lib - .so files for CTRE API (see notes in README)
            - src - TalonSRX VEX motor control script
        3. drivetrain - drivetrain motor signal handling
            - scripts - intermediary signal/message handling script
        4. launch - launch file starting full/all rover software systems
        5. luna_rover - gazebo simulation work for rover (see notes in README)
        6. mining_and_hopper - extensor, collector, & hopper signal handling
            - scripts - signal handling, GPIO to Arduino, & limit switch scripts
        7. sys_release - servo deployment
            - scripts - servo signal handling between Jetson & Arduino
        8. teleop - Tele-Op remote control
            - scripts - keyboard controller & video feed from ZED
3. testing_src - test scripts not used in rover


## Setup

For those new to ROS, the tutorials do a great job and can be found here:

<wiki.ros.org/ROS/Tutorials>

The NVIDIA Jetson Nano used supported only Ubuntu 18.04 and therefore ROS Melodic was
the only compatible option. Melodic is still built on Python 2 which complicates using any Python 3 libraries. The workaround used was to install catkin (ROS's build system) directly as a Python 3 pakage using pip3 instead of pip (Python 2).

`pip3 install catkin-pkg`

Then, at the top of any .py script using Python 3 libs / pkgs a shebang was added as the first line of the script.

`#!/usr/bin/env python3`

This was the only special environmental setup that was not cleanly documented in any resources found. Hope this saves some serious research hours!

The CTRE Phoenix API was needed for the TalonSRX VEX motor controllers used in the rover. To integrate this into ROS, a porting was done on the C++ source code, headers, and libs. The `ctre_motors` ROS pkg contains the ported API and can be explored for reference to functions. To use the .so files a workaround was used as described in the README in the `/ctre_motors/lib` directory. An example and the source code used as a base for development using the CTRE Phoenix API can be found along with all API documentation here:

<https://github.com/CrossTheRoadElec/Phoenix-Linux-SocketCAN-Example>

<https://v5.docs.ctr-electronics.com/en/latest/index.html>


## Running The Rover

Once basic setup has been done, clone this repo to target controller. 

SSH over to your microcontroller and make sure X forwarding is configured. This will allow the GUI windows from your microcontroller to open for viewing on your control laptop and is necessary for viewing the ZED camera video stream. Info for X forwarding config can be found here:

<https://ostechnix.com/how-to-configure-x11-forwarding-using-ssh-in-linux/>

To make sure ROS is properly installed run the command `roscore` in a new terminal. If a similar output to below is seen congrats! ROS is working properly!

    process[rosout-1]: started with pid [3592]
    started core service [/rosout]

If not, check the tutorials linked above for install / config troubleshooting help.

The full rover software system can be launched simply by the command:

`roslaunch launch teleop.launch`

This should bring up the ZED live video stream and the keyboard contoller in the terminal used to launch. The menu is persistent so don't worry, you'll allwyas be able to see what key does what!

While for practcal use this option is the most elegant, individual process nodes can be run individually using the `rosrun [pkg_name] [node_name]` command. This is especially useful in debugging and testing. Another very useful debugging ROS command is `rostopic echo [msg_name]` which will print the specified message to the terminal screen. A full breakdown of useful ROS commands can be found in the tutorials linked above, however these constitute the core commands needed for most development.