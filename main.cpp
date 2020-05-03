
#include "calibrator.h"
using namespace cv;
/*
三个摄像头捕捉
*/
int main(int argc, char** argv) {
    //初始化棋盘数据，载入图片
    cout << "初始化棋盘数据，载入图片" << endl;
    calibrator calib(IMAGE_FOLDER, 30.f, 7, 5);
    cout << "初始化棋盘数据结束" << endl;
    //把所有的图片的角点坐标找到     
    calib.calc_image_points(true);

    //回车切换下张棋盘图
    cout << "计算相机参数中......请等待" << endl;

    //相机标定计算
    calib.calibrate();

    cout << "--------标定完成--------" << endl;

    //对标定结果进行评价
        //利用相机标定计算得到的每张图片的转换关系，将其三维点转换成二维点
        //和之前得到的角点二维坐标进行对比    三维--》二维
    calib.get_error();

    //查看标定效果——利用标定结果对棋盘图进行矫正
        //利用内参和畸变系数求出   无畸变和修正转换映射
        //去除镜头畸变的图像拉伸
    calib.Correct_image();

    string filename =  string("cam_calib.xml");
    FileStorage fs(filename, FileStorage::WRITE);
    fs << "cameraMatrix" << calib.get_cameraMatrix();
    fs << "distCoeffs" << calib.get_distCoeffs();
    fs.release();
    cout << "保存相机参数到：" << filename << endl;

    system("pause");
    return 0;

}