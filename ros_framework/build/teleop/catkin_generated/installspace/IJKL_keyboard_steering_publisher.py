#!/usr/bin/env python3

#import needed libraries
import rospy
import time
from std_msgs.msg import Int16
from getkey import getkey, keys

#ROS node standard form
if __name__ == '__main__':
    #initialize node
    rospy.init_node('IJKL_keyboard_steering_publisher')

    print("-----------------------------------------------------")
    print("----------TELEOP KEYBOARD MANUAL STEERING------------")
    print("------i=FWD---m=REV---j=LEFT---l=RIGHT---k=STOP------")
    print("-u=FWD+LEFT---o=FWD+RIGHT---n=REV+LEFT---,=REV+RIGHT-")
    print("-------------s=SLOW---f=FAST---q=QUIT----------------")
    print("-----------------------------------------------------")

    pub_x = rospy.Publisher('x_cmd_velocity', Int16, queue_size = 10)
    pub_theta = rospy.Publisher('theta_cmd_velocity', Int16, queue_size = 10)

    rate = rospy.Rate(50)

    cmd_velocity = 1
    x = 0
    theta = 0

    
    while not rospy.is_shutdown():

        key = getkey()

        if key == 'i':
            x = cmd_velocity
            #print(x)
        
        elif key == 'j':
            theta = 1
            #print(theta)
        
        elif key == 'k':
            x = 0
            theta = 0
            #print(x, theta)

        elif key == 'm':
            x = -cmd_velocity
            #print(x)

        elif key == 'l':
            theta = -1
            #print(theta)

        elif key == 'u':
            x = cmd_velocity
            theta = 1
            #print(x, theta)

        elif key == 'o':
            x = cmd_velocity
            theta = -1
            #print(x, theta)

        elif key == 'n':
            x = -cmd_velocity
            theta = -1
            print(x, theta)

        elif key == ',':
            x = -cmd_velocity
            theta = 1
            #print(x, theta)

        elif key == 's':
            if cmd_velocity == 1:
                pass
            elif cmd_velocity == 2:
                cmd_velocity = 1
            else:
                cmd_velocity = 2
            #print(cmd_velocity)

        elif key == 'f':
            if cmd_velocity == 1:
                cmd_velocity = 2
            elif cmd_velocity == 2:
                cmd_velocity = 3
            else:
                pass
            #print(cmd_velocity)

        elif key == 'q':
            break

        else:
            x = 0
            theta = 0
            #print("press valid key")
        pub_x.publish(x)
        pub_theta.publish(theta)

        rate.sleep()
    
