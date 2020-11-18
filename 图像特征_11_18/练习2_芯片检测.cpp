#include<opencv2/opencv.hpp>
#include<iostream>
#include<cmath>
using namespace cv;
using namespace std;

int main()
{
	cv::Mat srcMat = imread("C:\\Users\\Lenovo\\Pictures\\数图\\芯片.jpg", 0); //转灰度图
	cv::Mat dstMat = imread("C:\\Users\\Lenovo\\Pictures\\数图\\芯片.jpg");
	cv::Mat binary;
	cv::Mat element;
	cv::Mat close;
	int Kernelsize = 2;

	std::vector<vector<Point>> contours;//输出保存轮廓的向量

	element = getStructuringElement(MORPH_RECT, Size(Kernelsize, Kernelsize));


	threshold(srcMat, binary, 160, 255, THRESH_BINARY);//二值化

	morphologyEx(binary, close, 3, element); //闭运算

	findContours(close, contours, CV_RETR_TREE, CV_CHAIN_APPROX_NONE);//检测最外围轮廓
	//绘制轮廓及最小外接四边形
	for (int i = 0; i < contours.size(); i++)
	{
		//获得最小外接四边形
		RotatedRect rbox = minAreaRect(contours[i]);

		if (rbox.size.width > 40 && rbox.size.height > 40) //规定最小外接四边形宽、高大于40
		{			
				//绘制轮廓线
				drawContours(dstMat, contours, i, Scalar(0, 255, 255), 1, 8);

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
	imshow("原图", srcMat);
	imshow("二值化图", binary);
	imshow("闭运算", close);
	imshow("检测结果", dstMat);
	waitKey(0);

}