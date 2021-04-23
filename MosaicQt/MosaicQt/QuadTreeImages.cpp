#include "QuadTreeimages.h"
#include <iostream>

QuadTreeimages::QNode::QNode(int x0, int y0, int width, int heigth)
{
	this->x0 = x0;
	this->y0 = y0;
	this->width = width;
	this->height = heigth;
	this->children = std::vector<QNode*>();
}

int QuadTreeimages::QNode::GetWidth()
{
	return this->width;
}

int QuadTreeimages::QNode::GetHeigth()
{
	return this->height;
}

cv::Mat QuadTreeimages::QNode::GetPoints()
{
	return this->points;
}

cv::Mat QuadTreeimages::QNode::GetPoints(const cv::Mat& image)
{
	//std::cout << x0 << " " << y0 << " " << width << " " << height << std::endl;
	cv::Rect cropped(y0, x0, width, height);

	return image(cropped);
}

double QuadTreeimages::QNode::GetError(const cv::Mat& image)
{
	auto pixels = GetPoints(image);

	cv::Mat3i temp = pixels;

	cv::Scalar avg = cv::mean(temp);
	mean = avg;
	temp = temp - avg;

	cv::pow(temp, 2, temp);
	cv::Scalar mse = cv::mean(temp);

	double e = mse[0] * 0.2989 + mse[1] * 0.5870 + mse[2] * 0.1140;
	return (e * image.cols * image.rows) / 90000000;
}

void QuadTreeimages::RecursiveSubDivide(QNode* node, double k, int m_minPixelSize, const cv::Mat& img)
{
	double size = node->GetError(img);

	//std::cout << "size:" << size << std::endl;
	if (size <= k)
	{
		return;
	}
	int w_1 = (int)(std::floor(node->width / 2));
	int w_2 = (int)(std::ceil(node->width / 2));
	int h_1 = (int)(std::floor(node->height / 2));
	int h_2 = (int)(std::ceil(node->height / 2));
	//std::cout << w_1 << " " << w_2 << " " << h_1 << " " << h_2;

	if (w_1 <= m_minPixelSize || h_1 <= m_minPixelSize)
	{
		return;
	}

	QNode* x1 = new QNode(node->x0, node->y0, w_1, h_1); //top left
	RecursiveSubDivide(x1, k, m_minPixelSize, img);

	QNode* x2 = new QNode(node->x0, node->y0 + w_1, w_1, h_2); //btm left
	RecursiveSubDivide(x2, k, m_minPixelSize, img);

	QNode* x3 = new QNode(node->x0 + h_1, node->y0, w_2, h_1); //top right
	RecursiveSubDivide(x3, k, m_minPixelSize, img);

	QNode* x4 = new QNode(node->x0 + h_1, node->y0 + w_1, w_2, h_2); //btm right
	RecursiveSubDivide(x4, k, m_minPixelSize, img);

	node->children = std::vector<QNode*>();

	node->children.push_back(x1);
	node->children.push_back(x2);
	node->children.push_back(x3);
	node->children.push_back(x4);

}

QuadTreeimages::QuadTreeimages(double m_threshold, int m_minPixelSize, const cv::Mat& image)
{
	this->m_threshold = m_threshold;
	this->m_minSize = m_minPixelSize;
	this->m_minPixelSize = m_minPixelSize;
	this->m_image = image;
	this->m_root = new QNode(0, 0, image.cols, image.rows);
}

void QuadTreeimages::Subdivide()
{
	RecursiveSubDivide(m_root, m_threshold, m_minPixelSize, m_image);
}

cv::Mat QuadTreeimages::Concat_images(const cv::Mat& img1, const cv::Mat& img2, int boarder, const cv::Scalar& color)
{
	cv::Mat borderImg1 = img1;
	cv::Mat borderImg2 = img2;

	cv::copyMakeBorder(img1, borderImg1, boarder, boarder, boarder, boarder, cv::BORDER_CONSTANT, color);
	cv::copyMakeBorder(img2, borderImg2, boarder, boarder, 0, boarder, cv::BORDER_CONSTANT, color);


	// Get dimension of final image
	int rows = cv::max(img1.rows, img2.rows);
	int cols = img1.cols + img2.cols;

	// Create a black image
	cv::Mat3b res(rows, cols, cv::Vec3b(0, 0, 0));

	// Copy images in correct position
	img1.copyTo(res(cv::Rect(0, 0, img1.cols, img1.rows)));
	img2.copyTo(res(cv::Rect(img1.cols, 0, img2.cols, img2.rows)));

	return res;
}

double QuadTreeimages::GetThreshold() const
{
	return this->m_threshold;
}

void QuadTreeimages::SetThreshold(const double& threshold)
{
	this->m_threshold = threshold;
}

int QuadTreeimages::GetMinSize() const
{
	return this->m_minSize;
}

void QuadTreeimages::SetMinSize(const int& minSize)
{
	this->m_minSize = minSize;
}

int QuadTreeimages::GetMinPixelSize() const
{
	return this->m_minPixelSize;
}

void QuadTreeimages::SetMinPixelSize(const int& minPixelSize)
{
	this->m_minPixelSize = minPixelSize;
}

cv::Mat QuadTreeimages::GetImage() const
{
	return this->m_image;
}

void QuadTreeimages::SetImage(const cv::Mat& image)
{
	this->m_image = image;
}

QuadTreeimages::QNode* QuadTreeimages::GetRoot() const
{
	return this->m_root;
}
