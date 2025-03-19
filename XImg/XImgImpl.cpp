#include "XImgImpl.h"
#include <cstring>

XImgImpl::XImgImpl() : width(0), height(0), format(xFormat_Invalid) {}

XImgImpl::XImgImpl(const unsigned char *data, int width, int height, XImgImpl::DataFormat format, int bytesPerLine)
	: width(width), height(height), format(format)
{
	if (data && width > 0 && height > 0)
	{
		int bytesPerPixel = getBytesPerPixel(format);
		if (bytesPerPixel == 0)
		{
			return;  // 不支持的格式
		}

		int effectiveBytesPerLine = (bytesPerLine > 0) ? bytesPerLine : width * bytesPerPixel;
		int dataSize = effectiveBytesPerLine * height;

		imageData.resize(dataSize);
		std::memcpy(imageData.data(), data, dataSize);
	}
}

XImgImpl::XImgImpl(const XImgImpl &impl)
	: shootChannel(impl.shootChannel),
	shootCamera(impl.shootCamera),
	shootView(impl.shootView),
	errorInfoStr(impl.errorInfoStr),
	imageData(impl.imageData),
	width(impl.width),
	height(impl.height),
	format(impl.format)
{
}

XImgImpl::~XImgImpl() {}

bool XImgImpl::loadImage(const unsigned char *data, int width, int height, XImgImpl::DataFormat format, int bytesPerLine)
{
	if (!data || width <= 0 || height <= 0)
	{
		return false;
	}

	int bytesPerPixel = getBytesPerPixel(format);
	if (bytesPerPixel == 0)
	{
		return false;  // 不支持的格式
	}

	int effectiveBytesPerLine = (bytesPerLine > 0) ? bytesPerLine : width * bytesPerPixel;
	int requiredSize = effectiveBytesPerLine * height;

	// 检查数据大小是否合法
	if (std::strlen(reinterpret_cast<const char *>(data)) < requiredSize)
	{
		return false;
	}

	imageData.resize(requiredSize);
	std::memcpy(imageData.data(), data, requiredSize);

	return true;
}

bool XImgImpl::isEmpty()
{
	return imageData.empty();
}

XImgImpl &XImgImpl::operator=(const XImgImpl &impl)
{
	if (this != &impl)
	{
		shootChannel = impl.shootChannel;
		shootCamera = impl.shootCamera;
		shootView = impl.shootView;
		errorInfoStr = impl.errorInfoStr;

		width = impl.width;
		height = impl.height;
		format = impl.format;

		imageData = impl.imageData;
	}
	return *this;
}

XImgImpl XImgImpl::clone()
{
	return *this;
}

bool XImgImpl::setShootChannel(const std::string &channel)
{
	shootChannel = channel;
	return true;
}

const std::string XImgImpl::getShootChannel()
{
	return shootChannel;
}

bool XImgImpl::setShootCamera(const std::string &camera)
{
	shootCamera = camera;
	return true;
}

const std::string XImgImpl::getShootCamera()
{
	return shootCamera;
}

const std::string XImgImpl::createShootViewCode(int cameraView, int productAngle)
{
	return "C" + std::to_string(cameraView) + "P" + std::to_string(productAngle);
}

bool XImgImpl::setShootView(const std::string &viewCode)
{
	shootView = viewCode;
	return true;
}

const std::string XImgImpl::getShootView()
{
	return shootView;
}

const std::string XImgImpl::errorInfo()
{
	return errorInfoStr;
}

int XImgImpl::getBytesPerPixel(XImgImpl::DataFormat format)
{
	switch (format)
	{
	case xFormat_Grayscale8:
		return 1;  
	case xFormat_RGB888:
	case xFormat_BGR888:
		return 3;  
	case xFormat_RGBA32:
	case xFormat_BGRA32:
		return 4;  
	default:
		return 0;  // 无效格式
	}
}