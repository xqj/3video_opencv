
#include "calibrator.h"
using namespace cv;
/*
��������ͷ��׽
*/
int main(int argc, char** argv) {
    //��ʼ���������ݣ�����ͼƬ
    cout << "��ʼ���������ݣ�����ͼƬ" << endl;
    calibrator calib(IMAGE_FOLDER, 30.f, 7, 5);
    cout << "��ʼ���������ݽ���" << endl;
    //�����е�ͼƬ�Ľǵ������ҵ�     
    calib.calc_image_points(true);

    //�س��л���������ͼ
    cout << "�������������......��ȴ�" << endl;

    //����궨����
    calib.calibrate();

    cout << "--------�궨���--------" << endl;

    //�Ա궨�����������
        //��������궨����õ���ÿ��ͼƬ��ת����ϵ��������ά��ת���ɶ�ά��
        //��֮ǰ�õ��Ľǵ��ά������жԱ�    ��ά--����ά
    calib.get_error();

    //�鿴�궨Ч���������ñ궨���������ͼ���н���
        //�����ڲκͻ���ϵ�����   �޻��������ת��ӳ��
        //ȥ����ͷ�����ͼ������
    calib.Correct_image();

    string filename =  string("cam_calib.xml");
    FileStorage fs(filename, FileStorage::WRITE);
    fs << "cameraMatrix" << calib.get_cameraMatrix();
    fs << "distCoeffs" << calib.get_distCoeffs();
    fs.release();
    cout << "���������������" << filename << endl;

    system("pause");
    return 0;

}