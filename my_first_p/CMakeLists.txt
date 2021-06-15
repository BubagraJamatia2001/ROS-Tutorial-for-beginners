cmake_minimum_required(VERSION 3.0.2)
project(my_first_p)

find_package(catkin REQUIRED)
catkin_package()
include_directories()
add_executable(hello_cpp_e src/hello_cpp_f.cpp)
