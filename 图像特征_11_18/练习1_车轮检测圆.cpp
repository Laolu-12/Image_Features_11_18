#include<opencv2/opencv.hpp>
#include<iostream>
#include<cmath>
using namespace cv;
using namespace std;

int main()
{
	cv::Mat srcMat = imread("C:\\Users\\Lenovo\\Pictures\\��ͼ\\����.png",0); //ת�Ҷ�ͼ
	cv::Mat dstMat = imread("C:\\Users\\Lenovo\\Pictures\\��ͼ\\����.png");
	cv::Mat binary,binary_i;
	cv::Mat DilationImage,close;
	cv::Mat element1,element2;//�ṹ����
	int Kernelsize1 = 3, Kernelsize2 = 15;

	
	
	element1 = getStructuringElement(MORPH_ELLIPSE, Size(Kernelsize1, Kernelsize1));
	element2 = getStructuringElement(MORPH_ELLIPSE, Size(Kernelsize2, Kernelsize2));

	std::vector<vector<Point>> contours;//�����������������


	threshold(srcMat, binary, 105,255, THRESH_BINARY);//��ֵ��

	binary_i = 255 - binary;//��ֵ��ͼ��ɫ

	dilate(binary_i, DilationImage, element1); //����

	morphologyEx(DilationImage, close, 3, element2); //������

	findContours(close, contours, CV_RETR_TREE, CV_CHAIN_APPROX_NONE);//�������Χ����	
	//������������С����ı���
	for (int i = 0; i < contours.size(); i++)
	{
		//�����С����ı���
		RotatedRect rbox = minAreaRect(contours[i]);
		
		if (rbox.size.width > 30 && rbox.size.height > 30) //�涨��С����ı��ο��ߴ���30
		{
			if (abs(rbox.size.width - rbox.size.height) <1.5) //�涨��С����ı��ο������С����Ϊ�Ǽ����Բ�Σ�
			{
				//����������
				drawContours(dstMat, contours, i, Scalar(0, 255, 255), -1, 8);//��thicknessС��0ʱ�������ڲ������

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
		
	}
	
	
	imshow("ԭͼ", srcMat);
	imshow("��ֵ��ͼ", binary);
	imshow("����", DilationImage);
	imshow("������", close);
	imshow("�����", dstMat);

	waitKey(0);




}