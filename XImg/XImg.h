/**
 * @file XImg.h
 * @brief XImg ͼ������ͷ�ļ�
 *
 * ���ļ������� XImg �࣬���ڹ������ء�ת���ʹ���ͼ�����ݡ�
 * ����֧�ֶ��ֳ���ͼ���ʽ�����ṩ��ز����ӿڣ��翽������¡��
 * ��ͼ����ͨ������ȹ��ܡ�
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
 * @brief �ṩͼ�����ݵĹ������ء�ת���������Ϣ�Ĳ�����
 *
 * �������ڱ�ʾ�ʹ���ͼ�����ݣ�֧�ֲ�ͬ��ʽ��ͼ��洢�����ṩ���ء����ơ�ת���Ȳ�����
 */
class XIMG_API XImg
{
	friend class XImgExportMat;
	friend class XImgExportQImage;

public:
	/**
	 * @enum DataFormat
	 * @brief ͼ�����ݸ�ʽö�����͡�
	 *
	 * �����˳�����ͼ���ʽ������ָ��ͼ�����ݵĴ洢��ʽ��
	 */
	enum DataFormat
	{
		xFormat_Invalid = 0, ///< ��Ч�ĸ�ʽ
		xFormat_Grayscale8 = 1, ///< �Ҷ�8λͼ��
		xFormat_RGB888 = 2, ///< RGB��ʽ��8λÿͨ��
		xFormat_BGR888 = 3, ///< BGR��ʽ��8λÿͨ��
		xFormat_RGBA32 = 4, ///< RGBA��ʽ��32λ
		xFormat_BGRA32 = 5 ///< BGRA��ʽ��32λ
	};

	/**
	 * @brief Ĭ�Ϲ��캯����
	 *
	 * ��ʼ��һ���յ� XImg ����
	 */
	XImg();

	/**
	 * @brief �����ݵĹ��캯����
	 *
	 * @param data ͼ������ָ��
	 * @param width ͼ����
	 * @param height ͼ��߶�
	 * @param format ͼ�����ݸ�ʽ
	 * @param bytesPerLine ÿ�е��ֽ�����Ĭ��0
	 */
	XImg(const unsigned char *data, int width, int height, XImg::DataFormat format, int bytesPerLine = 0);

	/**
	 * @brief �������캯����
	 *
	 * @param img Ҫ������ͼ�����
	 */
	XImg(const XImg &img);

	/**
	 * @brief ����������
	 * �ͷ��ڲ���Դ��
	 */
	~XImg();

	/**
	 * @brief ����ͼ�����ݡ�
	 *
	 * @param data ͼ������ָ��
	 * @param width ͼ����
	 * @param height ͼ��߶�
	 * @param format ͼ�����ݸ�ʽ
	 * @param bytesPerLine ÿ�е��ֽ�����Ĭ��0
	 *
	 * @return ���سɹ�����true�����򷵻�false��
	 */
	bool loadImage(const unsigned char *data, int width, int height, XImg::DataFormat format, int bytesPerLine = 0);

	/**
	* @brief �ж�ͼ���Ƿ�Ϊ�ա�
	*
	* @return ���ͼ��Ϊ�գ�����true�����򷵻�false��
	*/
	bool isEmpty();

	/**
	 * @brief ��ֵ��������
	 *
	 * @param img ��ֵ��Դͼ�����
	 *
	 * @return ���ظ�ֵ���ͼ�����
	 */
	XImg &operator= (const XImg &img);

	/**
	 * @brief ��¡��ǰͼ�����
	 *
	 * @return ���ؿ�¡��ͼ�����
	 */
	XImg clone();

	/**
	 * @brief ���������ͨ����
	 *
	 * @param channel ͨ����ʶ��
	 *
	 * @return �����Ƿ�ɹ���
	 */
	bool setShootChannel(const std::string &channel);

	/**
	 * @brief ��ȡ�����ͨ����
	 *
	 * @return ����ͨ���ı�ʶ����
	 */
	const std::string getShootChannel();

	/**
	 * @brief ��������������
	 *
	 * @param camera �����ʶ��
	 *
	 * @return �����Ƿ�ɹ���
	 */
	bool setShootCamera(const std::string &camera);

	/**
	 * @brief ��ȡ����������
	 *
	 * @return ��������ı�ʶ����
	 */
	const std::string getShootCamera();

	/**
	 * @brief ����������ͼ���롣
	 *
	 * ��������ӽǺͲ�Ʒ�Ƕ�����һ����ͼ���롣
	 *
	 * @param cameraView ����ӽǣ�Ĭ��0��
	 * @param productAngle ��Ʒ�Ƕȣ�Ĭ��0��
	 *
	 * @return ���ɵ���ͼ���롣
	 */
	static const std::string createShootViewCode(int cameraView = 0, int productAngle = 0);

	/**
	 * @brief ����������ͼ��
	 *
	 * @param viewCode ��ͼ����
	 *
	 * @return �����Ƿ�ɹ���
	 */
	bool setShootView(const std::string &viewCode);

	/**
	 * @brief ��ȡ������ͼ��
	 *
	 * @return ������ͼ����ͼ���롣
	 */
	const std::string getShootView();

	/**
	 * @brief ��ȡ������Ϣ��
	 *
	 * @return ���������ַ�����
	 */
	const std::string errorInfo();

private:
	std::unique_ptr<class XImgImpl> xImgImpl; 
};

#endif // XIMG_H
