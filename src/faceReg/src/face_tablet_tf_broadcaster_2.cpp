#include <ros/ros.h>
#include <tf/transform_broadcaster.h>
#include <tf/transform_datatypes.h>
#include "std_msgs/Int16.h"
#include <faceReg/facePose.h>
#include <math.h>

#define X_DISPLACE 0.137
#define Y_DISPLACE -0.095
#define Z_DISPLACE 0.6
#define ROLL_DISPLACE 0
#define PITCH_DISPLACE 0
#define YAW_DISPLACE 0


bool msg_received = false;
tf::Transform transform1, transform2, transform3;
tf::Quaternion qtr_trans1, qtr_trans2, qtr_trans3;


void actionNodeCallback(const faceReg::facePose& msg)
{

	ROS_INFO("facepos received");
	transform1.setOrigin( tf::Vector3(msg.trans_x, msg.trans_y, msg.trans_z));
	qtr_trans1.setRPY(msg.rot_x, msg.rot_y, msg.rot_z);
	transform1.setRotation(qtr_trans1);
	//Observer mode
	transform3.setOrigin(tf::Vector3(0.120, 0.516, 0.341));
	qtr_trans3.setRPY(atan(transform1.getOrigin().y()/transform1.getOrigin().z()), atan(transform1.getOrigin().x()/transform1.getOrigin().z()), 0);
	transform3.setRotation(qtr_trans3);
	msg_received = true;
}

int mode = 1;

void modeCallback(const std_msgs::Int16::ConstPtr& msg)
{
	ROS_INFO("Mode received");
	mode = msg->data;
}

int main(int argc, char** argv){
	//Subscribing to markers topic
	ros::init(argc, argv, "tf_broadcaster_node");
	ros::NodeHandle n;
	ros::Subscriber marker_sub = n.subscribe("facePose", 1000, actionNodeCallback);
	ros::Subscriber mode_sub = n.subscribe("tartMode", 1000, modeCallback);
	ros::Rate loop_rate(100);
	
	//Objects for transformation
	tf::TransformBroadcaster br;
	
	transform1.setOrigin( tf::Vector3(0, 0, 0));
	qtr_trans1.setRPY(0, 0, 0);
	transform1.setRotation(qtr_trans1);

	while(!msg_received){  //Do not proceed until first pos is received
		ros::spinOnce();
		loop_rate.sleep();
	}

	//Define transformation from face pose marker to tablet pose marker
	//Overlay mode
	transform2.setOrigin( tf::Vector3(X_DISPLACE, Y_DISPLACE, Z_DISPLACE) );
	qtr_trans2.setRPY(ROLL_DISPLACE, PITCH_DISPLACE, YAW_DISPLACE);
	transform2.setRotation(qtr_trans2);
	
	
						 
						 
	//Publish initial pose to tf
	while (n.ok()){
		br.sendTransform(tf::StampedTransform(transform1, ros::Time::now(), "camera", "face_pos"));
		ROS_INFO("transform sent");
		if (mode == 1) br.sendTransform(tf::StampedTransform(transform3, ros::Time::now(), "base_link", "tablet_target_pos"));
		else if (mode == 2) {
			transform1.setOrigin( tf::Vector3(0, transform1.getOrigin().y(),transform1.getOrigin().z()));
			br.sendTransform(tf::StampedTransform(transform2, ros::Time::now(), "face_pos", "tablet_target_pos"));
		}
		ros::spinOnce();
	}
	return 0;
}