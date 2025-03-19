#include "XImgExportMat.h"
#include "XImgImpl.h"

#ifdef OPENCV_ENABLED
cv::Mat XImgExportMat::XImgToMat(XImg image)
{
	if (image.isEmpty())
	{
		return cv::Mat();  
	}

	// ֱ�ӷ��� XImgImpl ����
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

	return mat.clone();  // ��������� Mat ����
}

const cv::Mat XImgExportMat::GetMatFromXImg(XImg& image)
{
	if (image.isEmpty())
	{
		static cv::Mat emptyMat;
		return emptyMat;  // ����һ���� Mat����̬������������ʱ�������٣�
	}

	int width = image.xImgImpl->width;
	int height = image.xImgImpl->height;
	XImgImpl::DataFormat format = image.xImgImpl->format;
	unsigned char* data = image.xImgImpl->imageData.data();

	// ���� Mat��ǳ��������ʹ�� clone��
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
	return emptyMat;  // Ĭ�Ϸ��ؿ� Mat
}

XImg XImgExportMat::MatToXImg(cv::Mat mat)
{
	// �� cv::Mat ת��Ϊ XImg ���������
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

	// ���� XImg ����������
	XImg img;
	img.xImgImpl->loadImage(data.data(), width, height, format);

	return img;  // ��������� XImg ����
}
#else

#endif