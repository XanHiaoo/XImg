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
	 * @brief XImgToMat  XImg 转换为cv::Mat 将内部Mat数据深拷贝
	 * @return 拷贝后的cv::Mat
	 */
	static cv::Mat XImgToMat(XImg image);

	/**
	 * @brief GetMatFromXImg 获取XImg中的Mat 仅获取Mat数据头 浅拷贝
	 * @return Mat对象
	 */
	static const cv::Mat GetMatFromXImg(XImg& image);

	/**
	 * @brief MatToXImg cv::Mat 转换为 XImg 将源图像数据深拷贝到 XImg内部的Mat
	 * @return 拷贝后的XImg
	 */
	static XImg MatToXImg(cv::Mat mat);
#else
	
#endif

};

#endif // XIMGEXPORTMAT_H
