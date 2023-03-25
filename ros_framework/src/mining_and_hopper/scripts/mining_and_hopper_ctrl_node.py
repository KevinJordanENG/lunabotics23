#!/usr/bin/env python3

#For all VEX Talon Motor control publishers 0=OFF, 1=FWD, -1=REV

#import needed libraries
import rospy
import time
from std_msgs.msg import Int16, Bool


#class object for easier main node flow programming: stuck_fault message ROS subscriber
class stuck_fault_sub:
    #class level variable accessable in main program node
    stuck_fault_flag = Bool()
    #object initialize as subscriber
    def __init__(self):
        self.stuck_fault_subscriber = rospy.Subscriber('stuck_fault_state', Bool, self.stuck_fault_flag_callback)
    #callback function assigning msg recieved to class level varibale
    def stuck_fault_flag_callback(self, msg):
        self.stuck_fault_flag.data = msg.data


#class object for easier main node flow programming: run_mining message ROS subscriber
class run_extensor_sub:
    #class level variable accessable in main program node
    run_extensor_flag = Int16()
    #object initialize as subscriber
    def __init__(self):
        self.run_extensor_subscriber = rospy.Subscriber('run_extensor_state', Int16, self.run_extensor_flag_callback)
    #callback function assigning msg recieved to class level varibale
    def run_extensor_flag_callback(self, msg):
        self.run_extensor_flag.data = msg.data

#class object for easier main node flow programming: run_mining message ROS subscriber
class run_collector_sub:
    #class level variable accessable in main program node
    run_collector_flag = Int16()
    #object initialize as subscriber
    def __init__(self):
        self.run_collector_subscriber = rospy.Subscriber('run_collector_state', Int16, self.run_collector_flag_callback)
    #callback function assigning msg recieved to class level varibale
    def run_collector_flag_callback(self, msg):
        self.run_collector_flag.data = msg.data


#class object for easier main node flow programming: run_hopper message ROS subscriber
class run_hopper_sub:
    #class level variable accessable in main program node
    run_hopper_flag = Bool()
    #object initialize as subscriber
    def __init__(self):
        self.run_hopper_subscriber = rospy.Subscriber('run_hopper_state', Bool, self.run_hopper_flag_callback)
    #callback function assigning msg recieved to class level varibale
    def run_hopper_flag_callback(self, msg):
        self.run_hopper_flag.data = msg.data

#class object for easier main node flow programming: mining_motors command ROS publisher
class extensor_motor_pub:
    #object initialize as publisher and pass command args from main program node
    def __init__(self, extensor = 0):
        self.extensor = extensor
        #setup ROS publishing & publish passed command args
        self.pub_extensor = rospy.Publisher('extensor_cmd_signal', Int16, queue_size = 10)
        self.pub_extensor.publish(self.extensor)

#class object for easier main node flow programming: mining_motors command ROS publisher
class collector_motor_pub:
    #object initialize as publisher and pass command args from main program node
    def __init__(self, collector = 0):
        self.collector = collector
        #setup ROS publishing & publish passed command args
        self.pub_collector = rospy.Publisher('collector_cmd_signal', Int16, queue_size = 10)
        self.pub_collector.publish(self.collector)

#class object for easier main node flow programming: hopper_motors command ROS publisher
class hopper_motor_pub:
    #object initialize as publisher and pass command arg from main program node
    def __init__(self, hopper = 0):
        self.hopper = hopper
        #setup ROS publishing & publish passed command arg
        self.pub_hopper = rospy.Publisher('hopper_cmd_signal', Int16, queue_size = 10)
        self.pub_hopper.publish(self.hopper)


