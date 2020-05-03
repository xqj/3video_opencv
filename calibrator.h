#pragma once
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/calib3d/calib3d.hpp>


#define IMAGE_FOLDER "C:\\Users\\wind\\Pictures\\Camera Roll\\"


using namespace cv;
using namespace std;
//using namespace boost::filesystem;

class calibrator
{
public:
	calibrator(string, float, int, int);           //构造函数，读取图像的信息

	void calc_image_points(bool);                  //找到图像的内角点

	void calibrate();                              //计算相机参数

	Mat get_cameraMatrix();                        //得到相机的内参矩阵

	Mat get_distCoeffs();                          //得到相机的畸变系数

	void get_error();                              //对标定结果进行评价

	void Correct_image();                          //查看标定效果——利用标定结果对棋盘图进行矫正

private:
	string pattern;                       //30张标定图片的位置
	vector<Mat> images;                //用于保存标定图片
	Mat cameraMatrix, distCoeffs;      //定义的相机内参矩阵、畸变系数


	bool show_chess_corners;
	float side_length;                 //棋盘单个正方形方块的长度
	int width, height;                 //内角点在长和宽方向上的数量
	vector<vector<Point2f> > image_points;  //保存2D点
	vector<vector<Point3f> > object_points; //保存3D点
	vector<Mat> rvecs, tvecs;               //保存每张图片R，T的转换矩阵

};