#include "opencv2/opencv.hpp"
#include <iostream>

using namespace std;

int main()
{
    
    std::cout << "Hello OpenCV" << std::endl;
    cv::Point2d a(1.23, 1.56);
    cv::Point2d b(1, 2.8);
    
    std::cout << "a: " << a << "\nb: " << b;
    std::cout << "\na + b = " << (a+b) << std::endl;
    std::cout << "a * b = " << a.ddot(b) << std::endl;
    std::cout << "a x b = " << a.cross(b) << std::endl;
    std::cout << sizeof(a.x) << std::endl;
    
    cv::Size sz1, sz2(10, 20);
    cout << sz1;
    sz1.width = 5, sz1.height = 5;
    cout << sz1 << sz2 << endl;
    
    cv::Size sz3 = sz1 + sz2;
    cv::Size sz4 = sz1 * 2;
    int area1 = sz4.area();
    
    cout << sz3 << '\n' << sz4 << "\nsz4's area is " << area1 << endl;
    
//     cv::Rect rc1;
//     cv::Rect rc2(10, 10, 60, 40);
//     
//     if(rc1.empty()) cout << "rc1 is empty!\n";
//     rc1 += cv::Size(40, 60);
//     rc1 += cv::Point(10, 10);
//     cout << "Now rc1 is " << rc1 << endl;
//     cout << rc1.br() << rc1.tl() << endl;
//     cout << "rc1 & rc2 is " << (rc1 & rc2) << endl;
//     cout << "rc1 | rc2 is " << (rc1 | rc2) << endl;
//     cout << "rc1's area = " << rc1.area() << " = " << (rc1.tl().x - rc1.br().x) * (rc1.tl().y - rc1.br().y) << endl;
    
    cv::RotatedRect rr1(cv::Point2f(40, 30), cv::Size2f(40, 20), 30.f);
    cout << rr1.center << rr1.size << rr1.angle << endl;
    
    cv::Point2f pts[4];
    rr1.points(pts);
    
    for(int i = 0; i < 4; i++){
        cout << pts[i] << " ";
    }   cout << endl;
    
    cv::Rect br = rr1.boundingRect();
    cout << "Minimum bounding rectangular is " << br << endl;
    
    // Range //
    cv::Range r1, r2(10, 20);
    cout << "r1: " << r1 << endl;
    cout << "r2: " << r2 << endl;
    if(!r2.empty()){
        cout << "r2's size is " << r2.size() << endl;
        cout << "r2's range is [" << r2.start << ", " << r2.end << ") // 열린구간주의" << endl;
    }
    
    // STRING == std::string 
    for(int i=0; i<5; i++){
        cv::String filename = cv::format("test%03d.bmp", i+1);
        cout << filename << endl;
    }
    
    // Mat
    // depth : CV_<bit-depth>{U|S|F}
    // depth + channel : CV_<bit-depth>{U|S|F}C(<number_of_channels>)
    // ex) CV_8UC1 : 8 bit unsigned char type 1 channel Mat.
    
    cv::Mat img1;
    cout << img1.rows << endl;
    cout << img1.cols << endl;
    cout << (img1.data == NULL) << endl;
    
    cv::Mat img2(480, 640, CV_8UC1);
    cv::Mat img3(480, 640, CV_8UC3);
    cv::Mat img4(cv::Size(480, 640), CV_8UC3);  // 모두쓰레기값이채워짐
    
    //with Initialization
    //Mat::Mat(int rows, int cols, int type, const Scalar& s);
    // Scalar is OpenCV class which can contain at most 4 real numbers.
    cv::Mat img5(480, 640, CV_8UC1, cv::Scalar(128));
    cv::Mat img6(480, 640, CV_8UC3, cv::Scalar(0, 0, 255));
    
    cv::Mat mat1 = cv::Mat::zeros(3, 3, CV_32SC1);
    cv::Mat mat2 = cv::Mat::ones(3, 3, CV_32SC1);
    cv::Mat mat3 = cv::Mat::eye(3, 3, CV_32SC1);
    cout << mat1 << mat2 << endl << mat3 << endl;
    
    //외부메모리공간을활용하기
    float data[] = {1, 2, 3, 4, 5, 6};
    cv::Mat mat4(2, 3, CV_32FC1, data);
    cout << mat4 << endl;
    
    // use Mat_ class
    cv::Mat_<float> mat5_(2, 3);  // Templete class! and specify size only;
    mat5_ << 1, 2, 3, 4, 5, 6;
    cv::Mat mat5 = mat5_;
    cv::Mat mat6 = (cv::Mat_<float>(2, 3) << 1, 2, 2, 3, 3, 3);
    cout << mat5 << endl << mat6 << endl;
    
    // Also can use C++11's initializer list
    cv::Mat mat7 = cv::Mat_<float>({2, 3}, {6, 5, 4, 3, 2, 1});
    cout << mat7 << endl;
    
    // Use create function **THERE's NO INTIALIZE!**
    mat4.create(8, 8, CV_32FC3);
    mat5.create(4, 4, CV_16FC1);
    
    // 2 way to initialize at once.
    mat4 = cv::Scalar(256, 0, 0);
    mat5.setTo(1.0f);
    cout << mat4 << endl << mat5 << endl;
    
    // more than 3 dimensions
    // Mat::Mat(int ndims, const int* sizes, int type)
    // Mat::Mat(const std::vector<int>& sizes, int type) // ndims = sizes.length();
    
    return 0;
    
}
