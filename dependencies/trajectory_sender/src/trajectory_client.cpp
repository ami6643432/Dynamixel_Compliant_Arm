#include <rclcpp/rclcpp.hpp>
#include <std_msgs/msg/float64_multi_array.hpp>
#include <sensor_msgs/msg/joint_state.hpp>

class TrajectoryClient : public rclcpp::Node
{
public:
    TrajectoryClient() : Node("trajectory_client")
    {
        RCLCPP_INFO(this->get_logger(), "Initializing trajectory client...");
        
        // Publisher for commands
        cmd_pub_ = this->create_publisher<std_msgs::msg::Float64MultiArray>(
            "/arm_2r_controller/commands", 10);

        // Timer to publish commands periodically
        timer_ = this->create_wall_timer(
            std::chrono::seconds(1),
            std::bind(&TrajectoryClient::timer_callback, this));

        RCLCPP_INFO(this->get_logger(), "Publisher created for topic: /arm_2r_controller/commands");
    }

private:
    rclcpp::Publisher<std_msgs::msg::Float64MultiArray>::SharedPtr cmd_pub_;
    rclcpp::TimerBase::SharedPtr timer_;

    void timer_callback()
    {
        auto msg = std::make_unique<std_msgs::msg::Float64MultiArray>();
        msg->data = {0.0, 0.8};  // Desired position

        RCLCPP_INFO(this->get_logger(), 
                    "Publishing command: [%.2f, %.2f]", 
                    msg->data[0], msg->data[1]);
        
        cmd_pub_->publish(std::move(msg));

        // Print number of subscribers
        RCLCPP_INFO(this->get_logger(), 
                    "Number of subscribers: %d", 
                    cmd_pub_->get_subscription_count());
    }
};

int main(int argc, char** argv)
{
    rclcpp::init(argc, argv);
    RCLCPP_INFO(rclcpp::get_logger("main"), "Starting trajectory client...");
    
    auto node = std::make_shared<TrajectoryClient>();
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}