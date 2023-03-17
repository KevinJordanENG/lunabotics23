#!/usr/bin/env python3

#import needed libraries
import rospy
import os
from getkey import getkey, keys

#ROS node standard form
if __name__ == '__main__':
    #initialize node
    rospy.init_node('IJKL_keyboard_steering_publisher')

    rate = rospy.Rate(50)

    key = getkey()
    while not rospy.is_shutdown():

        if key == 'i':
            print("FWD")
        
        elif key == 'j':
            print("LEFT")
        
        elif key == 'k':
            print("REV")

        elif key == 'l':
            print("RIGHT")

        elif key == 'u':
            print("FWD + LEFT")

        elif key == 'o':
            print("FWD + RIGHT")

        elif key == 'n':
            print("REV + LEFT")

        elif key == ',':
            print("REV + RIGHT")

        elif key == 's':
            print("VEL--")

        elif key == 'f':
            print("VEL++")

        elif key == 'q':
            break
            #rospy.signal_shutdown()

        else:
            print("press valid key")
        
        key = getkey()
        rate.sleep()
    
