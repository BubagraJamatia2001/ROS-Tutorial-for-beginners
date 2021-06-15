#include "ros/ros.h"
using namespace ros;
int main(int argc, char ** argv){
    init(argc,argv,"hello_log_coo_n");
    NodeHandle n;
    Rate loop_hz(10);
    while(ros::ok()){
        ROS_INFO_STREAM("Hello from C++");
        loop_hz.sleep();
    }
    return 0;
}