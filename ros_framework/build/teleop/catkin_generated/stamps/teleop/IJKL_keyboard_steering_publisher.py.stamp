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
    print("-d=SERVO---s=SLOW---f=FAST---h=HOP-FWD---y=HOP-REV---")
    print("-------e=EXT---r=RTCT---x=COLL-FWD---z=COLL-REV------")
    print("-----------------------------------------------------")
    print("-AFTER-ANY-COMMAND-SENT-MUST-PRESS-ANY-NON-CODED-KEY-")
    print("-----TO-CLEAR-SENT-COMMAND---c=CLEAR-RECOMMENDED-----")
    print("-----------------------------------------------------")

    #setup publishing topics
    pub_x = rospy.Publisher('x_cmd_code', Int16, queue_size = 20)
    pub_theta = rospy.Publisher('theta_cmd_code', Int16, queue_size = 20)
    pub_extensor = rospy.Publisher('run_extensor_state', Int16, queue_size = 20)
    pub_collector = rospy.Publisher('run_collector_state', Int16, queue_size = 20)
    pub_hopper = rospy.Publisher('run_hopper_state', Int16, queue_size = 20)
    pub_servo = rospy.Publisher('run_servo_key', Int16, queue_size = 20)
    #simulated stuck for testing
    #pub_stuck = rospy.Publisher('stuck_fault_state', Bool, queue_size = 20)
    
    #set publish rate (Hz)
    rate = rospy.Rate(100)

    #setup variables & initial values for topics to be published
    cmd_velocity = 1
    x = 0
    theta = 0
    extend = 0
    collect = 0
    hopper = 0
    servo = 0
    #simulated stuck
    #stuck = False

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

        #HOPPER FWD command
        elif key == 'h':
            hopper = 1

        #Hopper REV command
        elif key == 'y':
            hopper = -1

        #EXTEND command
        elif key == 'e':
            extend = 1

        #RETRACT command
        elif key == 'r':
            extend = -1

        #BUCKETS FWD command
        elif key == 'x':
            collect = 1

        #BUCKETS REV command
        elif key == 'z':
            collect = -1
        
        #DEPLOY SERVO command
        elif key == 'd':
            servo = 1

        #STUCK simulation command (for testing)
        #elif key == 't':
            #stuck = True

        #QUIT command - only clean way to shut down!
        elif key == 'q':
            break

        #Any other keypress sets motor commands to OFF
        #Also CLEARS sent HOPPER RUN, MINING RUN, DEPLOY SERVO, STUCK commands
        else:
            x = 0
            theta = 0
            extend = 0
            collect = 0
            hopper = 0
            servo = 0
            #stuck = False

        #publish all topics        
        pub_x.publish(x)
        pub_theta.publish(theta)
        pub_extensor.publish(extend)
        pub_collector.publish(collect)
        pub_hopper.publish(hopper)
        pub_servo.publish(servo)
        #simulated stuck fault sig
        #pub_stuck.publish(stuck)

        rate.sleep()
    
