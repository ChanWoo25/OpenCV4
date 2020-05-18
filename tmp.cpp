#include "opencv2/opencv.hpp"
#include <iostream>

int main()
{
	std::cout << "Hello OpenCV " << CV_VERSION << std::endl;
	
	cv::Mat img;
    // Return Mat class obj
    // flags
    // cv::IMREAD_UNCHANGED
    // cv::IMREAD_GRAYSCALE cv::IMREAD_COLOR
    // cv::IMREAD_REDUCED_GRAYSCALE_2 cv::IMREAD_REDUCED_COLOR_2   1/2 scale image
    // cv::IMREAD_IGNORE_ORIENTATION   Don't use direction info. stored in EXIF
	img = cv::imread("lenna.bmp", cv::IMREAD_COLOR);

	if(img.empty()){
		std::cerr << "Image Load Failed!" << std::endl;
		return -1;;
	}

	//cv::namedWindow("image", cv::WINDOW_AUTOSIZE);
	cv::imshow("image", img); //BGR base color

	cv::waitKey(5000);
	return 0;
}
