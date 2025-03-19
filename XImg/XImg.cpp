#include "XImg.h"
#include "XImgImpl.h"

XImg::XImg() : xImgImpl(std::make_unique<XImgImpl>()) {}

XImg::XImg(const unsigned char *data, int width, int height, XImg::DataFormat format, int bytesPerLine)
	: xImgImpl(std::make_unique<XImgImpl>(data, width, height, static_cast<XImgImpl::DataFormat>(format), bytesPerLine)) {}

XImg::XImg(const XImg &img) : xImgImpl(std::make_unique<XImgImpl>(*img.xImgImpl)) {}

XImg::~XImg() {}


bool XImg::loadImage(const unsigned char *data, int width, int height, XImg::DataFormat format, int bytesPerLine)
{
	return xImgImpl->loadImage(data, width, height, static_cast<XImgImpl::DataFormat>(format), bytesPerLine);
}

bool XImg::setShootChannel(const std::string &channel)
{
	return xImgImpl->setShootChannel(channel);
}

const std::string XImg::getShootChannel()
{
	return xImgImpl->getShootChannel();
}

bool XImg::setShootCamera(const std::string &camera)
{
	return xImgImpl->setShootCamera(camera);
}

const std::string XImg::getShootCamera()
{
	return xImgImpl->getShootCamera();
}

const std::string XImg::createShootViewCode(int cameraView, int productAngle)
{
	return XImgImpl::createShootViewCode(cameraView, productAngle);
}

bool XImg::setShootView(const std::string &viewCode)
{
	return xImgImpl->setShootView(viewCode);
}

const std::string XImg::getShootView()
{
	return xImgImpl->getShootView();
}

bool XImg::isEmpty()
{
	return xImgImpl->isEmpty();
}

XImg& XImg::operator= (const XImg &img)
{
	if (this != &img) {
		xImgImpl = std::make_unique<XImgImpl>(*img.xImgImpl);
	}
	return *this;
}

XImg XImg::clone()
{
	return XImg(*this);
}

const std::string XImg::errorInfo()
{
	return xImgImpl->errorInfo();
}
