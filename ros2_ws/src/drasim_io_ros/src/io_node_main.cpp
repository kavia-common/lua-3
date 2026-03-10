#include "drasim_io_ros/io_node.hpp"
#include <rclcpp/rclcpp.hpp>
int main(int c,char*v[]){rclcpp::init(c,v);rclcpp::spin(std::make_shared<drasim_io_ros::IONode>());rclcpp::shutdown();return 0;}