if __name__ == '__main__':
    #initialize node
    rospy.init_node('mining_and_hopper_ctrl_node')
    #publish rate (Hz)
    rate = rospy.Rate(100)
    #null val for motor signals on startup / while waiting for execution
    non_cycle_null_val = 0

    #keep node running unless CTRL C pressed
    while not rospy.is_shutdown():
        #initialize subscribers
        stuck_fault = stuck_fault_sub()
        run_extensor = run_extensor_sub()
        run_collector = run_collector_sub()
        run_hopper = run_hopper_sub()
        
        '''#if command to run mining is received activate system
        if run_mining.run_mining_flag.data == True:
            #start deploy timer
            deploy_timer = time.time() + 30
            while time.time() < deploy_timer:
                #publish extensor=EXT, collector=FWD
                mining_motors_pub(1, 1)
                #stuck_fault signal received?
                if stuck_fault.stuck_fault_flag.data == True:
                    #shutdown mining, publish extensor=OFF, collector=OFF
                    mining_motors_pub(0, 0)
                    #add stuck_fault recovery cycle time to deployement timer
                    deploy_timer += 10
                    #start stuck recovery timer
                    stuck_recovery_timer = time.time() + 10
                    while time.time() < stuck_recovery_timer:
                        #publish extensor=RTCT, collector=OFF
                        mining_motors_pub(-1, 0)
                        #print("stuck fault recovery retract")
                        rate.sleep()
                    #publish extensor=OFF, collector=OFF for transition back to mining
                    mining_motors_pub(0, 0)
                #print("deploying mining")
                rate.sleep()
            #publish extensor=OFF, collector=OFF for transition to retraction cycle
            mining_motors_pub(0, 0)
            #start retract timer
            retract_timer = time.time() + 30
            while time.time() < retract_timer:
                #publish extensor=RTCT, collector=OFF
                mining_motors_pub(-1, 0)
                #print("retracting mining")
                rate.sleep()
            mining_motors_pub(0, 0)'''

        

        if run_extensor.run_extensor_flag.data == 0:
            #set timer to run hopper for (x)s
            timer1 = time.time() + 0.01
            while time.time() < timer1:
                #publish x command to motors node
                extensor_motor_pub(0)
                rate.sleep()
        
        if run_extensor.run_extensor_flag.data == 1:
            #set timer to run hopper for (x)s
            timer2 = time.time() + 0.01
            while time.time() < timer2:
                #publish x command to motors node
                extensor_motor_pub(-1)
                rate.sleep()

        if run_extensor.run_extensor_flag.data == -1:
            #set timer to run hopper for (x)s
            timer3 = time.time() + 0.01
            while time.time() < timer3:
                #publish x command to motors node
                extensor_motor_pub(1)
                rate.sleep()
        
        if run_collector.run_collector_flag.data == 0:
            #set timer to run hopper for (x)s
            timer4 = time.time() + 0.01
            while time.time() < timer4:
                #publish x command to motors node
                collector_motor_pub(0)
                rate.sleep()
        
        if run_collector.run_collector_flag.data == 1:
            #set timer to run hopper for (x)s
            timer5 = time.time() + 0.01
            while time.time() < timer5:
                #publish x command to motors node
                collector_motor_pub(-1)
                rate.sleep()

        if run_collector.run_collector_flag.data == -1:
            #set timer to run hopper for (x)s
            timer6 = time.time() + 0.01
            while time.time() < timer6:
                #publish x command to motors node
                collector_motor_pub(1)
                rate.sleep()

        #if command to run hopper is received activate system
        if run_hopper.run_hopper_flag.data == True:
            #set timer to run hopper for (x)s
            hopper_timer = time.time() + 0.01
            while time.time() < hopper_timer:
                #publish hopper run FWD signal (1)
                hopper_motor_pub(1)
                #print("Running hopper")
                rate.sleep()
            hopper_motor_pub(0)

        #when not actively cycling the mining or hopper systems publish OFF commands to motors
        #extensor_motor_pub(non_cycle_null_val)
        #collector_motor_pub(non_cycle_null_val)
        hopper_motor_pub(non_cycle_null_val)
        #print("listening")

        rate.sleep()