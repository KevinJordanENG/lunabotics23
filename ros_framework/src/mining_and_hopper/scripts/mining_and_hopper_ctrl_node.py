#!/usr/bin/env python3

#import needed libraries
import rospy
from std_msgs.msg import Int16, Bool

class stuck_fault_sub:

    def __init__(self):
        self.stuck_fault_flag = False
        self.stuck_fault_subscriber = rospy.Subscriber("stuck_fault_state", Bool, self.stuck_fault_flag_callback)

    def stuck_fault_flag_callback(self, msg):
        self.stuck_fault_flag = msg.data


class run_mining_sub:

    def __init__(self):
        self.run_mining_flag = False
        self.run_mining_subscriber = rospy.Subscriber("run_mining_state", Bool, self.stuck_fault_flag_callback)

    def run_mining_flag_callback(self, msg):
        self.run_mining_flag = msg.date

class run_hopper_sub:

    def __init__(self):
        self.run_hopper_flag = False
        self.run_hopper_subscriber = rospy.Subscriber("run_hopper_state", Bool, self.stuck_fault_flag_callback)

    def run_hopper_flag_callback(self, msg):
        self.run_hopper_flag = msg.date

class mining_motors_pub:

    def __init__(self, extensor = 0, collector = 0):
        self.extensor = extensor
        self.collector = collector
        self.pub_extensor = rospy.Publisher("extensor_cmd_signal", Int16, queue_size = 10)
        self.pub_collector = rospy.Publisher("collector_cmd_signal", Int16, queue_size = 10)

    def mining_motors_cmd_publish(self):
        self.pub_extensor.publish(self.extensor)
        self.pub_collector.publish(self.collector)

class hopper_motor_pub:

    def __init__(self, hopper = 0):
        self.hopper = hopper
        self.pub_hopper = rospy.Publisher("hopper_cmd_signal", Int16, queue_size = 10)
    
    def hopper_motor_cmd_publish(self):
        self.pub_hopper.publish(self.hopper)


if __name__ == '__main__':
    #initialize node
    rospy.init_node('mining_and_hopper_ctrl_node')

    startup_null_val = 0
    mining_cycle_complete_flag = False

    while not rospy.is_shutdown():
        stuck_fault = stuck_fault_sub()
        run_mining = run_mining_sub()
        run_hopper = run_hopper_sub()
        if run_mining.run_mining_flag == True:
            while mining_cycle_complete_flag == False:
        elif run_hopper.run_hopper_flag == True:
            hopper_motor_pub()
        else:
            pass


