#!/usr/bin/env python3

from __future__ import print_function

import rospy
from geometry_msgs.msg import Twist

def stop(cmd_msg):
    cmd_msg.linear.x = 0
    cmd_msg.linear.y = 0
    cmd_msg.linear.z = 0
    cmd_msg.angular.x = 0
    cmd_msg.angular.y = 0
    cmd_msg.angular.z = 0

def turn_left(cmd_msg):
    cmd_msg.linear.x = 0
    cmd_msg.angular.z = 1

def turn_right(cmd_msg):
    cmd_msg.linear.x = 0
    cmd_msg.angular.z = -1

def forward(cmd_msg):
    cmd_msg.linear.x = 0.5
    cmd_msg.angular.z = 0

def backward(cmd_msg):
    cmd_msg.linear.x = -0.5
    cmd_msg.angular.z = 0

def move_control():
    pub = rospy.Publisher('/cmd_vel', Twist, queue_size=1)
    rospy.init_node('move_control', anonymous=True)
    rate = rospy.Rate(4)

    cmd_msg = Twist()
    stop(cmd_msg)

    cycle_cntr = 0

    while not rospy.is_shutdown():
        if cycle_cntr < 40:
            turn_left(cmd_msg)
            if cycle_cntr == 4:
                print("WARNING! Proximity")
            pub.publish(cmd_msg)
        elif 40 <= cycle_cntr < 52:
            stop(cmd_msg)
            if cycle_cntr == 40:
                print("warning_cleared")
            pub.publish(cmd_msg)
        elif 52 <= cycle_cntr < 68:
            forward(cmd_msg)
            if cycle_cntr == 64:
                print("WARNING! Proximity")
            pub.publish(cmd_msg)
        elif 68 <= cycle_cntr < 80:
            stop(cmd_msg)
            pub.publish(cmd_msg)
        elif 80 <= cycle_cntr < 112:
            turn_right(cmd_msg)
            pub.publish(cmd_msg)
        elif 112 <= cycle_cntr < 124:
            stop(cmd_msg)
            if cycle_cntr == 116:
                print("warning_cleared")
            pub.publish(cmd_msg)
        elif 124 <= cycle_cntr < 148:
            forward(cmd_msg)
            pub.publish(cmd_msg)
        elif 148 <= cycle_cntr < 160:
            stop(cmd_msg)
            pub.publish(cmd_msg)
        elif 160 <= cycle_cntr < 280:
            turn_left(cmd_msg)
            pub.publish(cmd_msg)
        elif 280 <= cycle_cntr < 292:
            stop(cmd_msg)
            pub.publish(cmd_msg)
        elif 292 <= cycle_cntr < 316:
            forward(cmd_msg)
            pub.publish(cmd_msg)
        elif 316 <= cycle_cntr < 328:
            stop(cmd_msg)
            pub.publish(cmd_msg)
        elif 328 <= cycle_cntr < 360:
            turn_left(cmd_msg)
            pub.publish(cmd_msg)
        elif 360 <= cycle_cntr < 372:
            stop(cmd_msg)
            pub.publish(cmd_msg)
        elif 372 <= cycle_cntr < 388:
            forward(cmd_msg)
            pub.publish(cmd_msg)
        elif 388 <= cycle_cntr < 1024:
            stop(cmd_msg)
            pub.publish(cmd_msg)
        else:
            cycle_cntr = 0
        cycle_cntr = cycle_cntr + 1
        rate.sleep()


if __name__ == '__main__':
    try:
        move_control()
    except rospy.ROSInterruptException:
        pass