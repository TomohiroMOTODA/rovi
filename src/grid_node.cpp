#include <ros/ros.h>
#include <geometry_msgs/Point.h>
#include <geometry_msgs/Pose.h>
#include <sensor_msgs/Image.h>
#include <std_srvs/Trigger.h>
#include "rovi/GetGrid.h"
#include <vector>
#include <string>
#include <cstdio>
#include <opencv2/opencv.hpp>
#include <cv_bridge/cv_bridge.h>
#include <sensor_msgs/image_encodings.h>
#include "CircleCalibBoard.h"

CircleCalibBoard cboard;
ros::NodeHandle *nh;

bool get_grid(rovi::GetGrid::Request &req,rovi::GetGrid::Response &res){
	cv_bridge::CvImagePtr cv_ptr1;
	try{
		cv_ptr1=cv_bridge::toCvCopy(req.img,sensor_msgs::image_encodings::MONO8);
//		cv_ptr1=cv_bridge::toCvCopy(req.img,sensor_msgs::image_encodings::BGR8);
	}
	catch(cv_bridge::Exception& e){
		ROS_ERROR("get_grids:cv_bridge:exception: %s", e.what());
		return false;
	}
//	cboard.init();
	std::vector<cv::Point2f> imagePoints;
	cv::Mat mat;
	if(cboard.scan(cv_ptr1->image,imagePoints,&mat)){
		ROS_ERROR("CircleCalibBoard::scan:failed:");
		return false;
	}
	else{
		cv_ptr1->image=mat;
		cv_ptr1->encoding="bgr8";
		cv_ptr1->toImageMsg(res.img);
		int nx=cboard.para["n_circles_x"];
		int ny=cboard.para["n_circles_y"];
		std::vector<cv::Point3f> model;
		std::vector<cv::Point2f> scene;
		geometry_msgs::Point p;
		p.z=0;
//		for(int i=0;i<imagePoints.size();i++){
//			imagePoints[i].x=req.img.width/2+30*nx/2-i%nx*30;
//			imagePoints[i].y=req.img.height/2+30*ny/2-i/nx*30;
//		}
		for(int i=0;i<imagePoints.size();i++){
			if(imagePoints[i].x==FLT_MAX || imagePoints[i].y==FLT_MAX) p.z=-1;//recognition failed
			else p.z=0;
			p.x=imagePoints[i].x;
			p.y=imagePoints[i].y;
			res.grid.push_back(p);
			if(p.z<0) continue;
			cv::Point3f pm(cboard.get_3d_position(i));
			cv::Point2f ps(p.x,p.y);
			model.push_back(pm);
			scene.push_back(ps);
		}
		double flen=req.img.width/2; //Approx. focal length
		nh->getParam("gridboard/focalLength",flen);
		std::cout<<" focal::"<<flen<<"\n";
		cv::Point2f cen=cv::Point2f(req.img.width/2,req.img.height/2);  //Center of image
		cv::Mat kmat=(cv::Mat_<float>(3,3)<<flen,0,cen.x,0,flen,cen.y,0,0,1);
		cv::Mat dmat=cv::Mat::zeros(4,1,cv::DataType<float>::type); //No distortion
		cv::Mat rmat,tmat;
		cv::OutputArray oRmat(rmat),oTmat(tmat);
		cv::solvePnP(model,scene,kmat,dmat,oRmat,oTmat);
		float rx=rmat.at<float>(0,0);
		float ry=rmat.at<float>(1,0);
		float rz=rmat.at<float>(2,0);
		float rw=sqrt(rx*rx+ry*ry+rz*rz);
		res.pose.position.x=tmat.at<float>(0,0);
		res.pose.position.y=tmat.at<float>(1,0);
		res.pose.position.z=tmat.at<float>(2,0);
		res.pose.orientation.x= rw>0? sin(rw/2)*rx/rw:rx;
		res.pose.orientation.y= rw>0? sin(rw/2)*ry/rw:ry;
		res.pose.orientation.z= rw>0? sin(rw/2)*rz/rw:rz;
		res.pose.orientation.w=cos(rw/2);
		return true;
	}
}

bool reload(std_srvs::Trigger::Request &req,std_srvs::Trigger::Response &res){
	for(std::map<std::string, double>::iterator itr=cboard.para.begin();itr!=cboard.para.end();++itr){
		std::string pname("gridboard/");
		pname+=itr->first;
		if(nh->hasParam(pname)) nh->getParam(pname,itr->second);
	}
	cboard.init();
	return true;
}

int main(int argc, char **argv){
	ros::init(argc,argv,"grid_node");
	ros::NodeHandle n;
	nh=&n;
	cboard.para["bin_type"]=1;

	ros::ServiceServer svc1=n.advertiseService("gridboard",get_grid);
	ros::ServiceServer svc2=n.advertiseService("gridboard/reload",reload);
	std_srvs::Trigger::Request req;
	std_srvs::Trigger::Response res;
	reload(req,res);
	ros::spin();
	return 0;
}
