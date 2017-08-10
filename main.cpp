#include "DiffBot.hpp"
#include "PathPlanner.hpp"



int main(int argc, char** argv){
	const float Kv=0.5;
	const float Kh=1;
	const float L = 0.16;
	const float e=0.05;
	float xf=2;
	float yf=2;
	float speed,turn,angle;
	const float disToPoint=0.8;
	geometry_msgs::PoseStamped inicio,fim;
	
        inicio.pose.position.x = 2;
    	inicio.pose.position.y = 2;
    	inicio.pose.orientation.w = 1.0;
		
        fim.pose.position.x = 3;
    	fim.pose.position.y = 8;
    	fim.pose.orientation.w = 1.0;
	
	ros::init(argc, argv, "turtlebot_foward");
	ros::NodeHandle n;
	string topic="/mobile_base/commands/velocity"; //Meu topico
	//string topic="/cmd_vel_mux/input/teleop"; //Seu topico

	DiffBot bob(topic,n,2,2,0);
	ros::Subscriber sub = n.subscribe("odom", 1000,&DiffBot::set_position,&bob);
	PathPlanner plan(n,inicio,fim);
	
	ros::Rate loop_rate(10);
	while(n.ok()){
		if (bob.distance_to(fim.pose.position.x,fim.pose.position.y) > e){
			while ((bob.distance_to(xf,yf) < disToPoint) && (xf !=fim.pose.position.x  && yf !=fim.pose.position.y)){
				plan.next_point(xf,yf);		
				cout << "X Objetivo: " << xf << " Y Objetivo: " << yf << endl;
			}

			speed=Kv*bob.distance_to(xf,yf);
			angle=atan((yf - bob.get_y())/(xf - bob.get_x()));
			turn=(speed/L)*tan(Kh*DiffBot::angdif(angle,bob.get_o()));

			bob.set_speed(speed,turn);
		}else
			bob.set_speed(0,0);

		bob.publish();	
		cout << "X: " << bob.get_x() << " Y: " << bob.get_y() << " Angulo: "<< bob.get_o() <<endl;
		ros::spinOnce();
   		loop_rate.sleep();
	}

}
