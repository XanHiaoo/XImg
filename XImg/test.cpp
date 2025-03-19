#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "XImg.h"
#include "XImgExportMat.h"
#include <iostream>
#include <vector>

TEST_CASE("Load image from data") {
	unsigned char imageData[27] = {
		255, 0, 0,  0, 255, 0,  0, 0, 255,
		255, 255, 0,  0, 255, 255,  255, 0, 255,
		100, 100, 100,  150, 150, 150,  200, 200, 200
	};

	XImg img(imageData, 3, 3, XImg::xFormat_RGB888);

	CHECK_FALSE(img.isEmpty());
	CHECK(img.getShootChannel().empty());
	CHECK(img.getShootCamera().empty());
}

TEST_CASE("Set and get shoot channel") {
	XImg img;
	img.setShootChannel("Channel_1");
	CHECK(img.getShootChannel() == "Channel_1");

	img.setShootChannel("Channel_2");
	CHECK(img.getShootChannel() == "Channel_2");
}

TEST_CASE("Set and get shoot camera") {
	XImg img;
	img.setShootCamera("Camera_1");
	CHECK(img.getShootCamera() == "Camera_1");

	img.setShootCamera("Camera_2");
	CHECK(img.getShootCamera() == "Camera_2");
}

TEST_CASE("Set and get shoot view") {
	XImg img;
	img.setShootView("View_1");
	CHECK(img.getShootView() == "View_1");

	img.setShootView("View_2");
	CHECK(img.getShootView() == "View_2");
}

TEST_CASE("Clone image") {
	unsigned char imageData[9] = { 255, 0, 0, 0, 255, 0, 0, 0, 255 };// 3x3 RGB 图像
	XImg img1(imageData, 3, 3, XImg::xFormat_RGB888);
	XImg img2 = img1.clone();

	CHECK(img2.getShootChannel() == img1.getShootChannel());
	CHECK(img2.getShootCamera() == img1.getShootCamera());
	CHECK(img2.getShootView() == img1.getShootView());
	CHECK_FALSE(img2.isEmpty());
}

TEST_CASE("Edge cases: empty data and invalid format") {
	XImg img;

	// 空数据
	std::vector<unsigned char> emptyData;
	CHECK_FALSE(img.loadImage(emptyData.data(), 0, 0, XImg::xFormat_Invalid));

	// 无效格式
	XImg invalidFormatImg(emptyData.data(), 10, 10, XImg::xFormat_Invalid);
	CHECK(invalidFormatImg.isEmpty());

	// 数据大小与格式计算出的大小不匹配
	std::vector<unsigned char> smallData(10); // 仅 10 字节，但需要更大数据
	CHECK_FALSE(img.loadImage(smallData.data(), 10, 10, XImg::xFormat_RGB888));

	// bytesPerLine 影响数据大小
	std::vector<unsigned char> mismatchedLineData(10 * 4 * 5); // 10 宽度，RGBA32 但行大小不符
	CHECK_FALSE(img.loadImage(mismatchedLineData.data(), 10, 5, XImg::xFormat_RGBA32, 30));

	// nullptr 数据输入
	CHECK_FALSE(img.loadImage(nullptr, 10, 10, XImg::xFormat_RGB888));

	MESSAGE("All edge case tests passed.");
}

#ifdef OPENCV_ENABLED
TEST_CASE("Convert XImg to cv::Mat") {
	struct TestCase {
		XImg::DataFormat format;
		int channels;
		std::string name;
	};

	std::vector<TestCase> testCases = {
		{XImg::xFormat_Grayscale8, 1, "Grayscale8"},
		{XImg::xFormat_RGB888, 3, "RGB888"},
		{XImg::xFormat_BGR888, 3, "BGR888"},
		{XImg::xFormat_RGBA32, 4, "RGBA32"},
		{XImg::xFormat_BGRA32, 4, "BGRA32"}
	};

	for (const auto& testCase : testCases) {
		int width = 3, height = 3;
		int bytesPerPixel = testCase.channels;
		int bytesPerLine = width * bytesPerPixel;

		std::vector<unsigned char> imageData(height * bytesPerLine);
		for (int i = 0; i < height * width; ++i) {
			for (int c = 0; c < testCase.channels; ++c) {
				imageData[i * testCase.channels + c] = static_cast<unsigned char>(i * 10 * (c + 1));
			}
		}

		XImg img(imageData.data(), width, height, testCase.format, bytesPerLine);
		cv::Mat mat = XImgExportMat::XImgToMat(img);

		CHECK_FALSE(mat.empty());
		CHECK(mat.cols == width);
		CHECK(mat.rows == height);
		CHECK(mat.channels() == testCase.channels);
	}
}
#endif // OPENCV_ENABLED

