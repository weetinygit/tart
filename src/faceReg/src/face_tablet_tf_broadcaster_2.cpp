#include <ros/ros.h>
#include <tf/transform_broadcaster.h>
#include <tf/transform_datatypes.h>
#include "visualization_msgs/MarkerArray.h"
#include "visualization_msgs/Marker.h"
#include <faceReg/facePose.h>

#define X_DISPLACE 0.137
#define Y_DISPLACE -0.095
#define Z_DISPLACE 0.6
#define ROLL_DISPLACE 0
#define PITCH_DISPLACE 0
#define YAW_DISPLACE 0


visualization_msgs::Marker marker;
int msg_received = 0;
tf::Transform transform1, transform2;
tf::Quaternion qtr_trans1, qtr_trans2;

void actionNodeCallback(const faceReg::facePose& msg)
{

	ROS_INFO("facepos received");
	transform1.setOrigin( tf::Vector3(msg.trans_x, msg.trans_y, msg.trans_z));
	qtr_trans1.setRPY(msg.rot_x, msg.rot_y, msg.rot_z);
	transform1.setRotation(qtr_trans1);
	msg_received = 1;
}

int main(int argc, char** argv){
	//Subscribing to markers topic
	ros::init(argc, argv, "tf_broadcaster_node");
	ros::NodeHandle n;
	ros::Subscriber marker_sub = n.subscribe("facePose", 1000, actionNodeCallback);
	ros::Rate loop_rate(50);
	
	//Objects for transformation
	tf::TransformBroadcaster br;

	while(msg_received == 0){  //Do not proceed until first pos is received
		ros::spinOnce();
		loop_rate.sleep();
	}

	//Define transformation from face pose marker to tablet pose marker
	transform2.setOrigin( tf::Vector3(X_DISPLACE, Y_DISPLACE, Z_DISPLACE) );
	qtr_trans2.setRPY(ROLL_DISPLACE, PITCH_DISPLACE, YAW_DISPLACE);
	transform2.setRotation(qtr_trans2);
	
	//Publish initial pose to tf
	while (n.ok()){
		br.sendTransform(tf::StampedTransform(transform1, ros::Time::now(), "camera", "face_pos"));
		ROS_INFO("transform sent");
		br.sendTransform(tf::StampedTransform(transform2, ros::Time::now(), "face_pos", "tablet_target_pos"));
		ros::spinOnce();
		loop_rate.sleep();
	}
	return 0;
}