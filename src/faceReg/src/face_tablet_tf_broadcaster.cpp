#include <ros/ros.h>
#include <tf/transform_broadcaster.h>
#include <tf/transform_datatypes.h>
#include "visualization_msgs/MarkerArray.h"
#include "visualization_msgs/Marker.h"

#define X_DISPLACE 0.2
#define Y_DISPLACE 0.137
#define ROLL_DISPLACE 1.517
#define PITCH_DISPLACE 0
#define YAW_DISPLACE 1.517


visualization_msgs::Marker marker;
int msg_received = 0;
tf::Transform transform1, transform2;
tf::Quaternion qtr_trans1, qtr_trans2;

void actionNodeCallback(const visualization_msgs::MarkerArray::ConstPtr& msg)
{
	
	msg_received++;
	ROS_INFO("%d Marker pos received", msg_received);
	marker = msg->markers[0];
	//Update transforms: Define transformation from face pose marker to tablet pose marker, then publish
	transform1.setOrigin( tf::Vector3(marker.pose.position.x, marker.pose.position.y, marker.pose.position.z));
	tf::quaternionMsgToTF(marker.pose.orientation, qtr_trans1);
	transform1.setRotation(qtr_trans1);
}

int main(int argc, char** argv){
	//Subscribing to markers topic
	ros::init(argc, argv, "tf_broadcaster_node");
	ros::NodeHandle n;
	ros::Subscriber marker_sub = n.subscribe("visualization_marker_array", 1000, actionNodeCallback);
	ros::Rate loop_rate(30);
	
	//Objects for transformation
	tf::TransformBroadcaster br;
	
	while(msg_received == 0){  //Do not proceed until first marker is received
		ros::spinOnce();
		loop_rate.sleep();
	}
	//Define transformation from face pose marker to tablet pose marker
	transform2.setOrigin( tf::Vector3(X_DISPLACE, Y_DISPLACE, 0.0) );
	qtr_trans2.setRPY(ROLL_DISPLACE, PITCH_DISPLACE, YAW_DISPLACE);
	transform2.setRotation(qtr_trans2);
	
	//Publish initial pose to tf
	while (n.ok()){
		br.sendTransform(tf::StampedTransform(transform1, ros::Time::now(), "base_link", "face_pos"));
		br.sendTransform(tf::StampedTransform(transform2, ros::Time::now(), "face_pos", "tablet_pos"));
		ros::spinOnce();
		loop_rate.sleep();
	}
	return 0;
}