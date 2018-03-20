Commands to launch simulator:
roslaunch tart_moveit_config demo.launch arduino_usb:=/dev/ttyACM0
rosrun faceReg facePoseRecognition
rostopic pub tartMode std_msgs/Int16 1
rosrun path_planner path_planner_2

