//Phoenix & Talon SRX includes
#define Phoenix_No_WPI
#include "ctre_motors/Phoenix.h"
#include "ctre_motors/phoenix/platform/Platform.h"
#include "ctre_motors/phoenix/unmanaged/Unmanaged.h"
#include "ctre_motors/phoenix/cci/Unmanaged_CCI.h"

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
TalonSRX talExtend(5); //extensor
TalonSRX talCollect(6); //collector
TalonSRX talHopper(7); //hopper

class command_data {
public:
    int x_motor_input_cmd = 0;
    int theta_motor_input_cmd = 0;
    int extend_motor_input_cmd = 0;
    int collect_motor_input_cmd = 0;
    int hopper_motor_input_cmd = 0;
    void runXCallback(const std_msgs::Int16 &msg1);
    void runThetaCallback(const std_msgs::Int16 &msg2);
    void runExtendMotorCallback(const std_msgs::Int16 &msg5);
    void runCollectMotorCallback(const std_msgs::Int16 &msg6);
    void runHopperMotorCallback(const std_msgs::Int16 &msg7);
};

void command_data::runXCallback(const std_msgs::Int16 &msg1) {
    x_motor_input_cmd = msg1.data;
}

void command_data::runThetaCallback(const std_msgs::Int16 &msg2) {
    theta_motor_input_cmd = msg2.data;
}

void command_data::runExtendMotorCallback(const std_msgs::Int16 &msg5) {
    extend_motor_input_cmd = msg5.data;
}

void command_data::runCollectMotorCallback(const std_msgs::Int16 &msg6) {
    collect_motor_input_cmd = msg6.data;
}

void command_data::runHopperMotorCallback(const std_msgs::Int16 &msg7) {
    hopper_motor_input_cmd = msg7.data;
}

void initDrive()
{
	/* both talons should blink green when driving forward */
	talFRight.SetInverted(true);
	talBRight.SetInverted(true);
}

void drive(double x, double theta, double extend, double collect, double hopper)
{
	
    //FIXME-FIXME-FIXME-----NEED TO ADD TURNING MATH HERE------FIXME-FIXME-FIXME
    double right2Motors = - x - theta;
	double left2Motors = - x + theta; /* positive turn means turn robot LEFT */

	talFRight.Set(ControlMode::PercentOutput, right2Motors);
    talFLeft.Set(ControlMode::PercentOutput, left2Motors);
	talBLeft.Set(ControlMode::PercentOutput, left2Motors);
	talBRight.Set(ControlMode::PercentOutput, right2Motors);
    talExtend.Set(ControlMode::PercentOutput, extend);
	talCollect.Set(ControlMode::PercentOutput, collect);
	talHopper.Set(ControlMode::PercentOutput, hopper);
}

/** simple wrapper for code cleanup */
void sleepApp(int ms)
{
	std::this_thread::sleep_for(std::chrono::milliseconds(ms));
}

int main(int argc, char **argv){
    
    command_data input_sigs;
    double x = 0.0;
    double theta = 0.0;
    double extend = 0.0;
    double collect = 0.0;
    double hopper = 0.0;

    /* setup drive */
	initDrive(); 

    ros::init(argc, argv, "vex_talon_srx_motor_controllers_subscriber");
    ros::NodeHandle nh;
    ros::Rate loop_rate(100);

    ros::Subscriber x_sub = 
        nh.subscribe("x_cmd_velocity", 1000, &command_data::runXCallback, &input_sigs);
    ros::Subscriber theta_sub = 
        nh.subscribe("theta_cmd_velocity", 1000, &command_data::runThetaCallback, &input_sigs);
    ros::Subscriber extend_sub = 
        nh.subscribe("extensor_cmd_signal", 1000, &command_data::runExtendMotorCallback, &input_sigs);
    ros::Subscriber collect_sub = 
        nh.subscribe("collector_cmd_signal", 1000, &command_data::runCollectMotorCallback, &input_sigs);
    ros::Subscriber hopper_sub = 
        nh.subscribe("hopper_cmd_signal", 1000, &command_data::runHopperMotorCallback, &input_sigs);

    while (ros::ok()) {

        //motors OFF while waiting for command
		drive(0, 0, 0, 0, 0);

        ros::spinOnce();

        //x translation command states
        if (input_sigs.x_motor_input_cmd == 0) {
            std::cout << "OFF\n";
            x = 0;
        }
        else if (input_sigs.x_motor_input_cmd == 1) {
            std::cout << "FWD-SLOW\n";
            x = 0.10;
        }
        else if (input_sigs.x_motor_input_cmd == 2) {
            std::cout << "FWD-MID\n";
            x = 0.20;
        }
        else if (input_sigs.x_motor_input_cmd == 3) {
            std::cout << "FWD-FAST\n";
            x = 0.25;
        }
        else if (input_sigs.x_motor_input_cmd == -1) {
            std::cout << "REV-SLOW\n";
            x = -0.10;
        }
        else if (input_sigs.x_motor_input_cmd == -2) {
            std::cout << "REV-MID\n";
            x = -0.20;
        }
        else if (input_sigs.x_motor_input_cmd == -3) {
            std::cout << "REV-FAST\n";
            x = -0.25;
        }

        //theta rotation command states
        if (input_sigs.theta_motor_input_cmd == 0) {
            std::cout << "THETA-OFF\n";
            theta = 0;
        }
        else if (input_sigs.theta_motor_input_cmd == 1) {
            std::cout << "LEFT\n";
            theta = 0.10;
        }
        else if (input_sigs.theta_motor_input_cmd == -1) {
            std::cout << "RIGHT\n";
            theta = -0.10;
        }

        //extensor motor states
        if (input_sigs.extend_motor_input_cmd == 0) {
            std::cout << "EXT-OFF\n";
            extend = 0;
        }
        else if (input_sigs.extend_motor_input_cmd == 1) {
            std::cout << "EXT-FWD\n";
            extend = 0.6;
        }
        else if (input_sigs.extend_motor_input_cmd == -1) {
            std::cout << "EXT-REV\n";
            extend = -0.9;
        }

        //collector motor states
        if (input_sigs.collect_motor_input_cmd == 0) {
            std::cout << "COL-OFF\n";
            collect = 0;
        }
        else if (input_sigs.collect_motor_input_cmd == 1) {
            std::cout << "COL-FWD\n";
            collect = 0.5;
        }
        else if (input_sigs.collect_motor_input_cmd == -1) {
            std::cout << "COL-REV\n";
            collect = -0.5;
        }

        //hopper motor states
        if (input_sigs.hopper_motor_input_cmd == 0) {
            std::cout << "HOP-OFF\n";
            hopper = 0;
        }
        else if (input_sigs.hopper_motor_input_cmd == 1) {
            std::cout << "HOP-FWD\n";
            hopper = 0.9;
        }
        else if (input_sigs.hopper_motor_input_cmd == -1) {
            std::cout << "HOP-REV\n";
            hopper = -0.9;
        }
        
        drive(x, theta, extend, collect, hopper);
        ctre::phoenix::unmanaged::Unmanaged::FeedEnable(100);
        sleepApp(20);
    }
    //motors OFF if ROS shutdown
	drive(0, 0, 0, 0, 0);
    return 0;
}