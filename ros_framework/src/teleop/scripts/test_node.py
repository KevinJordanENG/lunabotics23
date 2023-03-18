#!/usr/bin/env python3

#import needed libraries
import rospy
import time
from std_msgs.msg import Bool

#ROS node standard form
if __name__ == '__main__':

    rospy.init_node('read_stuck_fault_GPIO_publisher')

    pub_stuck = rospy.Publisher('stuck_fault_state', Bool, queue_size = 10)
    pub_mining = rospy.Publisher('run_mining_state', Bool, queue_size = 10)
    pub_hopper = rospy.Publisher('run_hopper_state', Bool, queue_size = 10)

    rate = rospy.Rate(50)

    while not rospy.is_shutdown():
        
        stuck = False
        
        mining = False

        hopper = False

        pub_stuck.publish(stuck)
        pub_mining.publish(mining)
        pub_hopper.publish(hopper)

        rate.sleep()
