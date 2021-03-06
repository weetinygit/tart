#include <pluginlib/class_loader.h>
#include <ros/ros.h>
#include <boost/scoped_ptr.hpp>

// MoveIt!

#include <moveit/move_group_interface/move_group_interface.h>
#include <moveit/planning_scene_interface/planning_scene_interface.h>

#include <moveit_msgs/DisplayRobotState.h>
#include <moveit_msgs/DisplayTrajectory.h>

#include <moveit_msgs/AttachedCollisionObject.h>
#include <moveit_msgs/CollisionObject.h>



int main(int argc, char **argv) {
  
  //Setup ROS
  ros::init(argc, argv, "plan_node");
  ros::NodeHandle nh;
  ros::AsyncSpinner spinner(1);
  spinner.start();
  
  
  //Setup ROS publishers & subscribers
  moveit::planning_interface::MoveGroupInterface group("manipulator");
  moveit::planning_interface::PlanningSceneInterface planning_scene_interface;
  ros::Publisher display_publisher = nh.advertise<moveit_msgs::DisplayTrajectory>("/move_group/display_planned_path", 1, true);
  group.setPlannerId("RRTConnectkConfigDefault");
  //Attempt to write directly to /joint_states topic
  ros::Publisher joint_states_pub = nh.advertise<sensor_msgs::JointState>("/move_group/fake_controller_joint_states", 1000);
  ros::Rate loop_rate(10);
  sensor_msgs::JointState joint_states_msg;
  
  //Initialize variables needed for pose and path planning
  geometry_msgs::Pose target_pose1;
  moveit_msgs::DisplayTrajectory display_trajectory;
  
  //Setup loop variables
  int completeStatus = 0;
  
  //Loop
  while (ros::ok()){
    
    ROS_INFO("Pose status: %d", completeStatus);
    ROS_INFO_STREAM("Current pose: #" << group.getCurrentPose());
    
    if (completeStatus == 0) {
      target_pose1.position.x = 0;
      target_pose1.position.y = 5;
      target_pose1.position.z = 15;
      target_pose1.orientation.w = 1;
      target_pose1.orientation.x = -0.382449;
      target_pose1.orientation.y = 0;
      target_pose1.orientation.z = -0.382449;
      group.setPoseTarget(target_pose1);
    }
    else {
      target_pose1.position.x = 3.36;
      target_pose1.position.y = -8.1;
      target_pose1.position.z = 11.2;
      target_pose1.orientation.w = 1;
      group.setPoseTarget(target_pose1);
    }
    
    completeStatus = !completeStatus;
    ROS_INFO_STREAM("Target pose: " << group.getPoseTarget());

    group.setGoalTolerance(0.1);
    moveit::planning_interface::MoveGroupInterface::Plan my_plan;
    bool success = group.plan(my_plan);
    group.setPlanningTime(10);
        
    /* Sleep to give Rviz time to visualize the plan.*/
    sleep(1);  



    ROS_INFO("Visualizing plan 1 (pose goal) %s",success?"":"FAILED");

    //example of extracting plan points
    double r = my_plan.trajectory_.joint_trajectory.points[1].positions[1];



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
