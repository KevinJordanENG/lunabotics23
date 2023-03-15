#!/usr/bin/env python3

#import needed libraries
import rospy
import os
import subprocess
from std_msgs.msg import Bool

#send command in terminal to get list of attached USB cameras & convert to str
list_cameras_cmd = "v4l2-ctl --list-devices"
cameras_full_str = subprocess.Popen(list_cameras_cmd,stdout=subprocess.PIPE,shell=True).communicate()[0]
cameras_full_str = str(cameras_full_str, 'utf-8')

#split full string into individual device strings
cameras_list = cameras_full_str.split("\n\n")

#iterate thru devices to find ZED 2
for i in range(len(cameras_list)):
    #when we find ZED 2 device
    if cameras_list[i].startswith("ZED 2"):
        #split string to get video(X) device number X
        device_param_list = cameras_list[i].split("video")
        device_number = device_param_list[1]

#concatenate device number into terminal command to launch video feed
launch_video_feed_cmd = "gst-launch-1.0 v4l2src device=/dev/video" + device_number + " ! video/x-raw, format=YUY2 ! videoconvert ! xvimagesink"

#ROS node standard form
if __name__ == '__main__':
    #initialize node
    rospy.init_node('live_video_feed')

    #send terminal command to start live video feed
    os.system(launch_video_feed_cmd)

    #since video feed and ROS node both require CTRL C to exit no need to rospy.spin()
    #single CTRL C command kills video feed and ROS node
    