#include <pluginlib/class_loader.h>
#include <ros/ros.h>
#include <boost/scoped_ptr.hpp>
#include "std_msgs/Int16.h"

// MoveIt!

#include <moveit/move_group_interface/move_group_interface.h>
#include <moveit/planning_scene_interface/planning_scene_interface.h>

#include <moveit_msgs/DisplayRobotState.h>
#include <moveit_msgs/DisplayTrajectory.h>

#include <moveit_msgs/AttachedCollisionObject.h>
#include <moveit_msgs/CollisionObject.h>

#include <geometry_msgs/Pose.h>


#include <tf/transform_datatypes.h>
#include <tf/transform_listener.h>

geometry_msgs::Pose targetPose, defaultPose;
int mode = 1;
int completeStatus = 0;

void modeCallback(const std_msgs::Int16::ConstPtr& msg)
{
	ROS_INFO("Mode received");
	mode = msg->data;
	completeStatus = 1;
}

int main(int argc, char **argv) {

	//Setup ROS
	ros::init(argc, argv, "plan_node");
	ros::NodeHandle nh;
	ros::AsyncSpinner spinner(2);
	spinner.start();

	tf::StampedTransform target_transform;
	tf::TransformListener lr;
	
	


	//Setup ROS publishers & subscribers
	moveit::planning_interface::MoveGroupInterface group("manipulator");
	moveit::planning_interface::PlanningSceneInterface planning_scene_interface;
	ros::Publisher display_publisher = nh.advertise<moveit_msgs::DisplayTrajectory>("/move_group/display_planned_path", 1, true);
	ros::Subscriber mode_sub = nh.subscribe("tartMode", 1000, modeCallback);


	group.setPlannerId("RRTConnectkConfigDefault");
	//Write directly to /joint_states topic
	ros::Publisher joint_states_pub = nh.advertise<sensor_msgs::JointState>("/move_group/fake_controller_joint_states", 1000);
	ros::Rate loop_rate(20);
	sensor_msgs::JointState joint_states_msg;

	//Initialize variables needed for pose and path planning
	geometry_msgs::Pose target_pose1;
	moveit_msgs::DisplayTrajectory display_trajectory;

	//Initialize variables needed for joint-space planning
	static const std::string PLANNING_GROUP = "manipulator";
	std::vector<double> joint_group_positions;
	moveit::core::RobotStatePtr current_state;
	const robot_state::JointModelGroup *joint_model_group = group.getCurrentState()->getJointModelGroup(PLANNING_GROUP);

	//Default pose settings
	
	defaultPose.position.x = 0.120;
	defaultPose.position.y = 0.516;
	defaultPose.position.z = 0.341;
	defaultPose.orientation.w = 0.739;
	defaultPose.orientation.x = 0.673;
	defaultPose.orientation.y = 0;
	defaultPose.orientation.z = 0;
	/*
	defaultPose.position.x = 0.140;
	defaultPose.position.y = 0.546;
	defaultPose.position.z = 0.064;
	defaultPose.orientation.w = 1;
	defaultPose.orientation.x = 0;
	defaultPose.orientation.y = 0;
	defaultPose.orientation.z = 0;	
	*/

	//Loop
	while (ros::ok()){

	  if (completeStatus != 0){

		ROS_INFO("Pose status: %d", mode);
		ROS_INFO_STREAM("Current pose: #" << group.getCurrentPose());
		  
		//Check mode. Mode 1: Observer mode. Mode 2: Overlay mode
		if (mode == 1) { 
			
			group.setPoseTarget(defaultPose);
			completeStatus = 0;
			}
		else if (mode == 2) {
			try{
			//Obtain transformed pose (target pose)
			ros::Time now = ros::Time::now();
			lr.waitForTransform("base_link", "tablet_target_pos" ,now, ros::Duration(3.0));
			lr.lookupTransform("base_link", "tablet_target_pos", now, target_transform);
				targetPose.position.x = target_transform.getOrigin().x();
				targetPose.position.y = target_transform.getOrigin().y();
				targetPose.position.z = target_transform.getOrigin().z();
				tf::quaternionTFToMsg(target_transform.getRotation(), targetPose.orientation);
				group.setPoseTarget(targetPose);
			}catch (tf::TransformException &ex) {
		  ROS_ERROR("%s",ex.what());
			}
		}
		  
		loop_rate.sleep();
		ROS_INFO_STREAM("Target pose: " << group.getPoseTarget());

		group.setGoalTolerance(0.005);
		moveit::planning_interface::MoveGroupInterface::Plan my_plan;
		bool success = group.plan(my_plan);
		group.setPlanningTime(5);

		ROS_INFO("Visualizing plan (pose goal) %s",success?"":"FAILED");


		//Recognize end of plan  
		trajectory_msgs::JointTrajectoryPoint plan_end;
		plan_end.positions.push_back(-1000.0);
		my_plan.trajectory_.joint_trajectory.points.push_back(plan_end);
		joint_states_msg.name = my_plan.trajectory_.joint_trajectory.joint_names; 

		int a = 0;
		try{
			while(my_plan.trajectory_.joint_trajectory.points[a].positions[0] != -1000.0f){
				joint_states_msg.position = my_plan.trajectory_.joint_trajectory.points[a].positions;
				joint_states_pub.publish(joint_states_msg);
				a = a+1;
				ROS_INFO("a: %d",a);
				loop_rate.sleep();
				ROS_INFO("Conditional value: %f", my_plan.trajectory_.joint_trajectory.points[a].positions[0]);
				} 
		 }catch(int e){
		 }

		}
	}
      
}
