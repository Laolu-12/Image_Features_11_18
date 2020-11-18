#include<opencv2/opencv.hpp>
#include<iostream>
#include<cmath>
using namespace cv;
using namespace std;

int main()
{
	double scale = 0.2;
	//红色的HSV范围
	int i_minH = 156;
	int i_maxH = 180;

	int i_minS = 43;
	int i_maxS = 255;

	int i_minV = 46;
	int i_maxV = 255;


	cv::Mat srcMat = imread("C:\\Users\\Lenovo\\Pictures\\数图\\瓶盖.jpg"); 
	cv::Mat dstMat;
	cv::Mat hsvMat;
	cv::Mat binary;
	cv::Mat DilationImage;
	cv::Mat element;
	int Kernelsize = 7;
	std::vector<vector<Point>> contours;//输出保存轮廓的向量

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

	element = getStructuringElement(MORPH_RECT, Size(Kernelsize, Kernelsize));//结构算子

	//缩放
	Size ResImgSiz = Size(srcMat.cols*scale, srcMat.rows*scale);
	cv::Mat minMat = Mat(ResImgSiz, srcMat.type());
	resize(srcMat, minMat, ResImgSiz, INTER_LINEAR);

	minMat.copyTo(dstMat);

	cvtColor(minMat, hsvMat, COLOR_BGR2HSV);

	inRange(hsvMat, Scalar(i_minH, i_minS, i_minV), Scalar(i_maxH, i_maxS, i_maxV), binary); //二值化

	dilate(binary, DilationImage, element); //膨胀


	findContours(DilationImage, contours, CV_RETR_TREE, CV_CHAIN_APPROX_NONE);//检测最外围轮廓
	//绘制轮廓及最小外接四边形
	for (int i = 0; i < contours.size(); i++)
	{
		//获得最小外接四边形
		RotatedRect rbox = minAreaRect(contours[i]);

		if (rbox.size.width > 40 && rbox.size.height > 40) //规定最小外接四边形宽、高大于40
		{
			//绘制轮廓线
			//drawContours(dstMat, contours, i, Scalar(0, 255, 255), 1, 8);

			//绘制最小外接四边形
			cv::Point2f vtx[4];
			std::cout << rbox.size << std::endl; //打印最小外界四边形尺寸
			rbox.points(vtx); //将外接四边形四个点赋值给vtx
			for (int j = 0; j < 4; ++j)
			{
				cv::line(dstMat, vtx[j], vtx[j < 3 ? j + 1 : 0], cv::Scalar(0, 0, 255), 2, CV_AA); //两两点画线 构成矩形
			}

		}
	}

	imshow("原图", minMat);
	imshow("二值化", binary);
	imshow("膨胀", DilationImage);
	imshow("检测结果", dstMat);
	waitKey(0);

}