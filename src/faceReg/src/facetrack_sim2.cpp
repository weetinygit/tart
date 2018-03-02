#include "ros/ros.h"
#include "std_msgs/String.h"
#include "visualization_msgs/MarkerArray.h"
#include "visualization_msgs/Marker.h"
#include <geometry_msgs/Pose.h>
#include <tf/transform_datatypes.h>
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
	tf::StampedTransform face_transform, target_transform;
	
	
	
	//Objects for publishing target pose
	geometry_msgs::Pose targetPose;
	double roll, pitch, yaw;
	ros::Publisher targetPose_pub = n.advertise<geometry_msgs::Pose>("targetPose", 10);

	
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
	marker.scale.x = 0.075;
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
		try{
			//Obtain transformed pose (target pose)
			ros::Time now = ros::Time::now();
			lr.waitForTransform("base_link", "face_pos",now, ros::Duration(3.0));
			lr.lookupTransform("base_link", "face_pos", now, face_transform);
			ROS_INFO("Transform received");

			//Convert target pose to relevant objects
			marker.pose.position.x = face_transform.getOrigin().x();
			marker.pose.position.y = face_transform.getOrigin().y();
			marker.pose.position.z = face_transform.getOrigin().z();
			tf::quaternionTFToMsg(face_transform.getRotation(), marker.pose.orientation);
		} catch (tf::TransformException &ex) {
		  ROS_ERROR("%s",ex.what());
		}
		//If there is new incoming message, remap marker
		tf::quaternionMsgToTF(marker.pose.orientation, qtr_ref);
		tf::Matrix3x3(qtr_ref).getRPY(roll, pitch, yaw);
		marker.pose.orientation = tf::createQuaternionMsgFromRollPitchYaw(roll, pitch, yaw-1.57);
		marker_array.markers[0] = marker;
		marker_array.markers[0].header.stamp = ros::Time();
		vis_pub.publish( marker_array );
		ros::Duration(0.05).sleep();

		try{
			//Obtain transformed pose (target pose)
			ros::Time now = ros::Time::now();
			lr.waitForTransform("base_link", "tablet_target_pos" ,now, ros::Duration(3.0));
			lr.lookupTransform("base_link", "tablet_target_pos", now, target_transform);

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
	}

  return 0;
}
