//#include "calibrator.h"
//#include <opencv2\imgproc\types_c.h>
//
//calibrator::calibrator(string _path, float _side_length, int _width, int _height)
//{
//	side_length = _side_length;
//	width = _width;
//	height = _height;
//
//	pattern = _path;
//	cout << "图片的位置：" << pattern << endl;
//
//	//std::string pattern = "./img/*.jpg";
//	std::vector<cv::String>image_file;
//
//	glob(pattern, image_file);
//	cout << "图片数量:"<< endl;
//	cout << image_file.size() << endl;
//	for (int i = 0;i < image_file.size();i++)
//	{
//		images.push_back(imread(image_file[i]));
//	}
//
//}
//
//void calibrator::calc_image_points(bool show)  //计算内角点
//{
//	cout << "内角点计算" << endl;
//	//计算物体坐标系中的物体点(左上角原点)
//	vector<Point3f> ob_p;        //定义内角点的容器，20个点
//	cout << "height" << endl;
//	cout << height << endl;
//	cout << "width" << endl;
//	cout << width << endl;
//	for (int i = 0; i < height; i++) //4
//	{
//		for (int j = 0; j < width; j++) //5
//		{
//			ob_p.push_back(Point3f(j * side_length, i * side_length, 0.f));
//		}
//	}
//
//	if (show) namedWindow("Chessboard corners");
//
//	cout << "开始循环查找" << endl;
//	for (int i = 0; i < images.size(); i++)
//	{
//		cout << "图序列i:" << endl;
//		cout << i << endl;
//		Mat im = images[i];
//		vector<Point2f> im_p;           //在棋盘图像中找到内角点坐标，初始的二维点im_p
//		bool pattern_found = findChessboardCorners(im, Size(width, height), im_p, CALIB_CB_ADAPTIVE_THRESH + CALIB_CB_NORMALIZE_IMAGE + CALIB_CB_FAST_CHECK);
//		cout << "pattern_found:" << endl;
//		cout << pattern_found << endl;
//		if (pattern_found)
//		{
//			object_points.push_back(ob_p);//存放20个vector<Point3f>，每张图的20个点现在用不到
//										  //现在用不到，是物体的坐标，不是图像
//			Mat gray;
//			cvtColor(im, gray, CV_BGR2GRAY);//亚像素级角点检测，提高精度im_p，输出im_p		
//			cornerSubPix(gray, im_p, Size(5, 5), Size(-1, -1), TermCriteria(CV_TERMCRIT_EPS + CV_TERMCRIT_ITER, 30, 0.1));
//
//			image_points.push_back(im_p);
//
//			if (show)
//			{
//				Mat im_show = im.clone();      //第二个参数patternSize，每张标定棋盘上内角点的行列数
//				drawChessboardCorners(im_show, Size(width, height), im_p, true);
//				imshow("Chessboard corners", im_show);
//				while (char(waitKey(1)) != '\r') //按回车跳出，进行下一张图片
//				{
//					cout << "等待回车" << endl;
//				}
//			}
//		}
//		else{ 
//			cout << "删除图接口" << endl;
//			images.erase(images.begin() + i);//如果图片无效找不到角点，删除vector中这个图片的接口
//		}
//	}
//}
//
//void calibrator::calibrate()
//{
//	//vector<Mat> rvecs, tvecs;
//	float rms_error = calibrateCamera(object_points, image_points, images[0].size(),
//		cameraMatrix, distCoeffs, rvecs, tvecs);
//	//第一个参数：objectPoints，为世界坐标系中的三维点：vector<vector<Point3f>> object_points，
//	//需要依据棋盘上单个黑白矩阵的大小，计算出（初始化）每一个内角点的世界坐标。
//	//长100*宽75
//	//第二个参数：imagePoints，为每一个内角点对应的图像坐标点：vector<vector<Point2f>> image_points
//	//第三个参数：imageSize，为图像的像素尺寸大小
//	//第四个参数：cameraMatrix为相机的内参矩阵：Mat cameraMatrix=Mat(3,3,CV_32FC1,Scalar::all(0));
//	//第五个参数：distCoeffs为畸变矩阵Mat distCoeffs=Mat(1,5,CV_32FC1,Scalar::all(0));
//
//	//内参数矩阵 M=[fx γ u0,0 fy v0,0 0 1]
//	//外参矩阵  5个畸变系数k1,k2,p1,p2,k3
//
//
//
//	//第六个参数：rvecs旋转向量R，vector<Mat> tvecs;
//	//第七个参数：tvecs位移向量T，和rvecs一样，应该为vector<Mat> tvecs;
//	//第八个参数：flags为标定时所采用的算法  第九个参数：criteria是最优迭代终止条件设定。
//	//return：重投影的总的均方根误差。
//
//	//总结：得到相机内参矩阵K、相机的5个畸变系数、每张图片属于自己的平移向量T、旋转向量R
//	cout << "重投影的总的均方根误差：" << rms_error << endl;
//}
//
//Mat calibrator::get_cameraMatrix()
//{
//	return cameraMatrix;
//}
//
//Mat calibrator::get_distCoeffs()
//{
//	return distCoeffs;
//}
//
//void calibrator::get_error()
//{
//	double total_err = 0.0;   //所有图像的平均误差的总和 
//	double err = 0.0;    //每幅图像的平均误差 
//
//	vector<Point2f> image_points2; // 保存重新计算得到的投影点
//	cout << "\t每幅图像的标定误差：\n" << endl;
//	for (int i = 0;i < images.size(); i++)
//	{
//		vector<Point3f> tempPointSet = object_points[i];
//
//		//通过得到的摄像机内外参数，对空间的三维点进行重新投影计算，得到新的投影点
//		projectPoints(tempPointSet, rvecs[i], tvecs[i], cameraMatrix, distCoeffs, image_points2);
//
//		// 计算新的投影点和旧的投影点之间的误差
//		vector<Point2f> tempImagePoint = image_points[i];
//
//		Mat tempImagePointMat = Mat(1, tempImagePoint.size(), CV_32FC2); //cornerSubPix
//		Mat image_points2Mat = Mat(1, image_points2.size(), CV_32FC2);   //projectPoints
//
//		//对标定结果进行评价
//		for (int j = 0; j < tempImagePoint.size(); j++)
//		{                                                               // //分别给两个角点坐标赋值他x，y坐标
//			image_points2Mat.at<Vec2f>(0, j) = Vec2f(image_points2[j].x, image_points2[j].y);
//			tempImagePointMat.at<Vec2f>(0, j) = Vec2f(tempImagePoint[j].x, tempImagePoint[j].y);
//		}
//		//norm计算数组src1和src2的相对差范数
//		err = norm(image_points2Mat, tempImagePointMat, NORM_L2);
//		total_err += err;
//		std::cout << "第" << i + 1 << "幅图像的平均误差：" << err << "像素" << endl;
//	}
//
//	std::cout << "总体的平均误差：" << total_err / images.size() << "像素" << endl;
//}
//
//
////查看标定效果——利用标定结果对棋盘图进行矫正
//void calibrator::Correct_image()
//{
//
//	Mat mapx = Mat(images[0].size(), CV_32FC1);
//	Mat mapy = Mat(images[0].size(), CV_32FC1);
//	Mat R = Mat::eye(3, 3, CV_32F);      //单位矩阵
//		//计算出对应的映射表
//	initUndistortRectifyMap(cameraMatrix, distCoeffs, R, cameraMatrix, images[0].size(), CV_32FC1, mapx, mapy);
//	//第三个参数R，可选的输入，是第一和第二相机坐标之间的旋转矩阵；
//	//第四个参数newCameraMatrix，输入的校正后的3X3摄像机矩阵；
//	//第五个参数size，摄像机采集的无失真的图像尺寸；
//	//第六个参数m1type，定义map1的数据类型，可以是CV_32FC1或者CV_16SC2；
//	//第七个参数map1和第八个参数map2，输出的X / Y坐标重映射参数；
//
//	for (int i = 0; i != images.size(); i++)
//	{
//		Mat imageSource = images[i];
//		Mat newimage = images[i].clone();
//		Mat newimage1 = images[i].clone();
//
//		//方法一：使用initUndistortRectifyMap和remap两个函数配合实现。
//		//initUndistortRectifyMap用来计算畸变映射，remap把求得的映射应用到图像上。
//
//
//
//		remap(imageSource, newimage, mapx, mapy, INTER_LINEAR);
//		//第五个参数interpolation，定义图像的插值方式；
//		//第六个参数borderMode，定义边界填充方式；
//
//		//方法二：使用undistort函数实现
//		undistort(imageSource, newimage1, cameraMatrix, distCoeffs);
//		//第五个参数newCameraMatrix，默认跟cameraMatrix保持一致；		
//
//		//输出图像
//		string str = "./img_remap/" + to_string(i + 1) + ".jpg";
//		string str1 = "./img_remap_undistort/" + to_string(i + 1) + ".jpg";
//		//string str = "d:\\" + to_string(i + 1) + ".jpg";
//		imwrite(str, newimage);
//		imwrite(str1, newimage1);
//	}
//
//
//
//}
