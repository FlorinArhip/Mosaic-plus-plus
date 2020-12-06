#include "pch.h"
#include "CppUnitTest.h"
#include "../Mosaic++/PictureTools.h"
#include "../Mosaic++/PictureTools.cpp"
#include "../Mosaic++/StopWatch.h"
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc.hpp>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace PictureToolsTest
{
	TEST_CLASS(PictureToolsTest)
	{
	public:

		TEST_METHOD(TestSpeed)
		{			
			
			cv::Mat input = imread("..//test.jpg", IMREAD_COLOR);
			cv::Mat input2 = imread("..//test.jpg", IMREAD_COLOR);
			
			stopwatch swOriginal;
			stopwatch swMine;
			swOriginal.tick();

			//input = PictureTools::resize(input, 800, 800);
			cv::resize(input, input, { 800,800 });

			swOriginal.tock();

			swMine.tick();

			input2 = PictureTools::resize(input2, 800, 800);
			//cv::resize(input2, input2, { 800,800 });

			swMine.tock();

			//Assert::AreEqual(swOriginal, swMine);
		}

		TEST_METHOD(Resize)
		{
			Mat testImage = imread("..//test.jpg", IMREAD_COLOR);

			testImage = PictureTools::resize(testImage, 600, 600);

			bool testingSize = testImage.rows == 600 && testImage.cols == 600;

			Assert::IsTrue(testingSize);
			Assert::IsTrue(!testImage.empty());
		}

		TEST_METHOD(Crop)
		{
			Mat testImage = imread("..//test.jpg", IMREAD_COLOR);

			Mat cropedImage = PictureTools::crop(testImage, { 0,0 }, { 20,20 });

			bool isEqual = true;

			for (int index_x = 0; index_x < 20; ++index_x)
				for (int index_y = 0; index_y < 20; ++index_y)
					if (testImage.at<Vec3b>(index_x, index_y) != cropedImage.at<Vec3b>(index_x, index_y))
					{
						isEqual = false;
						break;
					}

			Assert::IsTrue(isEqual);
		}
	};
}