# CMake generated Testfile for 
# Source directory: /home/weety/tart5/src/roscontrol/src/ros_control/transmission_interface
# Build directory: /home/weety/tart5/build/transmission_interface
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(_ctest_transmission_interface_gtest_simple_transmission_test "/home/weety/tart5/build/transmission_interface/catkin_generated/env_cached.sh" "/usr/bin/python" "/opt/ros/kinetic/share/catkin/cmake/test/run_tests.py" "/home/weety/tart5/build/transmission_interface/test_results/transmission_interface/gtest-simple_transmission_test.xml" "--return-code" "/home/weety/tart5/devel/.private/transmission_interface/lib/transmission_interface/simple_transmission_test --gtest_output=xml:/home/weety/tart5/build/transmission_interface/test_results/transmission_interface/gtest-simple_transmission_test.xml")
add_test(_ctest_transmission_interface_gtest_differential_transmission_test "/home/weety/tart5/build/transmission_interface/catkin_generated/env_cached.sh" "/usr/bin/python" "/opt/ros/kinetic/share/catkin/cmake/test/run_tests.py" "/home/weety/tart5/build/transmission_interface/test_results/transmission_interface/gtest-differential_transmission_test.xml" "--return-code" "/home/weety/tart5/devel/.private/transmission_interface/lib/transmission_interface/differential_transmission_test --gtest_output=xml:/home/weety/tart5/build/transmission_interface/test_results/transmission_interface/gtest-differential_transmission_test.xml")
add_test(_ctest_transmission_interface_gtest_four_bar_linkage_transmission_test "/home/weety/tart5/build/transmission_interface/catkin_generated/env_cached.sh" "/usr/bin/python" "/opt/ros/kinetic/share/catkin/cmake/test/run_tests.py" "/home/weety/tart5/build/transmission_interface/test_results/transmission_interface/gtest-four_bar_linkage_transmission_test.xml" "--return-code" "/home/weety/tart5/devel/.private/transmission_interface/lib/transmission_interface/four_bar_linkage_transmission_test --gtest_output=xml:/home/weety/tart5/build/transmission_interface/test_results/transmission_interface/gtest-four_bar_linkage_transmission_test.xml")
add_test(_ctest_transmission_interface_gtest_transmission_interface_test "/home/weety/tart5/build/transmission_interface/catkin_generated/env_cached.sh" "/usr/bin/python" "/opt/ros/kinetic/share/catkin/cmake/test/run_tests.py" "/home/weety/tart5/build/transmission_interface/test_results/transmission_interface/gtest-transmission_interface_test.xml" "--return-code" "/home/weety/tart5/devel/.private/transmission_interface/lib/transmission_interface/transmission_interface_test --gtest_output=xml:/home/weety/tart5/build/transmission_interface/test_results/transmission_interface/gtest-transmission_interface_test.xml")
add_test(_ctest_transmission_interface_gtest_transmission_parser_test "/home/weety/tart5/build/transmission_interface/catkin_generated/env_cached.sh" "/usr/bin/python" "/opt/ros/kinetic/share/catkin/cmake/test/run_tests.py" "/home/weety/tart5/build/transmission_interface/test_results/transmission_interface/gtest-transmission_parser_test.xml" "--return-code" "/home/weety/tart5/devel/.private/transmission_interface/lib/transmission_interface/transmission_parser_test --gtest_output=xml:/home/weety/tart5/build/transmission_interface/test_results/transmission_interface/gtest-transmission_parser_test.xml")
add_test(_ctest_transmission_interface_gtest_simple_transmission_loader_test "/home/weety/tart5/build/transmission_interface/catkin_generated/env_cached.sh" "/usr/bin/python" "/opt/ros/kinetic/share/catkin/cmake/test/run_tests.py" "/home/weety/tart5/build/transmission_interface/test_results/transmission_interface/gtest-simple_transmission_loader_test.xml" "--return-code" "/home/weety/tart5/devel/.private/transmission_interface/lib/transmission_interface/simple_transmission_loader_test --gtest_output=xml:/home/weety/tart5/build/transmission_interface/test_results/transmission_interface/gtest-simple_transmission_loader_test.xml")
add_test(_ctest_transmission_interface_gtest_differential_transmission_loader_test "/home/weety/tart5/build/transmission_interface/catkin_generated/env_cached.sh" "/usr/bin/python" "/opt/ros/kinetic/share/catkin/cmake/test/run_tests.py" "/home/weety/tart5/build/transmission_interface/test_results/transmission_interface/gtest-differential_transmission_loader_test.xml" "--return-code" "/home/weety/tart5/devel/.private/transmission_interface/lib/transmission_interface/differential_transmission_loader_test --gtest_output=xml:/home/weety/tart5/build/transmission_interface/test_results/transmission_interface/gtest-differential_transmission_loader_test.xml")
add_test(_ctest_transmission_interface_gtest_four_bar_linkage_transmission_loader_test "/home/weety/tart5/build/transmission_interface/catkin_generated/env_cached.sh" "/usr/bin/python" "/opt/ros/kinetic/share/catkin/cmake/test/run_tests.py" "/home/weety/tart5/build/transmission_interface/test_results/transmission_interface/gtest-four_bar_linkage_transmission_loader_test.xml" "--return-code" "/home/weety/tart5/devel/.private/transmission_interface/lib/transmission_interface/four_bar_linkage_transmission_loader_test --gtest_output=xml:/home/weety/tart5/build/transmission_interface/test_results/transmission_interface/gtest-four_bar_linkage_transmission_loader_test.xml")
add_test(_ctest_transmission_interface_gtest_transmission_interface_loader_test "/home/weety/tart5/build/transmission_interface/catkin_generated/env_cached.sh" "/usr/bin/python" "/opt/ros/kinetic/share/catkin/cmake/test/run_tests.py" "/home/weety/tart5/build/transmission_interface/test_results/transmission_interface/gtest-transmission_interface_loader_test.xml" "--return-code" "/home/weety/tart5/devel/.private/transmission_interface/lib/transmission_interface/transmission_interface_loader_test --gtest_output=xml:/home/weety/tart5/build/transmission_interface/test_results/transmission_interface/gtest-transmission_interface_loader_test.xml")
subdirs(gtest)
