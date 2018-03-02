#include "ros/ros.h"
#include "std_msgs/String.h"
#include "visualization_msgs/MarkerArray.h"
#include "visualization_msgs/Marker.h"
#include <ncurses.h>
#include <geometry_msgs/Pose.h>
#include <tf/transform_datatypes.h>
#include <tf/transform_broadcaster.h>
#include <tf/transform_listener.h>



int main(int argc, char **argv)
{
	//Objects for publishing markers on rviz
	ros::init(argc, argv, "facetrack_sim");
	ros::NodeHandle n;
	ros::Publisher vis_pub = n.advertise<visualization_msgs::MarkerArray>( "visualization_marker_array", 10 );
	visualization_msgs::MarkerArray marker_array;
	visualization_msgs::Marker marker, poseMarker;
	ros::Rate loop_rate(10);
	tf::Quaternion qtr_ref;
	tf::TransformListener lr;
	tf::StampedTransform target_transform;
	
	
	
	//Objects for publishing target pose
	geometry_msgs::Pose targetPose;
	double roll, pitch, yaw;
	ros::Publisher targetPose_pub = n.advertise<geometry_msgs::Pose>("targetPose", 10);
	
	
	//Functions to initialize capture of keystrokes
	initscr();
	cbreak();
	noecho();
	int ch=0;
	
	//Initialize face pose marker
	marker.header.frame_id = "base_link";
	marker.header.stamp = ros::Time();
	marker.ns = "faceWithPose";
	marker.id = 0;
	marker.type = visualization_msgs::Marker::ARROW;
	marker.action = visualization_msgs::Marker::ADD;
	marker.pose.position.x = 0;
	marker.pose.position.y = 1.0;
	marker.pose.position.z = 0.3;
	marker.pose.orientation.x = 0.0;
	marker.pose.orientation.y = 0.0;
	marker.pose.orientation.z = -0.707;
	marker.pose.orientation.w = 0.707;
	marker.scale.x = 0.045;
	marker.scale.y = 0.02;
	marker.scale.z = 0.02;
	marker.color.a = 1.0; // Don't forget to set the alpha!
	marker.color.r = 0.0;
	marker.color.g = 1.0;
	marker.color.b = 0.0;
	marker_array.markers.push_back(marker);
	marker_array.markers.push_back(marker);
	
	//Duplicate marker for tablet pose
	marker_array.markers[1].ns = "targetTabletPose";
	marker_array.markers[1].color.r = 1.0;
	
	//Publish markers
	vis_pub.publish( marker_array );
	ros::spinOnce();
	loop_rate.sleep();
	
	
	int count = 1;
	while (ros::ok()){
		ROS_INFO("Use 'WSAD' to displace, 'rf' and 'zx' to tilt");
		ROS_INFO("%d KEY PRESSED: %c", count, ch);
		count++;
        ch = getch();
		if(ch == 'q') break;
		
		switch(ch){
			case 'w': 
				marker.pose.position.z = marker.pose.position.z + 0.01;
				break;
			case 's': 
				marker.pose.position.z = marker.pose.position.z - 0.01;
				break;
			case 'a': 
				marker.pose.position.x = marker.pose.position.x + 0.01;
				break;
			case 'd': 
				marker.pose.position.x = marker.pose.position.x - 0.01;
				break;
			case 'r':
				tf::quaternionMsgToTF(marker.pose.orientation, qtr_ref);
				tf::Matrix3x3(qtr_ref).getRPY(roll, pitch, yaw);
				marker.pose.orientation = tf::createQuaternionMsgFromRollPitchYaw(roll, pitch-0.1, yaw);
				break;
			case 'f': 
				tf::quaternionMsgToTF(marker.pose.orientation, qtr_ref);
				tf::Matrix3x3(qtr_ref).getRPY(roll, pitch, yaw);
				marker.pose.orientation = tf::createQuaternionMsgFromRollPitchYaw(roll, pitch+0.1, yaw);
				break;
			case 'z': 
				tf::quaternionMsgToTF(marker.pose.orientation, qtr_ref);
				tf::Matrix3x3(qtr_ref).getRPY(roll, pitch, yaw);
				marker.pose.orientation = tf::createQuaternionMsgFromRollPitchYaw(roll, pitch, yaw+0.1);
				break;
			case 'x': 
				tf::quaternionMsgToTF(marker.pose.orientation, qtr_ref);
				tf::Matrix3x3(qtr_ref).getRPY(roll, pitch, yaw);
				marker.pose.orientation = tf::createQuaternionMsgFromRollPitchYaw(roll, pitch, yaw-0.1);
				break;
			case 'e':
				marker.pose.position.y = marker.pose.position.y - 0.01;
				break;
			case 'c':
				marker.pose.position.y = marker.pose.position.y + 0.01;
				break;
		}
		marker_array.markers[0] = marker;
		marker_array.markers[0].header.stamp = ros::Time();
		vis_pub.publish( marker_array );
		ros::Duration(0.05).sleep(); 
		try{
			//Obtain transformed pose (target pose)
			ros::Time now = ros::Time::now();
			lr.waitForTransform("base_link", "tablet_pos",now, ros::Duration(3.0));
			lr.lookupTransform("base_link", "tablet_pos", now, target_transform);

			//Convert target pose to relevant objects
			targetPose.position.x = target_transform.getOrigin().x();
			targetPose.position.y = target_transform.getOrigin().y();
			targetPose.position.z = target_transform.getOrigin().z();
			tf::quaternionTFToMsg(target_transform.getRotation(), targetPose.orientation);
		} catch (tf::TransformException &ex) {
		  ROS_ERROR("%s",ex.what());
		}
		
		marker_array.markers[1].pose = targetPose;
		marker_array.markers[1].header.stamp = ros::Time();
		vis_pub.publish( marker_array );
		targetPose_pub.publish( targetPose );
		

		ros::spinOnce();
		loop_rate.sleep();
		clear();
		refresh();
	}

  return 0;
}
