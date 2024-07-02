#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"

#include <chrono>
#include <functional>

using namespace std::chrono_literals;

class HelloWorldpubNode : public rclcpp::Node
{
public:
    HelloWorldpubNode() : Node("hello_world_pub_node")
    {
        publisher_ = this->create_publisher<std_msgs::msg::String>(
            "hello_world", 10
        );
        timer_ = this->create_wall_timer(
            1s, 
            std::bind(&HelloWorldpubNode::publish_hello_world, this)
        );
    }

private:
    void publish_hello_world()
    {
        auto message = std_msgs::msg::String();
        message.data = "hello world " + std::to_string(counter_);

        publisher_->publish(message);

        counter_++;
    }

    rclcpp::Publisher<std_msgs::msg::String>::SharedPtr publisher_;
    rclcpp::TimerBase::SharedPtr timer_;
    size_t counter_ = 0;
};

int main(int argc, char *argv[])
{
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<HelloWorldpubNode>());
    rclcpp::shutdown();

    return 0;
}
