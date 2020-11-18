#include<opencv2/opencv.hpp>
#include<iostream>
#include<cmath>
using namespace cv;
using namespace std;

int main()
{
	cv::Mat srcMat = imread("C:\\Users\\Lenovo\\Pictures\\数图\\车轮.png",0); //转灰度图
	cv::Mat dstMat = imread("C:\\Users\\Lenovo\\Pictures\\数图\\车轮.png");
	cv::Mat binary,binary_i;
	cv::Mat DilationImage,close;
	cv::Mat element1,element2;//结构算子
	int Kernelsize1 = 3, Kernelsize2 = 15;

	
	
	element1 = getStructuringElement(MORPH_ELLIPSE, Size(Kernelsize1, Kernelsize1));
	element2 = getStructuringElement(MORPH_ELLIPSE, Size(Kernelsize2, Kernelsize2));

	std::vector<vector<Point>> contours;//输出保存轮廓的向量


	threshold(srcMat, binary, 105,255, THRESH_BINARY);//二值化

	binary_i = 255 - binary;//二值化图像反色

	dilate(binary_i, DilationImage, element1); //膨胀

	morphologyEx(DilationImage, close, 3, element2); //闭运算

	findContours(close, contours, CV_RETR_TREE, CV_CHAIN_APPROX_NONE);//检测最外围轮廓	
	//绘制轮廓及最小外接四边形
	for (int i = 0; i < contours.size(); i++)
	{
		//获得最小外接四边形
		RotatedRect rbox = minAreaRect(contours[i]);
		
		if (rbox.size.width > 30 && rbox.size.height > 30) //规定最小外接四边形宽、高大于30
		{
			if (abs(rbox.size.width - rbox.size.height) <1.5) //规定最小外接四边形宽、高相差小（因为是检测正圆形）
			{
				//绘制轮廓线
				drawContours(dstMat, contours, i, Scalar(0, 255, 255), -1, 8);//当thickness小于0时，轮廓内部被填充

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
		
	}
	
	
	imshow("原图", srcMat);
	imshow("二值化图", binary);
	imshow("膨胀", DilationImage);
	imshow("闭运算", close);
	imshow("检测结果", dstMat);

	waitKey(0);




}