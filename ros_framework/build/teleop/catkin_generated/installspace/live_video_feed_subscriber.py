#!/usr/bin/env python3

#import needed libraries
import rospy
import os
from std_msgs.msg import Bool



#def live_video_callback(msg):
    #print(msg.data)

if __name__ == '__main__':
    rospy.init_node('live_video_feed_subscriber')
    #while not rospy.is_shutdown():
    os.system("gst-launch-1.0 v4l2src device=/dev/video0 ! video/x-raw, format=YUY2 ! videoconvert ! xvimagesink")
    #rospy.Subscriber('', Bool, live_video_callback)
    