#ifndef DIFFBOT_HPP
#define DIFFBOT_HPP

#include <ros/ros.h>
#include <geometry_msgs/Twist.h>
#include <nav_msgs/Odometry.h>
#include <iostream>
#include <string>
#include <cmath>
using namespace std;

class DiffBot{
private:
	float x,y,o,linear_speed,angular_speed,xoff,yoff,ooff;	
	ros::Publisher cmd_vel;
	ros::NodeHandle n;
	geometry_msgs::Twist vel;
	float quaterion_to_rad(float qz,float qw);	
public:
	DiffBot(string topic,ros::NodeHandle n_);
	DiffBot(string topic,ros::NodeHandle n_,float xo,float yo,float oo);
	void set_speed(float linar,float angular);
	void set_position(const nav_msgs::Odometry::ConstPtr& msg);
	void publish();
	float distance_to(float xo,float yo);
	float get_x(){ return x;};
	float get_y(){ return y;};
	float get_o(){ return o;};
	float get_linear_speed(){ return linear_speed; };
	float get_angular_speed(){ return angular_speed;};
	static float angdif(float a,float b);	
};



#endif
