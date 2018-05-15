//============================================================================
// Name        : IP_Cam.cpp
// Author      : Nicolas IUNG
// Version     :
// Copyright   :
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <stdio.h>
#include <opencv2/opencv.hpp>
#include <iostream>
#include <memory>
#include <vector>
#include <chrono>
#include <ctime>
#include "rclcpp/rclcpp.hpp"
#include "sensor_msgs/msg/compressed_image.hpp"
#include "CurrentTime.h"
#include <cv_bridge/cv_bridge.h>
#define TOPIC_NAME "web_cam"
#define URL "http://admin:admin@192.168.1.7/videostream.cgi?.mjpg"

class IPCamPublisher: public rclcpp::Node {
public:
	IPCamPublisher() :
			Node("IPCam_publisher"), count_(0) {
		publisher_ = this->create_publisher<sensor_msgs::msg::CompressedImage>(
		TOPIC_NAME, rmw_qos_profile_sensor_data);
		cv::VideoCapture vcap;
		cv::Mat image;
		if (!vcap.open(URL)) {
			std::cout << "Error opening video stream or file" << std::endl;
		}
		for (;;) {
			if (!vcap.read(image)) {
				std::cout << "No frame" << std::endl;
				cv::waitKey();
			}
			auto message = sensor_msgs::msg::CompressedImage();
			cv_bridge::CvImage(std_msgs::msg::Header(), "bgr8", image).toCompressedImageMsg(
					message);
			CurrentTime now;
			message.header.stamp.sec = now.seconds();
			message.header.stamp.nanosec = now.nanoseconds();

			publisher_->publish(message);
			if (cv::waitKey(1) >= 0)
				break;
		}
	}

private:
	rclcpp::Publisher<sensor_msgs::msg::CompressedImage>::SharedPtr publisher_;
	size_t count_;
};

int main(int argc, char * argv[]) {
	rclcpp::init(argc, argv);
	rclcpp::spin(std::make_shared<IPCamPublisher>());
	rclcpp::shutdown();
	return 0;
}
