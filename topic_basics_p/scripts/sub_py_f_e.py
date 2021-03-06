#!/usr/bin/env python
import rospy
from std_msgs.msg import String

def py_clbk(rcvd_msg):
    rospy.loginfo("I heard %s", rcvd_msg.data)

rospy.init_node("sub_py_n")
sub_handle_py = rospy.Subscriber("my_first_t", String, py_clbk, queue_size=10)
rospy.spin()