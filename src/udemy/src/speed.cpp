#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/float64.hpp"
#include "std_msgs/msg/string.hpp"

#include<iostream>
#include<math.h>

const double WHEEL_DEFAULT_RADIUS = 12.5 / 100;


class RpmSubNode: public rclcpp::Node
{
    public:
        RpmSubNode() : Node("rpm_sub"){
            this->declare_parameter("speed_val", WHEEL_DEFAULT_RADIUS);
            // Create a subscription to the topic
            rpm_subscription_ = this->create_subscription<std_msgs::msg::Float64>(
                "rpm",10,std::bind(&RpmSubNode::calc_speed_value, this, std::placeholders::_1)
            );
            speed_publisher_ = this->create_publisher<std_msgs::msg::Float64>(
                "speed",10
            );
        }
    private:
    void calc_speed_value(const std_msgs::msg::Float64 & rpm_msg) const
    {
        auto speed_msg = std_msgs::msg::Float64();
        
        rclcpp::Parameter speed_val_param_object = this->get_parameter("speed_val");
        speed_msg.data = rpm_msg.data *(2* speed_val_param_object.as_double() * M_PI)/60;

        speed_publisher_->publish(speed_msg);
        
    }
    rclcpp::Subscription<std_msgs::msg::Float64> ::SharedPtr rpm_subscription_;
    rclcpp::Publisher<std_msgs::msg::Float64>::SharedPtr speed_publisher_;

};

int main(int argc, char *argv[]){
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<RpmSubNode>());
    rclcpp::shutdown();

    return 0;
}