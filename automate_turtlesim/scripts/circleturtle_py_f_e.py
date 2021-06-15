#!/usr/bin/env python
import rospy
from geometry_msgs.msg import Twist
from turtlesim.msg import Pose
import random

is_turtle_outside=None 

def pose_clbk(pose_message):
    global is_turtle_outside
    is_turtle_outside = (pose_message.x<2) or (pose_message.x>8) or \
        (pose_message.y<2) or (pose_message.y>8)


rospy.init_node("circleturtle_py_n")
vel_pub_py = rospy.Publisher("turtle1/cmd_vel",Twist,queue_size=10)
pos_sub_py = rospy.Subscriber("turtle1/pose",Pose,pose_clbk,queue_size=10)
loop_rate = rospy.Rate(20)

velocity_v = Twist()
velocity_v.linear.x=1
#velocity_v.angular.z=1

while not rospy.is_shutdown():
    # velocity_v.angular.z=random.random()
    if(is_turtle_outside):
        velocity_v.angular.z=1
    else:
        velocity_v.angular.z=0

    vel_pub_py.publish(velocity_v)
    loop_rate.sleep()
    

