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

using namespace ctre::phoenix;
using namespace ctre::phoenix::platform;
using namespace ctre::phoenix::motorcontrol;
using namespace ctre::phoenix::motorcontrol::can;

std::string interface = "can0";
TalonSRX talFRight(1, interface); //specify interface
TalonSRX talFLeft(2); //front left
TalonSRX talBLeft(3); //back left
TalonSRX talBRight(4); //back right
TalonSRX talCollect(6); //collector
TalonSRX talExtend(5); //extensor
TalonSRX talHopper(7); //hopper

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
    theta_motor_input_cmd = msg2.data;
}

void initDrive()
{
	/* both talons should blink green when driving forward */
	talFRight.SetInverted(true);
	talBRight.SetInverted(true);
}

void drive(double fwd, double turn, double buckets, double screw, double belt)
{
	double rght = - fwd - turn;
	double left = - fwd + turn; /* positive turn means turn robot LEFT */

	talFLeft.Set(ControlMode::PercentOutput, left);
	talFRight.Set(ControlMode::PercentOutput, fwd);
	talBLeft.Set(ControlMode::PercentOutput, left);
	talBRight.Set(ControlMode::PercentOutput, rght);
	talCollect.Set(ControlMode::PercentOutput, buckets);
	talExtend.Set(ControlMode::PercentOutput, screw);
	talHopper.Set(ControlMode::PercentOutput, belt);
}

/** simple wrapper for code cleanup */
void sleepApp(int ms)
{
	std::this_thread::sleep_for(std::chrono::milliseconds(ms));
}

int main(int argc, char **argv){
    
    command_data input_sigs;
    double rght = 0.0;

    ros::init(argc, argv, "FRight_motor_subscriber");
    ros::NodeHandle FRight_nh;
    ros::Rate loop_rate(50);
    ros::Subscriber x_sub = 
        FRight_nh.subscribe("x_motor_input_cmd", 1000, &command_data::runFRightMotorXCallback, &input_sigs);
    ros::Subscriber theta_sub = 
        FRight_nh.subscribe("theta_cmd_velocity", 1000, &command_data::runFRightMotorThetaCallback, &input_sigs);

    while (ros::ok()) {
        
        drive(0, 0, 0, 0, 0);

        ros::spinOnce();


        if (input_sigs.x_motor_input_cmd == 0) {
            std::cout << "OFF\n";
            rght = 0;
        }
        else if (input_sigs.x_motor_input_cmd == 1) {
            std::cout << "SLOW\n";
            rght = 0.05;
        }
        else if (input_sigs.x_motor_input_cmd == 2) {
            std::cout << "MID\n";
            rght = 0.15;
        }
        else if (input_sigs.x_motor_input_cmd == 3) {
            std::cout << "FAST\n";
            rght = 0.25;
        }
        else if (input_sigs.x_motor_input_cmd == -1) {
            std::cout << "SLOW\n";
            rght = -0.05;
        }
        else if (input_sigs.x_motor_input_cmd == -2) {
            std::cout << "MID\n";
            rght = -0.15;
        }
        else if (input_sigs.x_motor_input_cmd == -3) {
            std::cout << "FAST\n";
            rght = -0.25;
        }

        drive(rght, 0, 0, 0, 0);
        ctre::phoenix::unmanaged::Unmanaged::FeedEnable(100);
        sleepApp(20);
        /*
        if (input_sigs.x_motor_input_cmd == 0) {
            std::cout << "OFF\n";
        }
        else if (input_sigs.x_motor_input_cmd == 1) {
            std::cout << "FWD\n";
        }
        else if (input_sigs.x_motor_input_cmd == -1) {
            std::cout << "REV\n";
        }
        else {
            std::cout << "OFF\n";
        }
        */
    }

    return 0;
}