#include <iostream> 
#include <opencv2/core/core.hpp>  
#include <opencv2/highgui/highgui.hpp> 
#include <opencv2/imgproc/imgproc.hpp>
using namespace std;
void change(IplImage* src, int temp);
int delect(IplImage* src);
int main()
{
	IplImage* frame = cvLoadImage("C:\\Users\\53168\\Desktop\\3.jpg", 1);
	/*cvNamedWindow("Example", CV_WINDOW_AUTOSIZE); //�ڶ�������Ϊͼ�񴰿ڵ���ʾ��ʽ,Ϊ0ʱ�����ڴ�С����ͼƬ�ı�
	cvShowImage("Example", frame);   //��ʾͼƬ������
	cvWaitKey(0); //�ȴ���������Ϊ0����ʱ��һֱ�ȴ��û�����������oʱ��Ϊ�ȴ���ʱ��
	cvReleaseImage(&frame); //�ͷ�ͼƬ
	cvDestroyWindow("Example");*/
	int i = delect(frame);
	//cout << endl;
	cout << i << endl;
	//cout << 1;
	change(frame, i);
	cvNamedWindow("Example", CV_WINDOW_AUTOSIZE); //�ڶ�������Ϊͼ�񴰿ڵ���ʾ��ʽ,Ϊ0ʱ�����ڴ�С����ͼƬ�ı�
	cvShowImage("Example", frame);   //��ʾͼƬ������
	cvWaitKey(0); //�ȴ���������Ϊ0����ʱ��һֱ�ȴ��û�����������oʱ��Ϊ�ȴ���ʱ��
	cvReleaseImage(&frame); //�ͷ�ͼƬ
	cvDestroyWindow("Example");
	return 0;
}
int delect(IplImage* src)
{
	uchar iThrehold;
	try
	{
		int height = src->height;

		int width = src->width;
		cout << width << endl;
		cout << height << endl;
		int step = src->widthStep / sizeof(uchar);
		cout << step << endl;
		uchar* data = (uchar*)src->imageData;
		//cout << (int)data[(width-1)*step + 1];
		//cout <<(int)data[3];
		int iDiffRec = 0;
		int F[256] = { 0 }; //ֱ��ͼ����  		
		int iTotalGray = 0;//�Ҷ�ֵ��  		
		int iTotalPixel = 0;//��������  		
		uchar bt;//ĳ�������ֵ   		
		uchar iNewThrehold;
		uchar iMaxGrayValue = 0, iMinGrayValue = 255;
		uchar iMeanGrayValue1, iMeanGrayValue2;
		for (int i = 0; i < height; i++)
		{
			for (int j = 0; j < width; j++)
			{
				bt = data[i * step + j];
				if (bt < iMinGrayValue)
					iMinGrayValue = bt;
				if (bt > iMaxGrayValue)
					iMaxGrayValue = bt;
				F[bt]++;
			}
		}
		iThrehold = 0;

		iNewThrehold = (iMinGrayValue + iMaxGrayValue) / 2;

		iDiffRec = iMaxGrayValue - iMinGrayValue;
		for (int a = 0; (abs(iThrehold - iNewThrehold) > 0.5); a++) {
			iThrehold = iNewThrehold;
			for (int i = iMinGrayValue; i < iThrehold; i++)
			{

				iTotalGray += F[i] * i;
				iTotalPixel += F[i];

			}
			iMeanGrayValue1 = (uchar)(iTotalGray / iTotalPixel);
			iTotalPixel = 0;
			iTotalGray = 0;
			for (int j = iThrehold + 1; j < iMaxGrayValue; j++)

			{

				iTotalGray += F[j] * j;//F[]�洢ͼ����Ϣ  

				iTotalPixel += F[j];

			}
			iMeanGrayValue2 = (uchar)(iTotalGray / iTotalPixel);
			iNewThrehold = (iMeanGrayValue2 + iMeanGrayValue1) / 2;
			iDiffRec = abs(iMeanGrayValue2 - iMeanGrayValue1);
		}
	}
	catch (cv::Exception e)
	{

	}
	return iThrehold;
}
void change(IplImage* src, int temp)
{
	int height = src->height;

	int width = src->width;
	cout << width << endl;
	int step = src->widthStep / sizeof(uchar);
	cout << step << endl;
	uchar* data = (uchar*)src->imageData;
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width * (step / width); j++)
		{
			if (data[i * step + j] <= temp)
				*(uchar*)(src->imageData + i * src->widthStep + j) = 0;
			else
				*(uchar*)(src->imageData + i * src->widthStep + j) = 255;
		}
	}
}