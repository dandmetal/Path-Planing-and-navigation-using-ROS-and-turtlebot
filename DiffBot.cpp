#include "DiffBot.hpp"

DiffBot::DiffBot(string topic,ros::NodeHandle n_){
	n=n_;
	cmd_vel=n.advertise<geometry_msgs::Twist>(topic, 1);
	x=0;
	y=0;
	o=0;
	xoff=0;
	yoff=0;
	ooff=0;
	linear_speed=0;
	angular_speed=0;
	vel.linear.x = linear_speed;
	vel.angular.z = angular_speed;
}

DiffBot::DiffBot(string topic,ros::NodeHandle n_,float xo,float yo,float oo){
	n=n_;
	cmd_vel=n.advertise<geometry_msgs::Twist>(topic, 1);
	x=0;
	y=0;
	o=0;
	xoff=xo;
	yoff=yo;
	ooff=oo;
	linear_speed=0;
	angular_speed=0;
	vel.linear.x = linear_speed;
	vel.angular.z = angular_speed;
}


void DiffBot::set_speed(float linar,float angular){
	linear_speed=linar;
	angular_speed=angular;
	vel.linear.x = linear_speed;
	vel.angular.z = angular_speed;
}

void DiffBot::publish(){
	cmd_vel.publish(vel);
}

void DiffBot::set_position(const nav_msgs::Odometry::ConstPtr& msg){
	x=msg->pose.pose.position.x+xoff;
	y=msg->pose.pose.position.y+yoff;
	o=quaterion_to_rad(msg->pose.pose.orientation.z,msg->pose.pose.orientation.w)+ooff;
}

float DiffBot::distance_to(float xo,float yo){
	return sqrt((x-xo)*(x-xo) + (y-yo)*(y-yo));
}


float DiffBot::quaterion_to_rad(float qz,float qw){
	float yaw;
	double t3 = 2.0 * (qw * qz + 0);
	double t4 = 1.0 - 2.0 * (0 + qz*qz);  
	yaw = atan2(t3, t4);
	return yaw;
}

float DiffBot::angdif(float a,float b){
	float c = a- b;
	if (c > M_PI)
		c-=2*M_PI;
	else if (c < -M_PI)
		c+=2*M_PI;
	return c;

}
