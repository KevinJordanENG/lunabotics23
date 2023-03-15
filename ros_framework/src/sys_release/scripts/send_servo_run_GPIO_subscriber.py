#!/usr/bin/env python3

#import needed libraries
import rospy
from std_msgs.msg import Bool
import Jetson.GPIO as GPIO

#define pin on Jetson (using BOARD pin numbering)
SERVO_RUN_GPIO_PIN = 11

#create function to output to GPIO pin based on received command signal
def run_servo_command_callback(msg):
    GPIO.output(SERVO_RUN_GPIO_PIN, msg.data)

#ROS node standard form
if __name__ == '__main__':
    #initialize node
    rospy.init_node('send_servo_run_GPIO_subscriber')
    #setup pin for GPIO
    GPIO.setmode(GPIO.BOARD)
    GPIO.setup(SERVO_RUN_GPIO_PIN, GPIO.OUT)
    #setup subscribing to run servo command message
    rospy.Subscriber('run_servo_command', Bool, run_servo_command_callback)
    #keep node running unless CTRL C pressed
    rospy.spin()
    #cleanup GPIO pin
    GPIO.cleanup()