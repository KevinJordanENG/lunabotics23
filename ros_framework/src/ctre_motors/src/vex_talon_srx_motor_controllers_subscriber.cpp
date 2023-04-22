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

//setup needed namespaces for CTRE Phoenix API
using namespace ctre::phoenix;
using namespace ctre::phoenix::platform;
using namespace ctre::phoenix::motorcontrol;
using namespace ctre::phoenix::motorcontrol::can;

//initialize TalonSRX Controller objetcs
std::string interface = "can0";
TalonSRX talFRight(1, interface); //specify interface
TalonSRX talFLeft(2); //front left
TalonSRX talBLeft(3); //back left
TalonSRX talBRight(4); //back right
TalonSRX talExtend(5); //extensor
TalonSRX talCollect(6); //collector
TalonSRX talHopper(7); //hopper

//define class to store command signal input data & function calls to motors
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

//x command signal run motors action function
void command_data::runXCallback(const std_msgs::Int16 &msg1) {
    x_motor_input_cmd = msg1.data;
}

//theta command signal run motors action function
void command_data::runThetaCallback(const std_msgs::Int16 &msg2) {
    theta_motor_input_cmd = msg2.data;
}

//extensor command signal run motors action function
void command_data::runExtendMotorCallback(const std_msgs::Int16 &msg5) {
    extend_motor_input_cmd = msg5.data;
}

//collector command signal run motors action function
void command_data::runCollectMotorCallback(const std_msgs::Int16 &msg6) {
    collect_motor_input_cmd = msg6.data;
}

//hopper command signal run motors action function
void command_data::runHopperMotorCallback(const std_msgs::Int16 &msg7) {
    hopper_motor_input_cmd = msg7.data;
}

//initialize drivetrain with 2 motors directions switched so all drive in same direction
void initDrive() {
	/* both talons should blink green when driving forward */
    talFRight.SetInverted(true);
    talBRight.SetInverted(true);
}

//motor activation main function
void drive(double x, double theta, double extend, double collect, double hopper) {
    //drivetrain motor control combination of x & theta for FWD/REV + turning @ same time
    double right2Motors = - x - theta;
    double left2Motors = - x + theta; /* positive turn means turn robot LEFT */
    //setup controller modes to use %
    talFRight.Set(ControlMode::PercentOutput, right2Motors);
    talFLeft.Set(ControlMode::PercentOutput, left2Motors);
    talBLeft.Set(ControlMode::PercentOutput, left2Motors);
    talBRight.Set(ControlMode::PercentOutput, right2Motors);
    talExtend.Set(ControlMode::PercentOutput, extend);
    talCollect.Set(ControlMode::PercentOutput, collect);
    talHopper.Set(ControlMode::PercentOutput, hopper);
}

/* simple wrapper for code cleanup */
void sleepApp(int ms) {
    std::this_thread::sleep_for(std::chrono::milliseconds(ms));
}

//main motor control
int main(int argc, char **argv){
    //initialize class object and vars
    command_data input_sigs;
    double x = 0.0;
    double theta = 0.0;
    double extend = 0.0;
    double collect = 0.0;
    double hopper = 0.0;

    //setup drive
    initDrive(); 

    //initialize ROS node
    ros::init(argc, argv, "vex_talon_srx_motor_controllers_subscriber");
    ros::NodeHandle nh;
    //set rate (Hz)
    ros::Rate loop_rate(100);

    //setup signal ROS message subscribers
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

    //continue until CTRL C is pressed or other exit
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
            x = 0.15;
        }
        else if (input_sigs.x_motor_input_cmd == 2) {
            std::cout << "FWD-MID\n";
            x = 0.3;
        }
        else if (input_sigs.x_motor_input_cmd == 3) {
            std::cout << "FWD-FAST\n";
            x = 0.5;
        }
        else if (input_sigs.x_motor_input_cmd == -1) {
            std::cout << "REV-SLOW\n";
            x = -0.15;
        }
        else if (input_sigs.x_motor_input_cmd == -2) {
            std::cout << "REV-MID\n";
            x = -0.3;
        }
        else if (input_sigs.x_motor_input_cmd == -3) {
            std::cout << "REV-FAST\n";
            x = -0.5;
        }

        //theta rotation command states
        if (input_sigs.theta_motor_input_cmd == 0) {
            std::cout << "THETA-OFF\n";
            theta = 0;
        }
        else if (input_sigs.theta_motor_input_cmd == 1) {
            std::cout << "LEFT\n";
            theta = 0.3;
        }
        else if (input_sigs.theta_motor_input_cmd == -1) {
            std::cout << "RIGHT\n";
            theta = -0.3;
        }

        //extensor motor states
        if (input_sigs.extend_motor_input_cmd == 0) {
            std::cout << "EXT-OFF\n";
            extend = 0;
        }
        else if (input_sigs.extend_motor_input_cmd == 1) {
            std::cout << "EXT-FWD\n";
            extend = 0.9;
        }
        else if (input_sigs.extend_motor_input_cmd == -1) {
            std::cout << "EXT-REV\n";
            extend = -0.6;
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
        
        //take received motor activationsignals and drive motors as commanded
        drive(x, theta, extend, collect, hopper);
        ctre::phoenix::unmanaged::Unmanaged::FeedEnable(100);
        sleepApp(20);
    }
    //motors OFF if ROS shutdown
	drive(0, 0, 0, 0, 0);
    return 0;
}