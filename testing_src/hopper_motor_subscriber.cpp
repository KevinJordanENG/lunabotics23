//Phoenix & Talon SRX includes
#define Phoenix_No_WPI
#include "mining_and_hopper/Phoenix.h"
#include "mining_and_hopper/phoenix/platform/Platform.h"
#include "mining_and_hopper/phoenix/unmanaged/Unmanaged.h"
#include "mining_and_hopper/phoenix/cci/Unmanaged_CCI.h"

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

/* make some talons for drive train */
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
    int hopper_motor_input_cmd = 0;
    void runHopperMotorCallback(const std_msgs::Int16 &msg);
};

void command_data::runHopperMotorCallback(const std_msgs::Int16 &msg) {
    hopper_motor_input_cmd = msg.data;
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
	talFRight.Set(ControlMode::PercentOutput, rght);
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
    
    command_data input_sig;
    double belt = 0.0;

    /* setup drive */
	initDrive(); 

    ros::init(argc, argv, "hopper_motor_subscriber");
    ros::NodeHandle hopper_nh;
    ros::Rate loop_rate(50);
    ros::Subscriber hopper_sub = 
        hopper_nh.subscribe("hopper_cmd_signal", 1000, &command_data::runHopperMotorCallback, &input_sig);

    while (ros::ok()) {

        //motors OFF while waiting for command
		drive(0, 0, 0, 0, 0);

        ros::spinOnce();
        
        if (input_sig.hopper_motor_input_cmd == 0) {
            std::cout << "OFF\n";
            belt = 0;
        }
        else if (input_sig.hopper_motor_input_cmd == 1) {
            std::cout << "FWD\n";
            belt = 0.75;
        }
        else if (input_sig.hopper_motor_input_cmd == -1) {
            std::cout << "REV\n";
            belt = -0.75;
        }

        drive(0, 0, 0, 0, belt);
        ctre::phoenix::unmanaged::Unmanaged::FeedEnable(100);
        sleepApp(20);
    }
    //motors OFF if ROS shutdown
	drive(0, 0, 0, 0, 0);
    return 0;
}