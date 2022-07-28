// General includes
#include "ros/ros.h"
#include "std_msgs/String.h"
#include "std_msgs/Float64.h"
#include "ros/time.h"
#include "angles/angles.h"

// Conversion from Quaternion to Euler
#include "geometry_msgs/Vector3.h"
#include "geometry_msgs/Quaternion.h"
#include "tf/transform_datatypes.h"
#include "tf/LinearMath/Matrix3x3.h"

// Publisher Subscriber includes
#include "nav_msgs/Odometry.h"
#include "tf/transform_listener.h"

// C++ includes
#include "iostream"
#include "cmath"

ros::Publisher vel_publisher;
ros::Subscriber goal_subscriber;
tf::StampedTransform transform;

// Pose update method
#define ODOMETRY // TRANSFORM // INTEGRATION // LOCALIZATION

namespace husky
{

class Speed_Controller
{
	geometry_msgs::Point position, goal_position;
	geometry_msgs::Quaternion orientation, goal_orientation;
	geometry_msgs::Vector3 rpy, goal_rpy;
	geometry_msgs::Twist speed;

	double limit = 0.01, factor = 100, euclidean_limit = limit / factor;
	ros::Time begin, end;
	double rot = 2*M_PI;

	geometry_msgs::Vector3 point_to_v3(geometry_msgs::Point p)
	{
		geometry_msgs::Vector3 v;
		v.x = p.x; v.y = p.y; v.z = p.z;
		return v;
	}

	geometry_msgs::Vector3 euler_from_quaternion(geometry_msgs::Quaternion msg)
	{
		// the incoming geometry_msgs::Quaternion is transformed to a tf::Quaterion
		tf::Quaternion quat;
		tf::quaternionMsgToTF(msg, quat);

		// the tf::Quaternion has a method to acess roll pitch and yaw
		double roll, pitch, yaw;
		tf::Matrix3x3(quat).getRPY(roll, pitch, yaw, 1);	// solution_number = 1
		
		geometry_msgs::Vector3 ret_rpy;
		ret_rpy.x = roll;
		ret_rpy.y = pitch;
		ret_rpy.z = yaw;

		return ret_rpy;
	}

	void publish_velocity(double k = 1)
	{
		begin = ros::Time::now();
		double inc_x = goal_position.x - position.x;
		double inc_y = goal_position.y - position.y;
		double euclidean_dist = std::sqrt(std::pow(inc_x, 2) + std::pow(inc_y, 2));

		double angle_to_goal;
		if(euclidean_dist > euclidean_limit)
			angle_to_goal = std::atan2(inc_y, inc_x);
		else
		{
			rpy.z = angles::normalize_angle_positive(rpy.z);
			goal_rpy.z = angles::normalize_angle_positive(goal_rpy.z);
			angle_to_goal = goal_rpy.z;	// if goal position is reached
			euclidean_limit = limit / 10;
		}
		
		double temp = rot;
		rot = angle_to_goal - rpy.z;
		if(euclidean_dist > euclidean_limit)
		{
			if(abs(rot) > abs(rot + 2*M_PI)) rot = rot + 2*M_PI;
			if(abs(rot) > abs(rot - 2*M_PI)) rot = rot - 2*M_PI;
			else if(abs(rot) > abs(rot - 4*M_PI)) rot = rot - 4*M_PI;
		}
		else rot = angles::normalize_angle_positive(rot);

		ROS_INFO("Position : %f, %f, %f", position.x, position.y, position.z);
		ROS_INFO("RPY : %f, %f, %f", rpy.x, rpy.y, rpy.z);
		ROS_INFO("Goal Pos : %f, %f, %f", goal_position.x, goal_position.y, goal_position.z);
		ROS_INFO("RPY : %f, %f, %f", goal_rpy.x, goal_rpy.y, goal_rpy.z);
		ROS_INFO("Inc : %f, %f, %f, %f", inc_x, inc_y, euclidean_dist, rot);

		if(abs(rot) > 0.5)
		{
			speed.linear.x = 0.0;
			double sign = rot / abs(rot);
			speed.angular.z = sign * std::min(0.5, abs(rot));
		}
		else
		{
			speed.linear.x = std::min(0.5, k * euclidean_dist); // this->distance()
			//speed.linear.x = std::max(10 * this->limit, speed.linear.x);	// 0.01 = 0.001 * 10
			speed.angular.z = 0.0;
		}
		vel_publisher.publish(speed);
	}

