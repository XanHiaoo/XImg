/**
 * @file XImg.h
 * @brief XImg 图像处理类头文件
 *
 * 该文件定义了 XImg 类，用于管理、加载、转换和处理图像数据。
 * 该类支持多种常见图像格式，并提供相关操作接口，如拷贝、克隆、
 * 视图管理、通道管理等功能。
 *
 * @date 2025-03-03
 * @version 1.0.0
 */


#ifndef XIMG_H
#define XIMG_H

#include <string>
#include <memory>
#include <vector>

class XImgExportMat;
class XImgExportQImage;

#ifdef XIMG_LIBRARY
#define XIMG_API __declspec(dllexport)
#else
#define XIMG_API __declspec(dllimport)
#endif

/**
 * @class XImg
 * @brief 提供图像数据的管理、加载、转换及相关信息的操作。
 *
 * 该类用于表示和处理图像数据，支持不同格式的图像存储，并提供加载、复制、转换等操作。
 */
class XIMG_API XImg
{
	friend class XImgExportMat;
	friend class XImgExportQImage;

public:
	/**
	 * @enum DataFormat
	 * @brief 图像数据格式枚举类型。
	 *
	 * 包括了常见的图像格式，用于指定图像数据的存储格式。
	 */
	enum DataFormat
	{
		xFormat_Invalid = 0, ///< 无效的格式
		xFormat_Grayscale8 = 1, ///< 灰度8位图像
		xFormat_RGB888 = 2, ///< RGB格式，8位每通道
		xFormat_BGR888 = 3, ///< BGR格式，8位每通道
		xFormat_RGBA32 = 4, ///< RGBA格式，32位
		xFormat_BGRA32 = 5 ///< BGRA格式，32位
	};

	/**
	 * @brief 默认构造函数。
	 *
	 * 初始化一个空的 XImg 对象。
	 */
	XImg();

	/**
	 * @brief 带数据的构造函数。
	 *
	 * @param data 图像数据指针
	 * @param width 图像宽度
	 * @param height 图像高度
	 * @param format 图像数据格式
	 * @param bytesPerLine 每行的字节数，默认0
	 */
	XImg(const unsigned char *data, int width, int height, XImg::DataFormat format, int bytesPerLine = 0);

	/**
	 * @brief 拷贝构造函数。
	 *
	 * @param img 要拷贝的图像对象
	 */
	XImg(const XImg &img);

	/**
	 * @brief 析构函数。
	 * 释放内部资源。
	 */
	~XImg();

	/**
	 * @brief 加载图像数据。
	 *
	 * @param data 图像数据指针
	 * @param width 图像宽度
	 * @param height 图像高度
	 * @param format 图像数据格式
	 * @param bytesPerLine 每行的字节数，默认0
	 *
	 * @return 加载成功返回true，否则返回false。
	 */
	bool loadImage(const unsigned char *data, int width, int height, XImg::DataFormat format, int bytesPerLine = 0);

	/**
	* @brief 判断图像是否为空。
	*
	* @return 如果图像为空，返回true；否则返回false。
	*/
	bool isEmpty();

	/**
	 * @brief 赋值操作符。
	 *
	 * @param img 赋值的源图像对象
	 *
	 * @return 返回赋值后的图像对象。
	 */
	XImg &operator= (const XImg &img);

	/**
	 * @brief 克隆当前图像对象。
	 *
	 * @return 返回克隆的图像对象。
	 */
	XImg clone();

	/**
	 * @brief 设置拍摄的通道。
	 *
	 * @param channel 通道标识符
	 *
	 * @return 设置是否成功。
	 */
	bool setShootChannel(const std::string &channel);

	/**
	 * @brief 获取拍摄的通道。
	 *
	 * @return 拍摄通道的标识符。
	 */
	const std::string getShootChannel();

	/**
	 * @brief 设置拍摄的相机。
	 *
	 * @param camera 相机标识符
	 *
	 * @return 设置是否成功。
	 */
	bool setShootCamera(const std::string &camera);

	/**
	 * @brief 获取拍摄的相机。
	 *
	 * @return 拍摄相机的标识符。
	 */
	const std::string getShootCamera();

	/**
	 * @brief 创建拍摄视图代码。
	 *
	 * 根据相机视角和产品角度生成一个视图代码。
	 *
	 * @param cameraView 相机视角（默认0）
	 * @param productAngle 产品角度（默认0）
	 *
	 * @return 生成的视图代码。
	 */
	static const std::string createShootViewCode(int cameraView = 0, int productAngle = 0);

	/**
	 * @brief 设置拍摄视图。
	 *
	 * @param viewCode 视图代码
	 *
	 * @return 设置是否成功。
	 */
	bool setShootView(const std::string &viewCode);

	/**
	 * @brief 获取拍摄视图。
	 *
	 * @return 拍摄视图的视图代码。
	 */
	const std::string getShootView();

	/**
	 * @brief 获取错误信息。
	 *
	 * @return 错误描述字符串。
	 */
	const std::string errorInfo();

private:
	std::unique_ptr<class XImgImpl> xImgImpl; 
};

#endif // XIMG_H
