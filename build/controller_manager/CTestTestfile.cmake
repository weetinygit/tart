# CMake generated Testfile for 
# Source directory: /home/weety/tart5/src/roscontrol/src/ros_control/controller_manager
# Build directory: /home/weety/tart5/build/controller_manager
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(_ctest_controller_manager_rostest_test_hwi_switch_test.test "/home/weety/tart5/build/controller_manager/catkin_generated/env_cached.sh" "/usr/bin/python" "/opt/ros/kinetic/share/catkin/cmake/test/run_tests.py" "/home/weety/tart5/build/controller_manager/test_results/controller_manager/rostest-test_hwi_switch_test.xml" "--return-code" "/opt/ros/kinetic/share/rostest/cmake/../../../bin/rostest --pkgdir=/home/weety/tart5/src/roscontrol/src/ros_control/controller_manager --package=controller_manager --results-filename test_hwi_switch_test.xml --results-base-dir \"/home/weety/tart5/build/controller_manager/test_results\" /home/weety/tart5/src/roscontrol/src/ros_control/controller_manager/test/hwi_switch_test.test ")
subdirs(gtest)