	void update_pose()
	{
		#ifdef INTEGRATION
			end = ros::Time::now();
			double dt = (end - begin).toSec();
			double ddist = speed.linear.x * dt;
			double dphi = speed.angular.z * dt;
			rpy.z = rpy.z + dphi;
			position.x = position.x + ddist * std::cos(rpy.z);
			position.y = position.y + ddist * std::sin(rpy.z);
		#endif
		#ifdef TRANSFORM
			tf::TransformListener listener;
			listener.lookupTransform("/odom", "/base_link", ros::Time(0), transform);
			tf::pointTFToMsg(transform.getOrigin(), position);
			tf::quaternionTFToMsg(transform.getRotation(), orientation);
		#endif
		#ifdef ODOMETRY
			nav_msgs::Odometry::ConstPtr odom = ros::topic::waitForMessage<nav_msgs::Odometry>("/odometry/filtered");
			position = odom->pose.pose.position;
			orientation = odom->pose.pose.orientation;
			rpy = euler_from_quaternion(orientation);
		#endif
		#ifdef LOCALIZATION
			ROS_ERROR("Not defined yet.");
		#endif
	}

	double distance()
	{
		tf::Vector3 tf_pv, tf_gv;
		tf::vector3MsgToTF(point_to_v3(position), tf_pv);
		tf::vector3MsgToTF(point_to_v3(goal_position), tf_gv);

		return tf::tfDistance(tf_pv, tf_gv);
	}

	bool goal_reached(double limit)
	{
		geometry_msgs::Transform pose, goal_pose;
		tf::Transform tf_pose, tf_goal_pose;

		pose.translation = point_to_v3(position);
		pose.rotation = orientation;
		goal_pose.translation = point_to_v3(goal_position);
		goal_pose.rotation = goal_orientation;
		
		tf::Vector3 tf_pv, tf_gv;
		tf::vector3MsgToTF(pose.translation, tf_pv);
		tf::vector3MsgToTF(goal_pose.translation, tf_gv);

		tf::transformMsgToTF(pose, tf_pose);
		tf::Quaternion tf_diff = tf_pose.inverseTimes(tf_goal_pose).getRotation().normalize();

		double rpy_diff = abs(goal_rpy.x - rpy.x) + abs(goal_rpy.y - rpy.y) + abs(goal_rpy.z - rpy.z);

		double metric = tf::tfDistance(tf_pv, tf_gv) + tf_diff.length() - 1 + rpy_diff / M_PI;
		ROS_INFO("Metric : %f", metric);
		return metric <= limit;
	}

	void stop()
	{
		speed.linear.x = 0.0;
		speed.angular.z = 0.0;
		vel_publisher.publish(speed);
		euclidean_limit = limit / factor;
	}

public:
	void MsgCallback(const geometry_msgs::PoseStamped::ConstPtr goal_msg)
	{
		this->goal_position = goal_msg->pose.position;
		this->goal_orientation = goal_msg->pose.orientation;
		this->goal_rpy = this->euler_from_quaternion(goal_orientation);

		while(ros::ok() && ! this->goal_reached(this->limit))
		{
			this->publish_velocity();
			this->update_pose();
		}
		ROS_INFO("Goal reached..");
		this->stop(); return;
	}

	void set_limit(double value)
	{
		this->limit = value;
		this->euclidean_limit = value/this->factor;
	}
};
}

int main(int argc, char **argv)
{
    ros::init(argc, argv, "talker");
    ros::NodeHandle n;
	husky::Speed_Controller speed_controller;

	speed_controller.set_limit(0.01);

	// Topic: move_base_simple/goal 	// Type: geometry_msgs/PoseStamped
	goal_subscriber = n.subscribe<geometry_msgs::PoseStamped::ConstPtr>("move_base_simple/goal", 1, &husky::Speed_Controller::MsgCallback, &speed_controller);
	vel_publisher = n.advertise<geometry_msgs::Twist>("cmd_vel", 1000);

    // check for incoming quaternions untill ctrl+c is pressed
    ROS_INFO("waiting for goal position");
	
    ros::spin();
    return 0;
}