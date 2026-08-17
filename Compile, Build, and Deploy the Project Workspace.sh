# Compile, Build, and Deploy the Project WorkspaceFollow these exact steps in your terminal to compile the packages, launch the real-time simulation layer, and push your source modifications up to your GitHub repository.



# 1. Source your local system ROS 2 environment paths
source /opt/ros/jazzy/setup.bash

# 2. Compile the multi-package robotics workspace using colcon
colcon build --symlink-install

# 3. Source the newly built workspace setup hooks
source install/setup.bash

# 4. Execute the custom trajectory planning node
ros2 run am_arm_control am_arm_trajectory_planner

# 5. Push the code updates live to your online GitHub tracking branch
git add src/
git commit -m "Add URDF/MJCF models, ros2_control hardware interface, and FreeRTOS firmware with print_rtf"
# git push origin main
