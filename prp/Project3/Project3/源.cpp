#include "stdafx.h"
#include <opencv2/opencv.hpp>

using namespace cv;

int main()
{
	Mat srcImage = imread("C:\Users\53168\Desktop\3.jpg");

	imshow("Ô­Í¼Ïñ", srcImage);
	Mat dstImage;
	Mat element = getStructuringElement(MORPH_RECT, Size(10, 10));
	dilate(srcImage, dstImage, element);
	imshow("Ð§¹ûÍ¼", dstImage);
	waitKey(0);
}

