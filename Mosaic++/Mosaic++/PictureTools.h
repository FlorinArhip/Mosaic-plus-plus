#pragma once
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <cstdlib>

using namespace cv;




class PictureTools
{
private:
	using Point = std::pair <uint16_t, uint16_t>;

private:
	static const uint8_t defaultSize = 10;

public:
	static Mat crop(const Mat& image, Point topL, Point botR);
	static Mat rotateLeft(const Mat& image);
	static Mat rotateRight(const Mat& image);
	static Mat rotate180(const Mat& image);
	static Mat resize(const Mat& image, const uint16_t& width = 0, const uint16_t& height = 0);
	static Scalar averageColor(const Mat& image);
	static Mat makeMosaic(const std::unordered_map<cv::Scalar, std::string>& dataPictures, Mat& image, const uint8_t& partitionSize = defaultSize);
	static void replaceCell(Mat& originalPicture, const Mat& mosaicPhoto,const std::pair<int, int>& topL);

	friend int euclidianDistance(const Scalar& firstColor, const Scalar& secondColor);

};

