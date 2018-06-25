//============================================================================
// Name        : IP_Cam.cpp
// Author      : Nicolas IUNG
// Version     :
// Copyright   :
// Description : Hello World in C++, Ansi-style
//============================================================================


#include "rclcpp/rclcpp.hpp"
#include "sensor_msgs/msg/joy.hpp"
#include "geometry_msgs/msg/twist.hpp"
using std::placeholders::_1;

#define TOPIC_NAME_PUB "cmd_vel" //Topic Name
#define TOPIC_NAME_SUB "joy"

class JoyTeleop: public rclcpp::Node {
public:
	JoyTeleop() :
			Node("JoyTeleop") {
		//Init Publisher
		publisher_ = this->create_publisher<geometry_msgs::msg::Twist>(
		TOPIC_NAME_PUB, rmw_qos_profile_sensor_data);
		subscription_ = this->create_subscription<sensor_msgs::msg::Joy>(
				"topic", std::bind(&JoyTeleop::topic_callback, this, _1));
	}

private:
	rclcpp::Publisher<geometry_msgs::msg::Twist>::SharedPtr publisher_;
	rclcpp::Subscription<sensor_msgs::msg::Joy>::SharedPtr subscription_;
	void topic_callback(const sensor_msgs::msg::Joy::SharedPtr msg) {
		if (msg->buttons[7])
			boost = 3;
		else
			boost = 1;
		auto twist = geometry_msgs::msg::Twist();
		twist.linear.x = 0.5 * msg->axes[1] * boost;
		twist.linear.y = 0.5 * msg->axes[0] * boost;
		twist.angular.z = -1*(0.5 * msg->axes[2] * boost);
		publisher_->publish(twist);
	}
	int boost = 1;
};

int main(int argc, char * argv[]) {
	rclcpp::init(argc, argv);
	rclcpp::spin(std::make_shared<JoyTeleop>());
	rclcpp::shutdown();
	return 0;
}
