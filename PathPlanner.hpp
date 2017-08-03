#ifndef PATHPLANNER_HPP
#define PATHPLANNER

#include <ros/ros.h>
#include <geometry_msgs/Pose.h>
#include <geometry_msgs/PoseStamped.h>
#include <nav_msgs/Path.h>
#include <nav_msgs/GetPlan.h>
#include <array>

using namespace std;

class PathPlanner{
private:
	nav_msgs::GetPlan path;
	int i=0;
	int size;
	void fillPathRequest(nav_msgs::GetPlan::Request &request,geometry_msgs::PoseStamped inicio, geometry_msgs::PoseStamped fim);
public:
	PathPlanner(ros::NodeHandle node, geometry_msgs::PoseStamped inicio, geometry_msgs::PoseStamped fim);
	void next_point(float &x,float &y);
};



#endif
