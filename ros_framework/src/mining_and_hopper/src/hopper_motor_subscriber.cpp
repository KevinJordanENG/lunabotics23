#include "ros/ros.h"
#include "std_msgs/Int16.h"
#include <iostream>



void run_hopper_motor_callback(const std_msgs::Int16::ConstPtr& msg) {
    ROS_INFO("%d", msg->data);
}

int main(int argc, char **argv){
    
    ros::init(argc, argv, "hopper_motor_subscriber");
    ros::NodeHandle hopper_nh;

    ros::Subscriber hopper_sub = hopper_nh.subscribe("hopper_cmd_signal", 1000, run_hopper_motor_callback);
    
    ros::spin();

    return 0;
}