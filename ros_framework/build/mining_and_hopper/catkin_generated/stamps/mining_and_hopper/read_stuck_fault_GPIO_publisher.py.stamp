#!/usr/bin/env python3

#import needed libraries
import rospy
from std_msgs.msg import Bool
import Jetson.GPIO as GPIO

#define pin on Jetson (using BOARD pin numbering)
STUCK_FAULT_GPIO_PIN = 15

#ROS node standard form
if __name__ == '__main__':
    #initialize node
    rospy.init_node('read_stuck_fault_GPIO_publisher')
    #setup publishing variable and message for other nodes in ROS framework
    pub = rospy.Publisher('stuck_fault_state', Bool, queue_size = 10)
    #setup pin for GPIO
    GPIO.setmode(GPIO.BOARD)
    GPIO.setup(STUCK_FAULT_GPIO_PIN, GPIO.IN)
    #set message publishing rate (Hz)
    rate = rospy.Rate(50)
    #keep node running unless CTRL C pressed
    while not rospy.is_shutdown():
        #read GPIO pin for stuck-fault signal from arduino
        stuck_fault = GPIO.input(STUCK_FAULT_GPIO_PIN)
        #publish message to ROS framework
        pub.publish(stuck_fault)
        #wait for specified publish rate
        rate.sleep()
    #cleanup GPIO pin
    GPIO.cleanup()
