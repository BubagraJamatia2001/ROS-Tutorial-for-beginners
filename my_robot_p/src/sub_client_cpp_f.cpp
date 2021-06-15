#include "ros/ros.h"
#include "msgsrv_basics_p/RobotStatus.h"
#include "msgsrv_basics_p/WarningSwitch.h"
using namespace ros;
#define THRESH 1900
bool warningCondition = false, warningConditionPrev =false;

void statusCallBack(msgsrv_basics_p::RobotStatus statusMsg){
    if(statusMsg.motor1_rpm>THRESH||statusMsg.motor2_rpm>THRESH||statusMsg.motor3_rpm>THRESH||statusMsg.motor4_rpm>THRESH)
        warningCondition=true;
    else
        warningCondition=false;
    
}

int main(int argc, char **argv){
    init(argc,argv,"sub_status_cpp_n");
    NodeHandle nh;
    Subscriber sub_handle = nh.subscribe("my_robot_status_t",10,statusCallBack);
    ServiceClient client_handle = nh.serviceClient<msgsrv_basics_p::WarningSwitch>("my_robot_warning_s");
    client_handle.waitForExistence();
    msgsrv_basics_p::WarningSwitch warning_v;
    while (ok()){
        if(warningCondition==true && warningConditionPrev==false){
            ROS_INFO_STREAM("Sending Warning to Server");
            warning_v.request.req_msg = warningCondition;
            client_handle.call(warning_v);
            ROS_INFO_STREAM(warning_v.response.res_msg.data);
        }
        else if(warningCondition==false && warningConditionPrev==true){
            ROS_INFO_STREAM("Sending Normal Status to Server");
            warning_v.request.req_msg=warningCondition;
            client_handle.call(warning_v);
            ROS_INFO_STREAM(warning_v.response.res_msg.data);
        }

        warningConditionPrev=warningCondition;
        spinOnce();
    }
    return 0;
    
}