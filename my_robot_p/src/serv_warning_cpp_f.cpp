#include "ros/ros.h"
#include "msgsrv_basics_p/WarningSwitch.h"

using namespace ros;
bool serviceCallBack(msgsrv_basics_p::WarningSwitch::Request &requestMsg, 
                    msgsrv_basics_p::WarningSwitch::Response &responseMsg){
    if(requestMsg.req_msg){
        ROS_INFO_STREAM("Warning Received");
        responseMsg.res_msg.data="Warning Acknowledged by Server";
    }
    else{
        ROS_INFO_STREAM("Normal Status Received");
        responseMsg.res_msg.data = "Normal Status Received";
    }
    return true;
}

int main(int argc, char **argv){
    init(argc, argv, "serv_warning_cpp_n");
    NodeHandle nh;
    ServiceServer service_handle = nh.advertiseService("my_robot_service_s", serviceCallBack);
    spin();
    return 0;
}