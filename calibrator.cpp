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
//	cout << "ͼƬ��λ�ã�" << pattern << endl;
//
//	//std::string pattern = "./img/*.jpg";
//	std::vector<cv::String>image_file;
//
//	glob(pattern, image_file);
//	cout << "ͼƬ����:"<< endl;
//	cout << image_file.size() << endl;
//	for (int i = 0;i < image_file.size();i++)
//	{
//		images.push_back(imread(image_file[i]));
//	}
//
//}
//
//void calibrator::calc_image_points(bool show)  //�����ڽǵ�
//{
//	cout << "�ڽǵ����" << endl;
//	//������������ϵ�е������(���Ͻ�ԭ��)
//	vector<Point3f> ob_p;        //�����ڽǵ��������20����
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
//	cout << "��ʼѭ������" << endl;
//	for (int i = 0; i < images.size(); i++)
//	{
//		cout << "ͼ����i:" << endl;
//		cout << i << endl;
//		Mat im = images[i];
//		vector<Point2f> im_p;           //������ͼ�����ҵ��ڽǵ����꣬��ʼ�Ķ�ά��im_p
//		bool pattern_found = findChessboardCorners(im, Size(width, height), im_p, CALIB_CB_ADAPTIVE_THRESH + CALIB_CB_NORMALIZE_IMAGE + CALIB_CB_FAST_CHECK);
//		cout << "pattern_found:" << endl;
//		cout << pattern_found << endl;
//		if (pattern_found)
//		{
//			object_points.push_back(ob_p);//���20��vector<Point3f>��ÿ��ͼ��20���������ò���
//										  //�����ò���������������꣬����ͼ��
//			Mat gray;
//			cvtColor(im, gray, CV_BGR2GRAY);//�����ؼ��ǵ��⣬��߾���im_p�����im_p		
//			cornerSubPix(gray, im_p, Size(5, 5), Size(-1, -1), TermCriteria(CV_TERMCRIT_EPS + CV_TERMCRIT_ITER, 30, 0.1));
//
//			image_points.push_back(im_p);
//
//			if (show)
//			{
//				Mat im_show = im.clone();      //�ڶ�������patternSize��ÿ�ű궨�������ڽǵ��������
//				drawChessboardCorners(im_show, Size(width, height), im_p, true);
//				imshow("Chessboard corners", im_show);
//				while (char(waitKey(1)) != '\r') //���س�������������һ��ͼƬ
//				{
//					cout << "�ȴ��س�" << endl;
//				}
//			}
//		}
//		else{ 
//			cout << "ɾ��ͼ�ӿ�" << endl;
//			images.erase(images.begin() + i);//���ͼƬ��Ч�Ҳ����ǵ㣬ɾ��vector�����ͼƬ�Ľӿ�
//		}
//	}
//}
//
//void calibrator::calibrate()
//{
//	//vector<Mat> rvecs, tvecs;
//	float rms_error = calibrateCamera(object_points, image_points, images[0].size(),
//		cameraMatrix, distCoeffs, rvecs, tvecs);
//	//��һ��������objectPoints��Ϊ��������ϵ�е���ά�㣺vector<vector<Point3f>> object_points��
//	//��Ҫ���������ϵ����ڰ׾���Ĵ�С�����������ʼ����ÿһ���ڽǵ���������ꡣ
//	//��100*��75
//	//�ڶ���������imagePoints��Ϊÿһ���ڽǵ��Ӧ��ͼ������㣺vector<vector<Point2f>> image_points
//	//������������imageSize��Ϊͼ������سߴ��С
//	//���ĸ�������cameraMatrixΪ������ڲξ���Mat cameraMatrix=Mat(3,3,CV_32FC1,Scalar::all(0));
//	//�����������distCoeffsΪ�������Mat distCoeffs=Mat(1,5,CV_32FC1,Scalar::all(0));
//
//	//�ڲ������� M=[fx �� u0,0 fy v0,0 0 1]
//	//��ξ���  5������ϵ��k1,k2,p1,p2,k3
//
//
//
//	//������������rvecs��ת����R��vector<Mat> tvecs;
//	//���߸�������tvecsλ������T����rvecsһ����Ӧ��Ϊvector<Mat> tvecs;
//	//�ڰ˸�������flagsΪ�궨ʱ�����õ��㷨  �ھŸ�������criteria�����ŵ�����ֹ�����趨��
//	//return����ͶӰ���ܵľ�������
//
//	//�ܽ᣺�õ�����ڲξ���K�������5������ϵ����ÿ��ͼƬ�����Լ���ƽ������T����ת����R
//	cout << "��ͶӰ���ܵľ�������" << rms_error << endl;
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
//	double total_err = 0.0;   //����ͼ���ƽ�������ܺ� 
//	double err = 0.0;    //ÿ��ͼ���ƽ����� 
//
//	vector<Point2f> image_points2; // �������¼���õ���ͶӰ��
//	cout << "\tÿ��ͼ��ı궨��\n" << endl;
//	for (int i = 0;i < images.size(); i++)
//	{
//		vector<Point3f> tempPointSet = object_points[i];
//
//		//ͨ���õ������������������Կռ����ά���������ͶӰ���㣬�õ��µ�ͶӰ��
//		projectPoints(tempPointSet, rvecs[i], tvecs[i], cameraMatrix, distCoeffs, image_points2);
//
//		// �����µ�ͶӰ��;ɵ�ͶӰ��֮������
//		vector<Point2f> tempImagePoint = image_points[i];
//
//		Mat tempImagePointMat = Mat(1, tempImagePoint.size(), CV_32FC2); //cornerSubPix
//		Mat image_points2Mat = Mat(1, image_points2.size(), CV_32FC2);   //projectPoints
//
//		//�Ա궨�����������
//		for (int j = 0; j < tempImagePoint.size(); j++)
//		{                                                               // //�ֱ�������ǵ����긳ֵ��x��y����
//			image_points2Mat.at<Vec2f>(0, j) = Vec2f(image_points2[j].x, image_points2[j].y);
//			tempImagePointMat.at<Vec2f>(0, j) = Vec2f(tempImagePoint[j].x, tempImagePoint[j].y);
//		}
//		//norm��������src1��src2����Բ��
//		err = norm(image_points2Mat, tempImagePointMat, NORM_L2);
//		total_err += err;
//		std::cout << "��" << i + 1 << "��ͼ���ƽ����" << err << "����" << endl;
//	}
//
//	std::cout << "�����ƽ����" << total_err / images.size() << "����" << endl;
//}
//
//
////�鿴�궨Ч���������ñ궨���������ͼ���н���
//void calibrator::Correct_image()
//{
//
//	Mat mapx = Mat(images[0].size(), CV_32FC1);
//	Mat mapy = Mat(images[0].size(), CV_32FC1);
//	Mat R = Mat::eye(3, 3, CV_32F);      //��λ����
//		//�������Ӧ��ӳ���
//	initUndistortRectifyMap(cameraMatrix, distCoeffs, R, cameraMatrix, images[0].size(), CV_32FC1, mapx, mapy);
//	//����������R����ѡ�����룬�ǵ�һ�͵ڶ��������֮�����ת����
//	//���ĸ�����newCameraMatrix�������У�����3X3���������
//	//���������size��������ɼ�����ʧ���ͼ��ߴ磻
//	//����������m1type������map1���������ͣ�������CV_32FC1����CV_16SC2��
//	//���߸�����map1�͵ڰ˸�����map2�������X / Y������ӳ�������
//
//	for (int i = 0; i != images.size(); i++)
//	{
//		Mat imageSource = images[i];
//		Mat newimage = images[i].clone();
//		Mat newimage1 = images[i].clone();
//
//		//����һ��ʹ��initUndistortRectifyMap��remap�����������ʵ�֡�
//		//initUndistortRectifyMap�����������ӳ�䣬remap����õ�ӳ��Ӧ�õ�ͼ���ϡ�
//
//
//
//		remap(imageSource, newimage, mapx, mapy, INTER_LINEAR);
//		//���������interpolation������ͼ��Ĳ�ֵ��ʽ��
//		//����������borderMode������߽���䷽ʽ��
//
//		//��������ʹ��undistort����ʵ��
//		undistort(imageSource, newimage1, cameraMatrix, distCoeffs);
//		//���������newCameraMatrix��Ĭ�ϸ�cameraMatrix����һ�£�		
//
//		//���ͼ��
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
