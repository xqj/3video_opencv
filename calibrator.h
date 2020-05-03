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
	calibrator(string, float, int, int);           //���캯������ȡͼ�����Ϣ

	void calc_image_points(bool);                  //�ҵ�ͼ����ڽǵ�

	void calibrate();                              //�����������

	Mat get_cameraMatrix();                        //�õ�������ڲξ���

	Mat get_distCoeffs();                          //�õ�����Ļ���ϵ��

	void get_error();                              //�Ա궨�����������

	void Correct_image();                          //�鿴�궨Ч���������ñ궨���������ͼ���н���

private:
	string pattern;                       //30�ű궨ͼƬ��λ��
	vector<Mat> images;                //���ڱ���궨ͼƬ
	Mat cameraMatrix, distCoeffs;      //���������ڲξ��󡢻���ϵ��


	bool show_chess_corners;
	float side_length;                 //���̵��������η���ĳ���
	int width, height;                 //�ڽǵ��ڳ��Ϳ����ϵ�����
	vector<vector<Point2f> > image_points;  //����2D��
	vector<vector<Point3f> > object_points; //����3D��
	vector<Mat> rvecs, tvecs;               //����ÿ��ͼƬR��T��ת������

};