#pragma once

#include <vector>
#include <sensor_msgs/PointCloud.h>
#include <opencv2/opencv.hpp>
#include <pcl/point_types.h>
#include <pcl/point_cloud.h>
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
	
	int count()const;
	
	void operator()(unsigned char *image, const size_t step,const int width, const int height,std::vector<Point3d> &points, const int n_valid);
	
	bool make_point_cloud(sensor_msgs::PointCloud &pts);
	
	bool make_depth_image(cv::Mat &img);
	
	bool voxelization(const float leaf_x, const float leaf_y, const float leaf_z, sensor_msgs::PointCloud &pts);
	
	bool save_ply(const std::string &file_path);
};