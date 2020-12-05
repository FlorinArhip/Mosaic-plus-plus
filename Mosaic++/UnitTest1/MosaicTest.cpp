#include "pch.h"
#include "CppUnitTest.h"
#include "../Mosaic++/Mosaic.h"
#include "../Mosaic++/Mosaic.cpp"
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc.hpp>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace MosaicTest
{
	TEST_CLASS(MosaicTest)
	{
	public:

		TEST_METHOD(euclideanDistanceTest)
		{
			cv::Scalar color1(0, 0, 1);
			cv::Scalar color2(255, 255, 255);
			uint8_t blueD, greenD, redD;
			blueD = color1[0] - color2[0];
			greenD = color1[1] - color2[1];
			redD = color1[2] - color2[2];
			uint16_t euclid = blueD * blueD + greenD * greenD + redD + redD;
			Assert::IsTrue(euclideanDistance(color1, color2) == euclid);

		}

		TEST_METHOD(ReplaceTest)
		{
			//TOO DO 
		}

		TEST_METHOD(MakeTest)
		{
			//TOO DO
		}
	};
}