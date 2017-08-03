#include "PathPlanner.hpp"


PathPlanner::PathPlanner(ros::NodeHandle node,geometry_msgs::PoseStamped inicio, geometry_msgs::PoseStamped fim){

	ros::ServiceClient client = node.serviceClient<nav_msgs::GetPlan>("/move_base/make_plan",true);	
	
	fillPathRequest(path.request,inicio, fim);

	if(client.call(path)){
		if(!path.response.plan.poses.empty()){
			size= path.response.plan.poses.size();
		}
	}


}


void PathPlanner::fillPathRequest(nav_msgs::GetPlan::Request &request,geometry_msgs::PoseStamped inicio, geometry_msgs::PoseStamped fim){
    request.start.header.frame_id = "map";
    request.start.pose.position.x = inicio.pose.position.x;
    request.start.pose.position.y = inicio.pose.position.y;
    request.start.pose.orientation.w = inicio.pose.orientation.w;

    request.goal.header.frame_id = "map";
    request.goal.pose.position.x = fim.pose.position.x;
    request.goal.pose.position.y = fim.pose.position.y;
    request.goal.pose.orientation.w = fim.pose.orientation.w;

    request.tolerance = 0.5;


}


void PathPlanner::next_point(float &x,float &y){
	if (i > size){
		i = size - 1;
	}	
	x=path.response.plan.poses[i].pose.position.x;
	y=path.response.plan.poses[i].pose.position.y;
	i++;
}
