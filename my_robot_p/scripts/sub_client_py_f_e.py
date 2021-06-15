#!/usr/bin/env python
from os import WUNTRACED
from threading import Thread
from time import time
import rospy
from msgsrv_basics_p.msg import RobotStatus
from msgsrv_basics_p.srv import WarningSwitch, WarningSwitchRequest

THRESH=1900
warningCondition=False
prev=False
def statusCallBack(statusMsg):
    global warningCondition
    if(statusMsg.motor1_rpm>THRESH or statusMsg.motor2_rpm>THRESH or statusMsg.motor3_rpm>THRESH or statusMsg.motor4_rpm>THRESH):
        warningCondition=True
    else:
        warningCondition =False


rospy.init_node("sub_client_py_n")
status_sub_py = rospy.Subscriber("my_robot_status",RobotStatus, statusCallBack, queue_size=10)

rospy.wait_for_service("my_robot_warning_s")
warning_client_py = rospy.ServiceProxy("my_robot_warning", WarningSwitch)


service_request_v = WarningSwitchRequest()

while not rospy.is_shutdown():
    if(warningCondition == True) and (prev == False):
        rospy.loginfo("Sending Warning to Server")
        service_request_v.req_msg=True
        service_response_v=warning_client_py(service_request_v)
        rospy.loginfo(service_response_v.res_msg.data)
    elif (warningCondition == False) and (prev == True):
        rospy.loginfo("Sending Normalcy Status to the server")
        service_request_v.req_msg=False
        service_response_v=warning_client_py(service_request_v)
        rospy.loginfo(service_response_v.res_msg.data)

    prev = warningCondition
    time.sleep(0.01)