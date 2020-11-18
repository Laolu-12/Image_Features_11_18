#include<opencv2/opencv.hpp>
#include<iostream>
#include<cmath>
using namespace cv;
using namespace std;

int main()
{
	cv::Mat srcMat = imread("C:\\Users\\Lenovo\\Pictures\\��ͼ\\оƬ.jpg", 0); //ת�Ҷ�ͼ
	cv::Mat dstMat = imread("C:\\Users\\Lenovo\\Pictures\\��ͼ\\оƬ.jpg");
	cv::Mat binary;
	cv::Mat element;
	cv::Mat close;
	int Kernelsize = 2;

	std::vector<vector<Point>> contours;//�����������������

	element = getStructuringElement(MORPH_RECT, Size(Kernelsize, Kernelsize));


	threshold(srcMat, binary, 160, 255, THRESH_BINARY);//��ֵ��

	morphologyEx(binary, close, 3, element); //������

	findContours(close, contours, CV_RETR_TREE, CV_CHAIN_APPROX_NONE);//�������Χ����
	//������������С����ı���
	for (int i = 0; i < contours.size(); i++)
	{
		//�����С����ı���
		RotatedRect rbox = minAreaRect(contours[i]);

		if (rbox.size.width > 40 && rbox.size.height > 40) //�涨��С����ı��ο��ߴ���40
		{			
				//����������
				drawContours(dstMat, contours, i, Scalar(0, 255, 255), 1, 8);

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
	imshow("ԭͼ", srcMat);
	imshow("��ֵ��ͼ", binary);
	imshow("������", close);
	imshow("�����", dstMat);
	waitKey(0);

}