# CMake generated Testfile for 
# Source directory: /home/weety/roscontrol/src/ros_control/controller_manager_tests
# Build directory: /home/weety/roscontrol/build/ros_control/controller_manager_tests
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(_ctest_controller_manager_tests_rostest_test_cm_test.test "/home/weety/roscontrol/build/catkin_generated/env_cached.sh" "/usr/bin/python" "/opt/ros/kinetic/share/catkin/cmake/test/run_tests.py" "/home/weety/roscontrol/build/test_results/controller_manager_tests/rostest-test_cm_test.xml" "--return-code" "/opt/ros/kinetic/share/rostest/cmake/../../../bin/rostest --pkgdir=/home/weety/roscontrol/src/ros_control/controller_manager_tests --package=controller_manager_tests --results-filename test_cm_test.xml --results-base-dir \"/home/weety/roscontrol/build/test_results\" /home/weety/roscontrol/src/ros_control/controller_manager_tests/test/cm_test.test ")
add_test(_ctest_controller_manager_tests_nosetests_test "/home/weety/roscontrol/build/catkin_generated/env_cached.sh" "/usr/bin/python" "/opt/ros/kinetic/share/catkin/cmake/test/run_tests.py" "/home/weety/roscontrol/build/test_results/controller_manager_tests/nosetests-test.xml" "--return-code" "/usr/bin/cmake -E make_directory /home/weety/roscontrol/build/test_results/controller_manager_tests" "/usr/bin/nosetests-2.7 -P --process-timeout=60 --where=/home/weety/roscontrol/src/ros_control/controller_manager_tests/test --with-xunit --xunit-file=/home/weety/roscontrol/build/test_results/controller_manager_tests/nosetests-test.xml")
add_test(_ctest_controller_manager_tests_rostest_test_cm_msgs_utils_rostest.test "/home/weety/roscontrol/build/catkin_generated/env_cached.sh" "/usr/bin/python" "/opt/ros/kinetic/share/catkin/cmake/test/run_tests.py" "/home/weety/roscontrol/build/test_results/controller_manager_tests/rostest-test_cm_msgs_utils_rostest.xml" "--return-code" "/opt/ros/kinetic/share/rostest/cmake/../../../bin/rostest --pkgdir=/home/weety/roscontrol/src/ros_control/controller_manager_tests --package=controller_manager_tests --results-filename test_cm_msgs_utils_rostest.xml --results-base-dir \"/home/weety/roscontrol/build/test_results\" /home/weety/roscontrol/src/ros_control/controller_manager_tests/test/cm_msgs_utils_rostest.test ")
