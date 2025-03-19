#ifndef XIMG_IMPL_H
#define XIMG_IMPL_H

#include <string>
#include <vector>

class XImgImpl
{
	friend class XImgExportMat;
	friend class XImgExportQImage;
public:
	enum DataFormat
	{
		xFormat_Invalid = 0,
		xFormat_Grayscale8 = 1,
		xFormat_RGB888 = 2,
		xFormat_BGR888 = 3,
		xFormat_RGBA32 = 4,
		xFormat_BGRA32 = 5
	};

	XImgImpl();
	XImgImpl(const unsigned char *data, int width, int height, XImgImpl::DataFormat format, int bytesPerLine = 0);
	XImgImpl(const XImgImpl &impl);
	~XImgImpl();

	bool loadImage(const unsigned char *data, int width, int height, XImgImpl::DataFormat format, int bytesPerLine = 0);
	bool isEmpty();
	XImgImpl &operator= (const XImgImpl &impl);
	XImgImpl clone();

	bool setShootChannel(const std::string &channel);
	const std::string getShootChannel();
	bool setShootCamera(const std::string &camera);
	const std::string getShootCamera();
	static const std::string createShootViewCode(int cameraView = 0, int productAngle = 0);
	bool setShootView(const std::string &viewCode);
	const std::string getShootView();
	
	const std::string errorInfo();

private:
	std::string shootChannel;
	std::string shootCamera;
	std::string shootView;
	std::string errorInfoStr;

	std::vector<unsigned char> imageData;  
	int width, height;
	DataFormat format;

private:
	int getBytesPerPixel(XImgImpl::DataFormat format);
};

#endif // XIMG_IMPL_H
