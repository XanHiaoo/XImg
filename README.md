# XImg - 自定义图像数据结构

## 简介

XImg 是一个图像处理类库，旨在提供一种通用的、自定义的图像数据结构，用于管理、加载、转换和处理图像数据。XImg 类支持多种常见的图像格式，并提供了一些操作接口，如图像拷贝、克隆、视图管理和通道管理等。此类库还支持与主流图像数据结构的互转，如 `cv::Mat` 和 `QImage`，便于与其他图像处理框架（如 OpenCV 和 Qt）集成。

## 功能

- **图像管理**: 提供图像数据的加载、复制、克隆等操作。
- **格式支持**: 支持多种常见图像格式，如灰度图像、RGB、BGR 和 RGBA 格式。
- **通道与视图管理**: 可设置和获取图像的拍摄通道、相机、视图信息等。
- **与其他图像结构互转**: 提供与 OpenCV (`cv::Mat`) 和 Qt (`QImage`) 之间的互转支持。

## 安装

1. 克隆本项目到本地：
   ```bash
   git clone https://github.com/XanHiaoo/XImg.git
   ```

1. 将本项目包含在你的 C++ 工程中，确保正确设置编译器的 include 路径以及链接路径。(忽略项目的属性配置表，需自行配置)

## 依赖

- **OpenCV**: 用于图像处理操作（可选），如果启用了 OpenCV 支持，XImg 可以与 OpenCV 的 `cv::Mat` 类型进行互转。
- **Qt**: 用于图像显示和转换支持（可选）。

## XImg 使用说明

`XImg` 类提供了一些主要的功能和接口来管理图像数据。

#### 加载

- `XImg()` - 默认构造函数，创建一个空的 `XImg` 对象。
- `XImg(const unsigned char *data, int width, int height, DataFormat format, int bytesPerLine = 0)` - 根据给定的数据创建 `XImg` 对象。

#### 图像克隆与赋值

```cpp
XImg img2 = img.clone();
XImg img3;
img3 = img;
```

#### 拍摄信息管理

`XImg` 提供了对拍摄通道、相机和视图的管理。

```cpp
img.setShootChannel("ChannelA");
std::cout << "拍摄通道: " << img.getShootChannel() << std::endl;

img.setShootCamera("Camera1");
std::cout << "拍摄相机: " << img.getShootCamera() << std::endl;

img.setShootView(XImg::createShootViewCode(1, 0));
std::cout << "拍摄视图: " << img.getShootView() << std::endl;
```

#### 互转支持

##### 与 OpenCV 的互转

通过 `XImgExportMat` 类，`XImg` 可以与 `cv::Mat` 进行互转。

- 将 `XImg` 转换为 `cv::Mat`：

  ```cpp
  cv::Mat mat = XImgExportMat::XImgToMat(img);
  ```

- 将 `cv::Mat` 转换为 `XImg`：

  ```cpp
  XImg img2 = XImgExportMat::MatToXImg(mat);
  ```

##### XImgExportMat 深拷贝与浅拷贝

`XImgExportMat` 类提供了将 `XImg` 转换为 `cv::Mat` 和将 `cv::Mat` 转换为 `XImg` 的功能，并且支持 **深拷贝** 和 **浅拷贝** 操作。以下是详细的说明：

```cpp
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
```

- 在 **深拷贝** 中，数据被复制到目标对象，目标对象和源对象的修改不会互相影响。

- 在 **浅拷贝** 中，目标对象直接引用源对象的数据，因此修改目标对象的数据会影响源对象。

##### 与 QImage 的互转（待实现）

当前 `XImgExportQImage` 类尚未实现，但未来将支持将 `XImg` 转换为 `QImage` 类型，以及反向转换。

#### 错误信息

`XImg` 提供了获取错误信息的方法：

```
cpp复制编辑std::string error = img.errorInfo();
std::cout << "错误信息: " << error << std::endl;
```

## 示例代码

以下是一个使用 `XImg` 类的简单示例：

```cpp
#include "XImg.h"

int main() {
    // 创建一个 XImg 对象
    unsigned char* imageData = ... // 图像数据
    XImg img(imageData, 640, 480, XImg::xFormat_RGB888);
    
    // 检查图像是否为空
    if (img.isEmpty()) {
        std::cout << "图像加载失败！" << std::endl;
        return -1;
    }
    
    // 克隆图像
    XImg imgClone = img.clone();
    
    // 设置拍摄信息
    img.setShootChannel("ChannelA");
    img.setShootCamera("Camera1");
    
    // 转换为 OpenCV Mat 类型
    cv::Mat mat = XImgExportMat::XImgToMat(img);
    
    return 0;
}
```

## XImg 单元测试

本项目已集成 `doctest`，用于对 `XImg` 类及其相关功能进行单元测试