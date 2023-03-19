//Phoenix & Talon SRX includes
#define Phoenix_No_WPI
#include "drivetrain/Phoenix.h"
#include "drivetrain/phoenix/platform/Platform.h"
#include "drivetrain/phoenix/unmanaged/Unmanaged.h"
#include "drivetrain/phoenix/cci/Unmanaged_CCI.h"

//ROS includes
#include "ros/ros.h"
#include "std_msgs/Int16.h"

//sys includes
#include <string>
#include <iostream>
#include <chrono>
#include <thread>
#include <unistd.h>

class command_data {
public:
    int x_motor_input_cmd = 0;
    int theta_motor_input_cmd = 0;
    void runFRightMotorXCallback(const std_msgs::Int16 &msg1);
    void runFRightMotorThetaCallback(const std_msgs::Int16 &msg2);
};

void command_data::runFRightMotorXCallback(const std_msgs::Int16 &msg1) {
    x_motor_input_cmd = msg1.data;
}

void command_data::runFRightMotorThetaCallback(const std_msgs::Int16 &msg2) {
    x_motor_input_cmd = msg2.data;
}

int main(int argc, char **argv){
    
    command_data input_sigs;

    ros::init(argc, argv, "FRight_motor_subscriber");
    ros::NodeHandle hopper_nh;
    ros::Rate loop_rate(50);
    ros::Subscriber hopper_sub = 
        hopper_nh.subscribe("x_cmd_velocity", 1000, &command_data::runFRightMotorXCallback, &input_sig);
    ros::Subscriber hopper_sub = 
        hopper_nh.subscribe("theta_cmd_velocity", 1000, &command_data::runFRightMotorThetaCallback, &input_sig);

    while (ros::ok()) {
        ros::spinOnce();
        loop_rate.sleep();
        std::cout << input_sigs.x_motor_input_cmd;
        std::cout << " ";
        std::cout << input_sigs.theta_motor_input_cmd;
        std::cout << "\n";
        /*
        if (input_sigs.hopper_motor_input_cmd == 0) {
            std::cout << "OFF\n";
        }
        else if (input_sigs.hopper_motor_input_cmd == 1) {
            std::cout << "FWD\n";
        }
        else if (input_sigs.hopper_motor_input_cmd == -1) {
            std::cout << "REV\n";
        }
        else {
            std::cout << "OFF\n";
        }
        */
    }

    return 0;
}