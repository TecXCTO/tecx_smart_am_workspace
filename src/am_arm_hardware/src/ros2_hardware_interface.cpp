#include <hardware_interface/system_interface.hpp>
#include <hardware_interface/types/hardware_interface_type_values.hpp>
#include <rclcpp/rclcpp.hpp>

namespace am_arm_hardware {

class AdditiveMachineHardware : public hardware_interface::SystemInterface {
public:
    CallbackReturn on_init(const hardware_interface::HardwareInfo & info) override {
        if (SystemInterface::on_init(info) != CallbackReturn::SUCCESS) {
            return CallbackReturn::ERROR;
        }
        
        // Allocate space for 6 multi-axis robotic joints
        hw_positions_.resize(6, 0.0);
        hw_velocities_.resize(6, 0.0);
        hw_commands_.resize(6, 0.0);
        return CallbackReturn::SUCCESS;
    }

    std::vector<hardware_interface::StateInterface> export_state_interfaces() override {
        std::vector<hardware_interface::StateInterface> state_interfaces;
        for (size_t i = 0; i < 6; ++i) {
            state_interfaces.emplace_back(hardware_interface::StateInterface(
                info_.joints[i].name, hardware_interface::HW_IF_POSITION, &hw_positions_[i]));
            state_interfaces.emplace_back(hardware_interface::StateInterface(
                info_.joints[i].name, hardware_interface::HW_IF_VELOCITY, &hw_velocities_[i]));
        }
        return state_interfaces;
    }

    std::vector<hardware_interface::CommandInterface> export_command_interfaces() override {
        std::vector<hardware_interface::CommandInterface> command_interfaces;
        for (size_t i = 0; i < 6; ++i) {
            command_interfaces.emplace_back(hardware_interface::CommandInterface(
                info_.joints[i].name, hardware_interface::HW_IF_POSITION, &hw_commands_[i]));
        }
        return command_interfaces;
    }

    hardware_interface::return_type read(const rclcpp::Time &, const rclcpp::Duration &) override {
        // [Firmware Communication Bridge] 
        // Read raw encoder updates from FreeRTOS target over EtherCAT/CAN/UART.
        for(size_t i=0; i<6; ++i) {
            hw_positions_[i] = hw_commands_[i]; // Simulating perfect tracking loopback execution
        }
        return hardware_interface::return_type::OK;
    }

    hardware_interface::return_type write(const rclcpp::Time &, const rclcpp::Duration &) override {
        // [Firmware Communication Bridge]
        // Stream optimized reference commands straight down to FreeRTOS low-level registers.
        return hardware_interface::return_type::OK;
    }

private:
    std::vector<double> hw_positions_;
    std::vector<double> hw_velocities_;
    std::vector<double> hw_commands_;
};

} // namespace am_arm_hardware

#include <pluginlib/class_list_macros.hpp>
PLUGINLIB_EXPORT_CLASS(am_arm_hardware::AdditiveMachineHardware, hardware_interface::SystemInterface)
