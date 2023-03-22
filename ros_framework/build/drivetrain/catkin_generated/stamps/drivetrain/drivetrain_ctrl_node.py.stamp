#!/usr/bin/env python3

#import needed libraries
import rospy
import time
from std_msgs.msg import Int16, Bool


#class object for easier main node flow programming: keboard x command message ROS subscriber
class x_cmd_sub:
    #class level variable accessable in main program node
    x_cmd_flag = Int16()
    #object initialize as subscriber
    def __init__(self):
        self.x_cmd_subscriber = rospy.Subscriber('x_cmd_code', Int16, self.x_cmd_flag_callback)
    #callback function assigning msg recieved to class level varibale
    def x_cmd_flag_callback(self, msg):
        self.x_cmd_flag.data = msg.data


#class object for easier main node flow programming: keyboard theta command message ROS subscriber
class theta_cmd_sub:
    #class level variable accessable in main program node
    theta_cmd_flag = Int16()
    #object initialize as subscriber
    def __init__(self):
        self.theta_cmd_subscriber = rospy.Subscriber('theta_cmd_code', Bool, self.theta_cmd_flag_callback)
    #callback function assigning msg recieved to class level varibale
    def theta_cmd_flag_callback(self, msg):
        self.theta_cmd_flag.data = msg.data

#class object for easier main node flow programming: x control message to talons ROS publisher
class x_motors_pub:
    #object initialize as publisher and pass command args from main program node
    def __init__(self, x = 0):
        self.x = x
        #setup ROS publishing & publish passed command args
        self.pub_x_cmd_vel = rospy.Publisher('x_cmd_velocity', Int16, queue_size = 10)
        self.pub_x_cmd_vel.publish(self.x)

#class object for easier main node flow programming: theta control message to talons ROS publisher
class theta_motors_pub:
    #object initialize as publisher and pass command args from main program node
    def __init__(self, theta = 0):
        self.theta = theta
        #setup ROS publishing & publish passed command args
        self.pub_theta_cmd_vel = rospy.Publisher('theta_cmd_velocity', Int16, queue_size = 10)
        self.pub_theta_cmd_vel.publish(self.theta)


if __name__ == '__main__':
    #initialize node
    rospy.init_node('drivetrain_ctrl_node')
    #publish rate (Hz)
    rate = rospy.Rate(50)
    #null val for motor signals on startup / while waiting for execution
    non_cycle_null_val = 0

    #keep node running unless CTRL C pressed
    while not rospy.is_shutdown():
        #initialize subscribers
        x_cmd = x_cmd_sub()
        theta_cmd = theta_cmd_sub()

        
        #if 0 x command received X=OFF
        if x_cmd.x_cmd_flag.data == 0:
            #set timer to run for 1s
            timer1 = time.time() + 1
            while time.time() < timer1:
                #publish x command to motors node
                x_motors_pub(0)
                print("X=OFF")
                rate.sleep()

        #if 1 x command received X=FWD-SLOW
        if x_cmd.x_cmd_flag.data == 1:
            #set timer to run for 1s
            timer2 = time.time() + 1
            while time.time() < timer2:
                #publish x command to motors node
                x_motors_pub(1)
                print("X=FWD-SLOW")
                rate.sleep()

        #if 2 x command received X=FWD-MID
        if x_cmd.x_cmd_flag.data == 2:
            #set timer to run for 1s
            timer3 = time.time() + 1
            while time.time() < timer3:
                #publish x command to motors node
                x_motors_pub(2)
                print("X=FWD-MID")
                rate.sleep()

        #if 3 x command received X=FWD-FAST
        if x_cmd.x_cmd_flag.data == 3:
            #set timer to run for 1s
            timer4 = time.time() + 1
            while time.time() < timer4:
                #publish x command to motors node
                x_motors_pub(3)
                print("X=FWD-FAST")
                rate.sleep()

        #if -3 x command received X=REV-FAST
        if x_cmd.x_cmd_flag.data == -3:
            #set timer to run for 1s
            timer5 = time.time() + 1
            while time.time() < timer5:
                #publish x command to motors node
                x_motors_pub(-3)
                print("X=REV-FAST")
                rate.sleep()

        #if -2 x command received X=REV-MID
        if x_cmd.x_cmd_flag.data == -2:
            #set timer to run for 1s
            timer6 = time.time() + 1
            while time.time() < timer6:
                #publish x command to motors node
                x_motors_pub(-2)
                print("X=REV-MID")
                rate.sleep()

        #if -1 x command received X=REV-SLOW
        if x_cmd.x_cmd_flag.data == -1:
            #set timer to run for 1s
            timer7 = time.time() + 1
            while time.time() < timer7:
                #publish x command to motors node
                x_motors_pub(-1)
                print("X=REV-SLOW")
                rate.sleep()

        #if 0 theta command received THETA=OFF
        if theta_cmd.theta_cmd_flag.data == 0:
            #set timer to run for 1s
            timer8 = time.time() + 1
            while time.time() < timer8:
                #publish theta command to motors node
                theta_motors_pub(0)
                print("THETA=OFF")
                rate.sleep()

        #if 1 theta command received THETA=LEFT
        if theta_cmd.theta_cmd_flag.data == 1:
            #set timer to run for 1s
            timer9 = time.time() + 1
            while time.time() < timer9:
                #publish theta command to motors node
                theta_motors_pub(1)
                print("THETA=LEFT")
                rate.sleep()

        #if -1 theta command received THETA=RIGHT
        if theta_cmd.theta_cmd_flag.data == -1:
            #set timer to run for 1s
            timer10 = time.time() + 1
            while time.time() < timer10:
                #publish theta command to motors node
                theta_motors_pub(-1)
                print("THETA=RIGHT")
                rate.sleep()

        #when not actively receiving driving commands publish OFF commands to motors
        x_motors_pub(non_cycle_null_val)
        theta_motors_pub(non_cycle_null_val)

        rate.sleep()