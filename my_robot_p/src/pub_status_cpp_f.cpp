#include "ros/ros.h"
#include <fstream>
#include "msgsrv_basics_p/RobotStatus.h"

using namespace ros;
using namespace std;
int main(int argc, char **argv){
    init(argc,argv,"pub_status_cpp_n");
    NodeHandle nh;
    Publisher pub_handle = nh.advertise<msgsrv_basics_p::RobotStatus>("my_robot_status_t",10);
    Rate loop_rate(1);

    std::fstream fin;
    fin.open("/home/barry/Desktop/ros_ws/src/my_robot_p/data/rpm_locn_data.csv");
    std::string line, word;
    msgsrv_basics_p::RobotStatus status_v;

    while(ok()){
        getline(fin,line);
        std::stringstream s(line);

        getline(s,word,',');
        status_v.motor1_rpm = std::stoi(word);
        getline(s,word,',');
        status_v.motor2_rpm = std::stoi(word);
        getline(s,word,',');
        status_v.motor3_rpm = std::stoi(word);
        getline(s,word,',');
        status_v.motor4_rpm = std::stoi(word);

        getline(s,word,',');
        status_v.locn.x= stof(word);
        getline(s,word,',');
        status_v.locn.y = stof(word);
        getline(s,word,',');
        status_v.locn.z = stof(word);

        pub_handle.publish(status_v);
        ROS_INFO_STREAM(status_v.motor1_rpm<<" "<<
        status_v.motor2_rpm<<" "<<
        status_v.motor3_rpm<<" "<<
        status_v.motor4_rpm<<" "<<
        status_v.locn.x<<" "<<
        status_v.locn.y<<" "<<
        status_v.locn.z<<" ");
        loop_rate.sleep();
    }

}