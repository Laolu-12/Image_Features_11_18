#include<opencv2/opencv.hpp>
#include<iostream>
#include<cmath>
using namespace cv;
using namespace std;

int main()
{
	double scale = 0.2;
	//��ɫ��HSV��Χ
	int i_minH = 156;
	int i_maxH = 180;

	int i_minS = 43;
	int i_maxS = 255;

	int i_minV = 46;
	int i_maxV = 255;


	cv::Mat srcMat = imread("C:\\Users\\Lenovo\\Pictures\\��ͼ\\ƿ��.jpg"); 
	cv::Mat dstMat;
	cv::Mat hsvMat;
	cv::Mat binary;
	cv::Mat DilationImage;
	cv::Mat element;
	int Kernelsize = 7;
	std::vector<vector<Point>> contours;//�����������������

	/*
	//Hue (0 - 179)
	cvCreateTrackbar("LowH", "Control", &i_minH, 179);
	cvCreateTrackbar("HighH", "Control", &i_maxH, 179);
	//Saturation (0 - 255)
	cvCreateTrackbar("LowS", "Control", &i_minS, 255);
	cvCreateTrackbar("HighS", "Control", &i_maxS, 255);
	//Value (0 - 255)
	cvCreateTrackbar("LowV", "Control", &i_minV, 255);
	cvCreateTrackbar("HighV", "Control", &i_maxV, 255);
	*/

	element = getStructuringElement(MORPH_RECT, Size(Kernelsize, Kernelsize));//�ṹ����

	//����
	Size ResImgSiz = Size(srcMat.cols*scale, srcMat.rows*scale);
	cv::Mat minMat = Mat(ResImgSiz, srcMat.type());
	resize(srcMat, minMat, ResImgSiz, INTER_LINEAR);

	minMat.copyTo(dstMat);

	cvtColor(minMat, hsvMat, COLOR_BGR2HSV);

	inRange(hsvMat, Scalar(i_minH, i_minS, i_minV), Scalar(i_maxH, i_maxS, i_maxV), binary); //��ֵ��

	dilate(binary, DilationImage, element); //����


	findContours(DilationImage, contours, CV_RETR_TREE, CV_CHAIN_APPROX_NONE);//�������Χ����
	//������������С����ı���
	for (int i = 0; i < contours.size(); i++)
	{
		//�����С����ı���
		RotatedRect rbox = minAreaRect(contours[i]);

		if (rbox.size.width > 40 && rbox.size.height > 40) //�涨��С����ı��ο��ߴ���40
		{
			//����������
			//drawContours(dstMat, contours, i, Scalar(0, 255, 255), 1, 8);

			//������С����ı���
			cv::Point2f vtx[4];
			std::cout << rbox.size << std::endl; //��ӡ��С����ı��γߴ�
			rbox.points(vtx); //������ı����ĸ��㸳ֵ��vtx
			for (int j = 0; j < 4; ++j)
			{
				cv::line(dstMat, vtx[j], vtx[j < 3 ? j + 1 : 0], cv::Scalar(0, 0, 255), 2, CV_AA); //�����㻭�� ���ɾ���
			}

		}
	}

	imshow("ԭͼ", minMat);
	imshow("��ֵ��", binary);
	imshow("����", DilationImage);
	imshow("�����", dstMat);
	waitKey(0);

}