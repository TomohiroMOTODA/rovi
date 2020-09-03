#pragma once

#include <vector>
#include <sensor_msgs/PointCloud.h>
#include <opencv2/opencv.hpp>
#include "iPointCloudGenerator.hpp"

class YPCData : public PointCloudCallback{
private:
	unsigned char *image;
	size_t step;
	int width;
	int height; 
	std::vector<Point3d> points;
	int n_valid;
	
public:
	
	YPCData();
	virtual ~YPCData();
	
	bool is_empty()const;
	
	void operator()(unsigned char *image, const size_t step,const int width, const int height,std::vector<Point3d> &points, const int n_valid);
	
	bool make_point_cloud(sensor_msgs::PointCloud &pts);
	
	bool make_depth_image(cv::Mat &img);
	
	bool save_ply(const std::string &file_path);
};
