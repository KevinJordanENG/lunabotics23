#!/usr/bin/env python3

#import needed libraries
import rospy
import time
from std_msgs.msg import Int16, Bool

class stuck_fault_sub:
    stuck_fault_flag = Bool()

    def __init__(self):
        self.stuck_fault_subscriber = rospy.Subscriber("stuck_fault_state", Bool, self.stuck_fault_flag_callback)

    def stuck_fault_flag_callback(self, msg):
        self.stuck_fault_flag = msg.data


class run_mining_sub:
    run_mining_flag = Bool()

    def __init__(self):
        self.run_mining_subscriber = rospy.Subscriber("run_mining_state", Bool, self.run_mining_flag_callback)

    def run_mining_flag_callback(self, msg):
        self.run_mining_flag = msg.data

class run_hopper_sub:
    run_hopper_flag = Bool()

    def __init__(self):
        self.run_hopper_subscriber = rospy.Subscriber("run_hopper_state", Bool, self.run_hopper_flag_callback)

    def run_hopper_flag_callback(self, msg):
        self.run_hopper_flag.data = msg.data

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
    hopper_cycle_complete_flag = False
    mining_cycle_complete_flag = False

    while not rospy.is_shutdown():
        stuck_fault = stuck_fault_sub()
        run_mining = run_mining_sub()
        run_hopper = run_hopper_sub()
        #if run_mining.run_mining_flag == True:
            #while mining_cycle_complete_flag == False:
                #print("A")
        if run_hopper.run_hopper_flag.data == True:
            if hopper_cycle_complete_flag == False:
                timer1 = time.time() + 15
                while time.time() < timer1:
                    print("Running hopper")
                hopper_cycle_complete_flag = True
            elif hopper_cycle_complete_flag == True:
                timer2 = time.time() + 5
                while time.time() < timer2:
                    print("waiting for hoper reset")
                hopper_cycle_complete_flag = False
        print("COMPLETE")