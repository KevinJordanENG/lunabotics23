#!/usr/bin/env python3

import rospy
from std_msgs.msg import Bool
import Jetson.GPIO as GPIO

STUCK_FAULT_GPIO_PIN = 15

if __name__ == '__main__':
    rospy.init_node('read_stuck_fault_GPIO_publisher')

    pub = rospy.Publisher('stuck_fault_state', Bool, queue_size = 10)

    GPIO.setmode(GPIO.BOARD)
    GPIO.setup(STUCK_FAULT_GPIO_PIN, GPIO.IN, pull_up_down=GPIO.PUD_UP)

    rate = rospy.Rate(10)

    while not rospy.is_shutdown():
        stuck_fault = GPIO.input(STUCK_FAULT_GPIO_PIN)
        pub.publish(stuck_fault)
        rate.sleep()

    GPIO.cleanup()
