#!/usr/bin/env python3

#script acts as intermediary signal processor converting periodic command signals
#from keyboard controller into continuous messages understood by ROS message system

#import needed libraries
import rospy
import time
from std_msgs.msg import Bool, Int16


class sys_deploy_sub:
    #class level variable accessable in main program node
    gpio_output = Int16()
    #object initialize as subscriber
    def __init__(self):
        self.sys_deploy_subscriber = rospy.Subscriber('run_servo_key', Int16, self.run_servo_command_callback)
    #callback function assigning msg recieved to class level varibale
    def run_servo_command_callback(self, msg):
        self.gpio_output.data = msg.data

class sys_deploy_pub:
    #object initialize as publisher and pass command args from main program node
    def __init__(self, sys_deploy = False):
        self.sys_deploy = sys_deploy
        #setup ROS publishing & publish passed command args
        self.pub_run_servo = rospy.Publisher('run_servo_command', Bool, queue_size = 20)
        self.pub_run_servo.publish(self.sys_deploy)

#ROS node standard form
if __name__ == '__main__':
    #initialize node
    rospy.init_node('run_servo_intermediary')
    #publish rate (Hz)
    rate = rospy.Rate(100)

    #keep node running unless CTRL C pressed
    while not rospy.is_shutdown():
        #initialize subscriber
        sys_dep = sys_deploy_sub()
        

        if sys_dep.gpio_output.data == 0:
            #set timer to run hopper for (x)s
            timer1 = time.time() + 0.01
            while time.time() < timer1:
                #publish servo command signal to GPIO handler
                sys_deploy_pub(False)
                rate.sleep()
        
        if sys_dep.gpio_output.data == 1:
            #set timer to run hopper for (x)s
            timer2 = time.time() + 0.01
            while time.time() < timer2:
                #publish servo command signal to GPIO handler
                sys_deploy_pub(True)
                rate.sleep()

        rate.sleep()