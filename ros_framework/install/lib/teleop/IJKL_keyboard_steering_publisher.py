#!/usr/bin/env python3

#import needed libraries
import rospy
import time
from std_msgs.msg import Int16, Bool
from getkey import getkey, keys

#ROS node standard form
if __name__ == '__main__':
    #initialize node
    rospy.init_node('IJKL_keyboard_steering_publisher')

    print("-----------------------------------------------------")
    print("----------TELEOP KEYBOARD MANUAL STEERING------------")
    print("-----------------------------------------------------")
    print("----q=QUIT-----ONLY-CLEAN-EXIT-OF-PROGRAM-PLS-USE----")
    print("-----------------------------------------------------")
    print("---i=FWD---m=REV---j=LEFT---l=RIGHT---k=FULL-STOP----")
    print("-u=FWD+LEFT---o=FWD+RIGHT---n=REV+LEFT---,=REV+RIGHT-")
    print("-s=SLOW---f=FAST---d=DPLY---x=MINE---h=HOP---t=STUCK-")
    print("-----------------------------------------------------")
    print("-AFTER-ANY-d/x/h/t-COMMANDS-MUST-PRESS-NON-CODED-KEY-")
    print("-----TO-CLEAR-SENT-COMMAND---c=CLEAR-RECOMMENDED-----")
    print("-----------------------------------------------------")

    #setup publishing topics
    pub_x = rospy.Publisher('x_cmd_velocity', Int16, queue_size = 10)
    pub_theta = rospy.Publisher('theta_cmd_velocity', Int16, queue_size = 10)
    pub_mining = rospy.Publisher('run_mining_state', Bool, queue_size = 10)
    pub_hopper = rospy.Publisher('run_hopper_state', Bool, queue_size = 10)
    pub_servo = rospy.Publisher('run_servo_command', Bool, queue_size = 10)
    #simulated stuck for testing
    pub_stuck = rospy.Publisher('stuck_fault_state', Bool, queue_size = 10)
    
    #set publish rate (Hz)
    rate = rospy.Rate(50)

    #setup variables & initial values for topics to be published
    cmd_velocity = 1
    x = 0
    theta = 0
    mining = False
    hopper = False
    servo = False
    #simulated stuck
    stuck = False

    #keep node running unless CTRL C pressed
    while not rospy.is_shutdown():
        
        #get keypress continuously
        key = getkey()

        #if/else tree to handle all programmed key functions
        
        #FWD command
        if key == 'i':
            x = cmd_velocity
        
        #LEFT command
        elif key == 'j':
            theta = 1
        
        #FULL STOP command
        elif key == 'k':
            x = 0
            theta = 0

        #REV command
        elif key == 'm':
            x = -cmd_velocity

        #RIGHT command
        elif key == 'l':
            theta = -1

        #FWD + LEFT command
        elif key == 'u':
            x = cmd_velocity
            theta = 1

        #FWD + RIGHT command
        elif key == 'o':
            x = cmd_velocity
            theta = -1

        #REV + LEFT command
        elif key == 'n':
            x = -cmd_velocity
            theta = -1

        #REV + RIGHT command
        elif key == ',':
            x = -cmd_velocity
            theta = 1

        #SLOW command - decrements velocity, min = 1
        elif key == 's':
            if cmd_velocity == 1:
                pass
            elif cmd_velocity == 2:
                cmd_velocity = 1
            else:
                cmd_velocity = 2

        #FAST command - increments velocity, max=3
        elif key == 'f':
            if cmd_velocity == 1:
                cmd_velocity = 2
            elif cmd_velocity == 2:
                cmd_velocity = 3
            else:
                pass

        #HOPPER RUN command
        elif key == 'h':
            hopper = True

        #MINING RUN command
        elif key == 'x':
            mining = True
        
        #DEPLOY SERVO command
        elif key == 'd':
            servo = True

        #STUCK simulation command (for testing)
        elif key == 't':
            stuck = True

        #QUIT command - only clean way to shut down!
        elif key == 'q':
            break

        #Any other keypress sets motor commands to OFF
        #Also CLEARS sent HOPPER RUN, MINING RUN, DEPLOY SERVO, STUCK commands
        else:
            x = 0
            theta = 0
            mining = False
            hopper = False
            servo = False
            stuck = False

        #publish all topics        
        pub_x.publish(x)
        pub_theta.publish(theta)
        pub_mining.publish(mining)
        pub_hopper.publish(hopper)
        pub_servo.publish(servo)
        #simulated stuck fault sig
        pub_stuck.publish(stuck)

        rate.sleep()
    
