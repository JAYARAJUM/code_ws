#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"
#include "std_msgs/msg/float64.hpp"
#include "std_msgs/msg/bool.hpp"
#include "std_msgs/msg/int32.hpp"



class HelloWorldSubNode : public rclcpp::Node
{
    public:
        HelloWorldSubNode(): Node("hello_world_sub_node")
        {
            subscription_ = this->create_subscription<std_msgs::msg::String>(
                "hello_world",10, std::bind(&HelloWorldSubNode::sub_callback, this, std::placeholders::_1)
            );
        }
    private:
        void sub_callback(const std_msgs::msg::String & msg ) const {
            //std::cout << msg.data << std::endl;
            RCLCPP_INFO(this->get_logger(), msg.data.c_str());
            RCLCPP_DEBUG(this->get_logger(), msg.data.c_str());
            RCLCPP_ERROR(this->get_logger(), msg.data.c_str());
        }
        rclcpp::Subscription<std_msgs::msg::String> ::SharedPtr subscription_;        

};

int main(int argc, char * argv[])
{
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<HelloWorldSubNode>());
    rclcpp::shutdown();

    return 0;
}
