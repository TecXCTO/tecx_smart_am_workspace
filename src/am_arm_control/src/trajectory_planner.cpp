#include <memory>
#include <rclcpp/rclcpp.hpp>
#include <sensor_msgs/msg/joint_state.hpp>
#include <std_msgs/msg/float64_multi_array.hpp>

class AmArmTrajectoryPlanner : public rclcpp::Node {
public:
    AmArmTrajectoryPlanner() : Node("am_arm_trajectory_planner") {
        // Publisher for streaming reference setpoints directly to the ros2_control engine
        command_pub_ = this->create_publisher<std_msgs::msg::Float64MultiArray>(
            "/forward_position_controller/commands", 10);

        // Timer to enforce a strict 100Hz trajectory generation loop
        timer_ = this->create_wall_timer(
            std::chrono::milliseconds(10), std::bind(&AmArmTrajectoryPlanner::generate_trajectory, this));
        
        RCLCPP_INFO(this->get_logger(), "ROS 2 Additive Manufacturing Trajectory Node operational.");
    }

private:
    void generate_trajectory() {
        auto command_msg = std_msgs::msg::Float64MultiArray();
        command_msg.data.resize(6);

        // Multi-axis spatial calculation profile logic
        double time_sec = this->now().seconds();
        command_msg.data[0] = 0.5 * sin(time_sec * 0.5); // Smooth sinusoidal scanning motions
        command_msg.data[1] = 0.2 * cos(time_sec * 0.5);
        command_msg.data[2] = 0.1 * sin(time_sec * 1.0);
        command_msg.data[3] = 0.0;
        command_msg.data[4] = 0.0;
        command_msg.data[5] = time_sec * 0.1; // Continuous extrusion rotation tracking

        command_pub_->publish(command_msg);
    }

    rclcpp::Publisher<std_msgs::msg::Float64MultiArray>::SharedPtr command_pub_;
    rclcpp::TimerBase::SharedPtr timer_;
};

int main(int argc, char **argv) {
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<AmArmTrajectoryPlanner>());
    rclcpp::shutdown();
    return 0;
}
