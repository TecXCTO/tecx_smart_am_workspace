# tecx_smart_am_workspace

## Tecx (Technology Engineering Computation Expansion ) Smart Additive Manufacturing Workspace

This architectural design is for a production-grade Advanced Additive Manufacturing Machine with an Integrated 6-DOF Robotic Arm using ROS 2 (Jazzy Jalisco), MuJoCo (Moko) for real-time hardware-in-the-loop (HIL) physics validation, FreeRTOS as the Real-Time Operating System on the motor node, and print_rtf (Rich Text Format Print/Logging Library) for embedded terminal formatting.

### Part 1: GitHub Repository Structural ArchitectureRun these terminal commands to lay out the workspace for an advanced hardware, firmware, and software engineering project:

```
# 1. Structure the workspace layout
mkdir -p smart_am_workspace/src
cd smart_am_workspace/src

# Create the ROS 2 controller, firmware node, and MuJoCo packages
mkdir -p am_arm_control/src am_arm_control/include/am_arm_control
mkdir -p am_arm_hardware/src am_arm_hardware/include/am_arm_hardware
mkdir -p am_arm_firmware/src am_arm_firmware/include
mkdir -p am_arm_description/urdf am_arm_description/mujoco

# 2. Initialize the Git tracking environment
cd ..
git init
echo "build/
install/
log/
.vscode/
*.pyc" > .gitignore

git add .
git commit -m "Initial commit: Production Additive Manufacturing workspace architecture finalized"
git branch -M main
# Link live to GitHub (Replace 'yourusername' with your actual username)
# git remote add origin https://github.com
```
Your final repository blueprint file tree will be structured exactly like this:

```
smart_am_workspace/
├── .gitignore
├── src/
│   ├── am_arm_description/
│   │   ├── urdf/robot_arm.urdf       <-- 6-DOF Spatial AM Arm Definition
│   │   └── mujoco/am_machine.xml     <-- MuJoCo Blueprint with Extruder Actuators
│   ├── am_arm_control/
│   │   ├── src/trajectory_planner.cpp <-- Real-Time Motion Profile Generator
│   │   └── CMakeLists.txt
│   ├── am_arm_hardware/
│   │   ├── src/ros2_hardware_interface.cpp <-- Custom ros2_control Lifecycle Plug-in
│   │   └── CMakeLists.txt
│   └── am_arm_firmware/
│       ├── src/main.c                <-- FreeRTOS Firmware with print_rtf
│       ├── include/print_rtf.h        <-- Rich Text Format Printing / Debugging
│       └── CMakeLists.txt
```

### Part 2: Complete Package Source Files

#### File 1: src/am_arm_description/mujoco/am_machine.xml
The core physics model defining a 6-DOF industrial manipulator equipped with a continuous position-controlled extrusion nozzle terminal effector.


