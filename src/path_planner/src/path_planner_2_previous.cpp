#include <pluginlib/class_loader.h>
#include <ros/ros.h>
#include <boost/scoped_ptr.hpp>
#include "std_msgs/String.h"
#include <string>     // std::string, std::stoi

// MoveIt!

#include <moveit/move_group_interface/move_group_interface.h>
#include <moveit/planning_scene_interface/planning_scene_interface.h>

#include <moveit_msgs/DisplayRobotState.h>
#include <moveit_msgs/DisplayTrajectory.h>

#include <moveit_msgs/AttachedCollisionObject.h>
#include <moveit_msgs/CollisionObject.h>

//Setup loop variables
int completeStatus = 0;

void actionNodeCallback(const std_msgs::String::ConstPtr& msg)
{
  ROS_INFO("I heard: [%s]", msg->data.c_str());
  //Transmit loop variable
  completeStatus = std::stoi (msg->data.c_str(),nullptr,0);
}

int main(int argc, char **argv) {
  
  //Setup ROS
  ros::init(argc, argv, "plan_node");
  ros::NodeHandle nh;
  ros::AsyncSpinner spinner(2);
  spinner.start();
  
  
  //Setup ROS publishers & subscribers
  moveit::planning_interface::MoveGroupInterface group("manipulator");
  moveit::planning_interface::PlanningSceneInterface planning_scene_interface;
  ros::Publisher display_publisher = nh.advertise<moveit_msgs::DisplayTrajectory>("/move_group/display_planned_path", 1, true);
  ros::Subscriber sub = nh.subscribe("/action_node", 1000, actionNodeCallback);
    
  group.setPlannerId("RRTConnectkConfigDefault");
  //Attempt to write directly to /joint_states topic
  ros::Publisher joint_states_pub = nh.advertise<sensor_msgs::JointState>("/move_group/fake_controller_joint_states", 1000);
  ros::Rate loop_rate(10);
  sensor_msgs::JointState joint_states_msg;
  
  //Initialize variables needed for pose and path planning
  geometry_msgs::Pose target_pose1;
  moveit_msgs::DisplayTrajectory display_trajectory;
  
	//Initialize variables needed for joint-space planning
	static const std::string PLANNING_GROUP = "manipulator";
	std::vector<double> joint_group_positions;
	moveit::core::RobotStatePtr current_state;
	const robot_state::JointModelGroup *joint_model_group = group.getCurrentState()->getJointModelGroup(PLANNING_GROUP);

  
  //Loop
  while (ros::ok()){

      if (completeStatus != 0){

        ROS_INFO("Pose status: %d", completeStatus);
        ROS_INFO_STREAM("Current pose: #" << group.getCurrentPose());

        if (completeStatus == 1) {
			
			// sample joint-space target
			
			current_state = group.getCurrentState();
            current_state->copyJointGroupPositions(joint_model_group, joint_group_positions);
			joint_group_positions[1] = -1.0;  // radians
            group.setJointValueTarget(joint_group_positions);
			
			/* sample pose target
			
			
          target_pose1.position.x = -0.195;
          target_pose1.position.y = -0.036;
          target_pose1.position.z = 0.129;
          target_pose1.orientation.w = -0.008;
          target_pose1.orientation.x = -0.010;
          target_pose1.orientation.y = 0.784;
          target_pose1.orientation.z = 0.620;
          group.setPoseTarget(target_pose1);
		  */
        }
        else {
			current_state = group.getCurrentState();
			current_state->copyJointGroupPositions(joint_model_group, joint_group_positions);
			joint_group_positions[1] = -0.5;  // radians
            group.setJointValueTarget(joint_group_positions);
			
			/* sample pose target
          target_pose1.position.x = 0.082;
          target_pose1.position.y = 0.035;
          target_pose1.position.z = 0.279;
          target_pose1.orientation.w = 0.472;
          target_pose1.orientation.x = 0.352;
          target_pose1.orientation.y = 0.483;
          target_pose1.orientation.z = 0.648;
          group.setPoseTarget(target_pose1);
		  */
        }

        completeStatus = 0;
        //ROS_INFO_STREAM("Target pose: " << group.getPoseTarget());

        group.setGoalTolerance(0.1);
        moveit::planning_interface::MoveGroupInterface::Plan my_plan;
        bool success = group.plan(my_plan);
        group.setPlanningTime(10);

        ROS_INFO("Visualizing plan 1 (pose goal) %s",success?"":"FAILED");
		  
        ROS_INFO("Visualizing plan 1 (joint-space goal) %s",success?"":"FAILED");

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
