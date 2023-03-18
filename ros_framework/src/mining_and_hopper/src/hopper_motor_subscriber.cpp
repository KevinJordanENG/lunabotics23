#include "ros/ros.h"
#include "std_msgs/Int16.h"
#include <iostream>

class command_data {
public:
    int hopper_motor_input_cmd = 0;
    void runHopperMotorCallback(const std_msgs::Int16 &msg);
};

void command_data::runHopperMotorCallback(const std_msgs::Int16 &msg) {
    hopper_motor_input_cmd = msg.data;
}

int main(int argc, char **argv){
    
    command_data input_sig;

    ros::init(argc, argv, "hopper_motor_subscriber");
    ros::NodeHandle hopper_nh;
    ros::Rate loop_rate(50);
    ros::Subscriber hopper_sub = 
        hopper_nh.subscribe("hopper_cmd_signal", 1000, &command_data::runHopperMotorCallback, &input_sig);

    while (ros::ok()) {
        ros::spinOnce();
        loop_rate.sleep();
        std::cout << input_sig.hopper_motor_input_cmd;
        std::cout << "\n";
    }

    return 0;
}