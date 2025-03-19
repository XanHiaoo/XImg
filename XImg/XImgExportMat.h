#ifndef XIMGEXPORTMAT_H
#define XIMGEXPORTMAT_H

#include "XImg.h"

#ifdef OPENCV_ENABLED
#include <opencv2/opencv.hpp>
#endif

class XIMG_API XImgExportMat
{
public:

#ifdef OPENCV_ENABLED
	/**
	 * @brief XImgToMat  XImg ת��Ϊcv::Mat ���ڲ�Mat�������
	 * @return �������cv::Mat
	 */
	static cv::Mat XImgToMat(XImg image);

	/**
	 * @brief GetMatFromXImg ��ȡXImg�е�Mat ����ȡMat����ͷ ǳ����
	 * @return Mat����
	 */
	static const cv::Mat GetMatFromXImg(XImg& image);

	/**
	 * @brief MatToXImg cv::Mat ת��Ϊ XImg ��Դͼ����������� XImg�ڲ���Mat
	 * @return �������XImg
	 */
	static XImg MatToXImg(cv::Mat mat);
#else
	
#endif

};

#endif // XIMGEXPORTMAT_H
