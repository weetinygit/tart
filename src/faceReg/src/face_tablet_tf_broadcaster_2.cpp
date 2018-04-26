#include <ros/ros.h>
#include <tf/transform_broadcaster.h>
#include <tf/transform_datatypes.h>
#include "std_msgs/Int16.h"
#include <faceReg/facePose.h>
#include <math.h>

//For overlay mode
#define X_DISPLACE 0.137
#define Y_DISPLACE -0.095
#define Z_DISPLACE 0.25   // minimum distance
#define ROLL_DISPLACE_OVERLAY 0.33 //0.4

//For observer mode
#define X_OBSERVER 0
#define Y_OBSERVER 0.428
#define Z_OBSERVER 0.349
#define ROLL_DISPLACE 2.118
#define PITCH_DISPLACE 0
#define YAW_DISPLACE 0

bool msg_received = false;
tf::Transform defaultTransform, transform1, transform2, transform3, transform4;
tf::Quaternion qtr_default, qtr_trans1, qtr_trans2, qtr_trans3, qtr_trans4;
int mode = 1;
int camera_setting = 3;
double last_pose_received = 0;

/*Callback function to handle incoming face pose msgs*/
void actionNodeCallback(const faceReg::facePose& msg)
{
	last_pose_received = ros::Time::now().toSec();
	//Overlay mode
	transform1.setOrigin( tf::Vector3(msg.trans_x, msg.trans_y, msg.trans_z));
	if (mode==2) transform1.setOrigin( tf::Vector3(0, transform1.getOrigin().y(),transform1.getOrigin().z()));
	qtr_trans1.setRPY(msg.rot_x, msg.rot_y, msg.rot_z);
	transform1.setRotation(qtr_trans1);
	//Observer mode
	qtr_trans3.setRPY(-atan(transform1.getOrigin().y()/transform1.getOrigin().z())+ROLL_DISPLACE, 0, atan(transform1.getOrigin().x()/transform1.getOrigin().z()));
	transform3.setRotation(qtr_trans3);
	msg_received = true;
}


void modeCallback(const std_msgs::Int16::ConstPtr& msg)
{
	ROS_INFO("Mode received");
	if (msg->data<3) mode = msg->data;
	else camera_setting = msg->data;
}

int main(int argc, char** argv){
	//Initializations
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
	defaultTransform.setOrigin( tf::Vector3(0.026, 1, 0.2));
	qtr_default.setRPY(1.57, 0, 0);
	defaultTransform.setRotation(qtr_default);
	//Observer mode
	transform3.setOrigin(tf::Vector3(0, 0.440, 0.397));
	qtr_trans3.setRPY(ROLL_DISPLACE, 0, 0);
	transform3.setRotation(qtr_trans3);
	transform4.setOrigin(tf::Vector3(0.1435, 0, 0));
	qtr_trans4.setRPY(0, 0, 0);
	transform4.setRotation(qtr_trans4);
	//Overlay mode
	transform2.setOrigin( tf::Vector3(X_OBSERVER, Y_OBSERVER, Z_OBSERVER));
	qtr_trans2.setRPY(ROLL_DISPLACE_OVERLAY, 0, 0);
	transform2.setRotation(qtr_trans2);		

	/*while(!msg_received){  //Do not proceed until first pos is received
		ros::spinOnce();
		loop_rate.sleep();
	}*/

 
						 
	//Publish initial pose to tf
	while (n.ok()){
		if((ros::Time::now().toSec() - last_pose_received) < 0.5) br.sendTransform(tf::StampedTransform(transform1, ros::Time::now(), "camera", "face_pos"));
		else br.sendTransform(tf::StampedTransform(defaultTransform, ros::Time::now(), "base_link", "face_pos"));
		if (mode == 1) {
			br.sendTransform(tf::StampedTransform(transform3, ros::Time::now(), "base_link", "tablet_target_pos_axis"));
			br.sendTransform(tf::StampedTransform(transform4, ros::Time::now(), "tablet_target_pos_axis", "tablet_target_pos_0"));
		}
		else if (mode == 2) {
			transform2.setOrigin( tf::Vector3(X_DISPLACE, Y_DISPLACE, Z_DISPLACE));
			br.sendTransform(tf::StampedTransform(transform2, ros::Time::now(), "face_pos", "tablet_target_pos_0"));
		}
		ros::spinOnce();
	}
	return 0;
}