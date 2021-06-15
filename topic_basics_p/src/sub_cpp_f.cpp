#include "ros/ros.h"
#include "std_msgs/String.h"

using namespace ros;
using namespace std_msgs;

void cpp_clbk(String received_msg){
    ROS_INFO_STREAM("I heard :"<< received_msg.data);
}

int main(int argc, char **argv){
    init(argc,argv,"sub_cpp_n");
    NodeHandle nh;
    Subscriber sub_handle_cpp = nh.subscribe("my_first_t", 10, cpp_clbk);
    spin();
    return 0;
}