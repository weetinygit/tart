#include <pluginlib/class_loader.h>
#include <ros/ros.h>

// MoveIt!
#include <moveit/robot_model_loader/robot_model_loader.h>
#include <moveit/planning_interface/planning_interface.h>
#include <moveit/planning_scene/planning_scene.h>
#include <moveit/kinematic_constraints/utils.h>
#include <moveit_msgs/DisplayTrajectory.h>
#include <moveit_msgs/PlanningScene.h>

int main(int argc, char **argv) {
    ros::init (argc, argv, "move_group_tutorial");
    ros::AsyncSpinner spinner(1);
    spinner.start();
    ros::NodeHandle node_handle("~");
    
    robot_model_loader::RobotModelLoader robot_model_loader("robot_description");
    robot_model::RobotModelPtr robot_model = robot_model_loader.getModel();
    ROS_INFO("Model frame: %s", robot_model->getModelFrame().c_str());
    
    
    robot_state::RobotStatePtr kinematic_state(new robot_state::RobotState(robot_model));
    kinematic_state->setToDefaultValues();
    const robot_state::JointModelGroup *joint_model_group = robot_model->getJointModelGroup("manipulator");

    const std::vector<std::string> &joint_names = joint_model_group->getVariableNames();
    
    std::vector<double> joint_values;
    kinematic_state->copyJointGroupPositions(joint_model_group, joint_values);
    for (std::size_t i = 0; i < joint_names.size(); ++i) {
    ROS_INFO("Joint %s: %f", joint_names[i].c_str(), joint_values[i]);}
    
    kinematic_state->setToRandomPositions(joint_model_group);
    const Eigen::Affine3d &end_effector_state = kinematic_state->getGlobalLinkTransform("tablet");
    
    /* Set one joint in the right arm outside its joint limit */
joint_values[0] = 1.57;
kinematic_state->setJointGroupPositions(joint_model_group, joint_values);

/* Check whether any joint is outside its joint limits */
ROS_INFO_STREAM("Current state is " << (kinematic_state->satisfiesBounds() ? "valid" : "not valid"));

/* Enforce the joint limits for this state and check again*/
kinematic_state->enforceBounds();
ROS_INFO_STREAM("Current state is " << (kinematic_state->satisfiesBounds() ? "valid" : "not valid"));

    /* Print end-effector pose. Remember that this is in the model frame */
    ROS_INFO_STREAM("Translation: " << end_effector_state.translation());
    ROS_INFO_STREAM("Rotation: " << end_effector_state.rotation());
    
    bool found_ik = kinematic_state->setFromIK(joint_model_group, end_effector_state, 10, 0.1);
    if (found_ik) {
  kinematic_state->copyJointGroupPositions(joint_model_group, joint_values);
  for (std::size_t i = 0; i < joint_names.size(); ++i)
  {
    ROS_INFO("Joint %s: %f", joint_names[i].c_str(), joint_values[i]);
  }
}
else
{
  ROS_INFO("Did not find IK solution");
}
}
