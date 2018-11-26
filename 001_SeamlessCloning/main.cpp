#include <opencv2/opencv.hpp>

using namespace cv;

int main()
{
	// Read images : src image will be cloned into dst
	Mat src = imread("images/src.jpg");
	Mat dst = imread("images/ref.jpg");


	// Create a rough mask around the airplane.
	Mat src_mask = Mat::zeros(src.rows, src.cols, src.depth());

	// Define the mask as a closed polygon
	cv::Point poly[1][4];
	poly[0][0] = cv::Point(149, 722);
	poly[0][1] = cv::Point(950, 722);
	poly[0][2] = cv::Point(950, 1722);
	poly[0][3] = cv::Point(169, 1722);

	const Point* polygons[1] = { poly[0] };
	int num_points[] = { 4 };

	// Create mask by filling the polygon

	fillPoly(src_mask, polygons, num_points, 1, Scalar(255, 255, 255));

	imwrite("images/mask.jpg", src_mask);

	// The location of the center of the src in the dst
	Point center(465, 516);

	// Seamlessly clone src into dst and put the results in output
	Mat output;
	seamlessClone(src, dst, src_mask, center, output, NORMAL_CLONE);

	// Save result
	imwrite("images/opencv-seamless-cloning-example.jpg", output);

	return 1;
}