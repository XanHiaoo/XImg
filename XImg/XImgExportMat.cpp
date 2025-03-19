#include "XImgExportMat.h"
#include "XImgImpl.h"

#ifdef OPENCV_ENABLED
cv::Mat XImgExportMat::XImgToMat(XImg image)
{
	if (image.isEmpty())
	{
		return cv::Mat();  
	}

	// 直接访问 XImgImpl 数据
	int width = image.xImgImpl->width;
	int height = image.xImgImpl->height;
	XImgImpl::DataFormat format = image.xImgImpl->format;
	const std::vector<unsigned char>& data = image.xImgImpl->imageData;

	cv::Mat mat;
	if (format == XImgImpl::xFormat_Grayscale8)
	{
		mat = cv::Mat(height, width, CV_8UC1, (void*)data.data());
	}
	else if (format == XImgImpl::xFormat_RGB888)
	{
		mat = cv::Mat(height, width, CV_8UC3, (void*)data.data());
	}
	else if (format == XImgImpl::xFormat_BGR888)
	{
		mat = cv::Mat(height, width, CV_8UC3, (void*)data.data());
	}
	else if (format == XImgImpl::xFormat_RGBA32)
	{
		mat = cv::Mat(height, width, CV_8UC4, (void*)data.data());
	}
	else if (format == XImgImpl::xFormat_BGRA32)
	{
		mat = cv::Mat(height, width, CV_8UC4, (void*)data.data());
	}

	return mat.clone();  // 返回深拷贝的 Mat 对象
}

const cv::Mat XImgExportMat::GetMatFromXImg(XImg& image)
{
	if (image.isEmpty())
	{
		static cv::Mat emptyMat;
		return emptyMat;  // 返回一个空 Mat（静态变量，避免临时对象销毁）
	}

	int width = image.xImgImpl->width;
	int height = image.xImgImpl->height;
	XImgImpl::DataFormat format = image.xImgImpl->format;
	unsigned char* data = image.xImgImpl->imageData.data();

	// 创建 Mat（浅拷贝，不使用 clone）
	if (format == XImgImpl::xFormat_Grayscale8)
	{
		return cv::Mat(height, width, CV_8UC1, data);
	}
	else if (format == XImgImpl::xFormat_RGB888 || format == XImgImpl::xFormat_BGR888)
	{
		return cv::Mat(height, width, CV_8UC3, data);
	}
	else if (format == XImgImpl::xFormat_RGBA32 || format == XImgImpl::xFormat_BGRA32)
	{
		return cv::Mat(height, width, CV_8UC4, data);
	}

	static cv::Mat emptyMat;
	return emptyMat;  // 默认返回空 Mat
}

XImg XImgExportMat::MatToXImg(cv::Mat mat)
{
	// 将 cv::Mat 转换为 XImg 并深拷贝数据
	XImgImpl::DataFormat format;
	int channels = mat.channels();

	if (channels == 1)
	{
		format = XImgImpl::xFormat_Grayscale8;
	}
	else if (channels == 3)
	{
		format = XImgImpl::xFormat_RGB888;
	}
	else if (channels == 4)
	{
		format = XImgImpl::xFormat_RGBA32;
	}
	else
	{
		// Unsupported format
		format = XImgImpl::xFormat_Invalid;
	}

	int width = mat.cols;
	int height = mat.rows;
	std::vector<unsigned char> data(mat.total() * mat.elemSize());
	std::memcpy(data.data(), mat.data, data.size());

	// 创建 XImg 并设置数据
	XImg img;
	img.xImgImpl->loadImage(data.data(), width, height, format);

	return img;  // 返回深拷贝的 XImg 对象
}
#else

#endif