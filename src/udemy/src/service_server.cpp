#include "rclcpp/rclcpp.hpp"
#include "udemy/srv/detail/odd_even_check.hpp"

typedef udemy::srv::OddEvenCheck OddEvenCheckSrv;

class OddEvenCheckServiceNode : public rclcpp:Node()
{
    public:
        OddEvenCheckServiceNode():Node("odd_or_even_node")
        {
            service_ = this->create_service<udemy::srv::OddEvenCheck>(
                "odd_or_even_check",
                std:bind(&OddEvenCheckServiceNode::check_num_odd_even, this, 
                    std::placeholders::_1, std::placeholders::_2
                )
            );
        }
        private:
            void check_num_odd_even (
                const OddEvenCheckSrv::Request::SharedPtr request,
                OddEvenCheckSrv::Response::SharedPtr response)
                {
                    if remainder = request->number%2;

                    switch(remainder){
                        case 0:
                            response->descion = "Even";
                            break;
                        case 1:
                            response->descion = "Odd";
                    }
                }
            rclcpp::Service<OddEvenCheckSrv>::SharedPtr service_;
};

    

int main(int argc, char * argv[])
{
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<OddEvenCheckServiceNode>());
    rclcpp::shutdown();
    
    return 0;
}