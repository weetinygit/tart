#include <pluginlib/class_loader.h>
#include <ros/ros.h>
#include <boost/scoped_ptr.hpp>
#include "sensor_msgs/JointState.h"

#include "std_msgs/Float32.h"

float joint_states[6];
std_msgs::Float32 joint_states_msg[6];
int newmsg_status = 0;


void actionNodeCallback(const sensor_msgs::JointState& msg)
{
	//msg to variable
	
	for(int i=0; i<6; i++){
		joint_states[i] = msg.position[i]*57.3;
		//variable to msg
		joint_states_msg[i].data = joint_states[i];
	}
	
	//Transmit loop variable
	ROS_INFO("I heard: [%f]", joint_states_msg[0].data);
	newmsg_status = 1;
}

int main(int argc, char **argv) {
  
  //Setup ROS
  ros::init(argc, argv, "arduino_comm");
  ros::NodeHandle nh;
  ros::Publisher motor_pub[6];
  for(int i=0; i<6; i++){
	  motor_pub[i] = nh.advertise<std_msgs::Float32>("/arduino/motor_"+std::to_string(i+1), 1, true);
  }
  ros::Subscriber sub = nh.subscribe("/joint_states", 1000, actionNodeCallback);
  ros::Rate loop_rate(10);
  //Loop
  while (ros::ok()){
	  ros::spinOnce();
      if (newmsg_status==1) {
		  for(int i=0; i<6; i++){
			  motor_pub[i].publish(joint_states_msg[i]);
		  }
		  ROS_INFO("I sent: [%f]", joint_states_msg[0].data);
		  newmsg_status=0;
	  }
  }
   

}
