# CMake generated Testfile for 
# Source directory: /home/weety/tart5/src/roscontrol/src/ros_control/joint_limits_interface
# Build directory: /home/weety/tart5/build/joint_limits_interface
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(_ctest_joint_limits_interface_gtest_joint_limits_interface_test "/home/weety/tart5/build/joint_limits_interface/catkin_generated/env_cached.sh" "/usr/bin/python" "/opt/ros/kinetic/share/catkin/cmake/test/run_tests.py" "/home/weety/tart5/build/joint_limits_interface/test_results/joint_limits_interface/gtest-joint_limits_interface_test.xml" "--return-code" "/home/weety/tart5/devel/.private/joint_limits_interface/lib/joint_limits_interface/joint_limits_interface_test --gtest_output=xml:/home/weety/tart5/build/joint_limits_interface/test_results/joint_limits_interface/gtest-joint_limits_interface_test.xml")
add_test(_ctest_joint_limits_interface_gtest_joint_limits_urdf_test "/home/weety/tart5/build/joint_limits_interface/catkin_generated/env_cached.sh" "/usr/bin/python" "/opt/ros/kinetic/share/catkin/cmake/test/run_tests.py" "/home/weety/tart5/build/joint_limits_interface/test_results/joint_limits_interface/gtest-joint_limits_urdf_test.xml" "--return-code" "/home/weety/tart5/devel/.private/joint_limits_interface/lib/joint_limits_interface/joint_limits_urdf_test --gtest_output=xml:/home/weety/tart5/build/joint_limits_interface/test_results/joint_limits_interface/gtest-joint_limits_urdf_test.xml")
add_test(_ctest_joint_limits_interface_rostest_test_joint_limits_rosparam.test "/home/weety/tart5/build/joint_limits_interface/catkin_generated/env_cached.sh" "/usr/bin/python" "/opt/ros/kinetic/share/catkin/cmake/test/run_tests.py" "/home/weety/tart5/build/joint_limits_interface/test_results/joint_limits_interface/rostest-test_joint_limits_rosparam.xml" "--return-code" "/opt/ros/kinetic/share/rostest/cmake/../../../bin/rostest --pkgdir=/home/weety/tart5/src/roscontrol/src/ros_control/joint_limits_interface --package=joint_limits_interface --results-filename test_joint_limits_rosparam.xml --results-base-dir \"/home/weety/tart5/build/joint_limits_interface/test_results\" /home/weety/tart5/src/roscontrol/src/ros_control/joint_limits_interface/test/joint_limits_rosparam.test ")
subdirs(gtest)