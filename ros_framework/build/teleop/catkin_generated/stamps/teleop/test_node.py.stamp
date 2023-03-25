#!/usr/bin/env python3

#import needed libraries
import rospy
import time
from std_msgs.msg import Bool, Int16

#ROS node standard form
if __name__ == '__main__':

    rospy.init_node('test_node')

    pub_retract = rospy.Publisher('full_retract_state', Bool, queue_size = 10)
    #pub_mining = rospy.Publisher('run_mining_state', Bool, queue_size = 10)
    #pub_hopper = rospy.Publisher('run_hopper_state', Bool, queue_size = 10)

    rate = rospy.Rate(50)

    while not rospy.is_shutdown():
        
        retract = 1
        
        mining = False

        hopper = False

        pub_retract.publish(retract)
        #pub_mining.publish(mining)
        #pub_hopper.publish(hopper)

        rate.sleep()
