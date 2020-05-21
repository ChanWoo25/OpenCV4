#include "opencv2/opencv.hpp"
#include <iostream>

using namespace cv;
using namespace std;

void MatOp1();
void MatOp2();
void MatOp3();
void MatOp4();
void MatOp5();
void MatOp6();
void MatOp7();

int main()
{
// 	MatOp1();
// 	MatOp2();
// 	MatOp3();
// 	MatOp4();
// 	MatOp5();
// 	MatOp6();
	MatOp7();

	return 0;
}
// Mat변수 type, construct, scalar product, 
// zeros/ones/identity Matrix, Various Initialization Method
void MatOp1()
{
	Mat img1; 	// empty matrix

	Mat img2(480, 640, CV_8UC1);		// unsigned char, 1-channel
	Mat img3(480, 640, CV_8UC3);		// unsigned char, 3-channels
	Mat img4(Size(640, 480), CV_8UC3);	// Size(width, height)

	Mat img5(480, 640, CV_8UC1, Scalar(128));		// initial values, 128
	Mat img6(480, 640, CV_8UC3, Scalar(0, 0, 255));	// initial values, red

	Mat mat1 = Mat::zeros(3, 3, CV_32SC1);	// 0's matrix
	Mat mat2 = Mat::ones(3, 3, CV_32FC1);	// 1's matrix
	Mat mat3 = Mat::eye(3, 3, CV_32FC1);	// identity matrix

	float data[] = { 1, 2, 3, 4, 5, 6 };
	Mat mat4(2, 3, CV_32FC1, data);

	Mat mat5 = (Mat_<float>(2, 3) << 1, 2, 3, 4, 5, 6);
	Mat mat6 = Mat_<uchar>({2, 3}, { 1, 2, 3, 4, 5, 6 });

	mat4.create(5, 5, CV_8UC3);	// uchar, 3-channels
	mat5.create(4, 4, CV_32FC1);	// float, 1-channel

	mat4 = Scalar(255, 0, 0);
	mat5.setTo(1.f);
    
    cout << mat1 << endl;
    cout << mat2 << endl;
    cout << mat3 << endl;
    cout << mat4 << endl;
    cout << mat5 << endl;
    cout << mat6 << endl;
    //cout << mat7 << endl;
}

void MatOp2() //행렬의복사
{
    Mat img1 = imread("dog.bmp");
    if (img1.empty()) {
		cerr << "Image load failed!" << endl;
		return;
	}
    // 1. Use Copy constructor
    Mat img2 = img1; //direct same memory space // Shallow copy.
    
    // 2. Use Assignment operator.
    Mat img3;
    img3 = img1;    //Also shallow copy

    // How to deep copy?
    // 1. Mat Mat::clone() const
    Mat img4 = img1.clone();
    
    // 2.   void Mat::copyTo(OutputArray m) const;
    //      void Mat::copyTo(OutputArray m, InputArray mask) const; //0 이아닌부분만채워짐
    Mat img5;
    img1.copyTo(img5);
    
    img1.setTo(Scalar(0, 255, 255)); //yellow
    
    imshow("img1", img1);
    imshow("img2", img2);
    imshow("img3", img3);
    imshow("img4", img4);
    imshow("img5", img5);
    
    waitKey();
    destroyAllWindows();
}

void MatOp3() // 부분행렬추출,참조
{
	Mat img1 = imread("cat.bmp");

	if (img1.empty()) {
		cerr << "Image load failed!" << endl;
		return;
	}
    // 관심영역, 즉 ROI설정하는용도가능.
	// Use Overloaded Parentheses operator
	Mat img2 = img1(Rect(220, 120, 340, 240)); //Note that this is shallow copy
	Mat img3 = img1(Rect(220, 120, 340, 240)).clone();

    // * row-Range:y-axis  ||  col-Range:x-axis *
    Mat img4 = img1(Range(80, 160), Range(110, 330));
    Mat img5;
    img4.copyTo(img5);
    
    //반전영상!
	img2 = ~img2;
    img4 = ~img4;
    
	imshow("img1", img1);
	imshow("img2", img2);
	imshow("img3", img3);
    imshow("img4", img4);
	imshow("img5", img5);

	waitKey();
	destroyAllWindows();
    // Plus 밑의함수들은모두shallow copy
    /* Mat Mat::rowRange(int startrow, int endrow) const; // [startrow, endrow) 구간
     * Mat Mat::colRange(int startcol, int endcol) const; // [startcol, endcol) 구간
     * Mat Mat::rowRange(const Range& r) const;
     * Mat Mat::colRange(const Range& r) const;
     * Mat Mat::row(int y) const; 1행 1열짜리 Mat반환 
     * Mat Mat::col(int x) const;
     */
}

 //사용자가 자신만의 알고리즘을 구현하여 적용해야 하는 경우, 픽셀 접근 방법 3가지의 장단점
void MatOp4()
{
    Mat mat1 = Mat::zeros(3, 4, CV_8UC1);
    
    for(int j = 0; j < mat1.rows; j++) { // y coord
        for(int i=0; i<mat1.cols; i++){  // x coord
            mat1.at<uchar>(j, i)++;     // can change value since 'at' returns reference.
        }                               // origin point is (0,0)
    }

    //일정한 행에서 대부분의 작업이 이루어지는 경우 ptr을 사용하는 것이 속도에서 유리하다.
    for (uint j=0; j<mat1.rows; j++){
        uchar* p = mat1.ptr<uchar>(j);
        for(uint i=0; i<mat1.cols;i++){
            ++*(p + i); // or p[i]++;
        }
    }

    for (MatIterator_<uchar> it = mat1.begin<uchar>(); it != mat1.end<uchar>(); ++it){
        (*it)++;
    }
	cout << "mat1:\n" << mat1 << endl;
}

void MatOp5()
{
    Mat img = imread("lenna.bmp");
    
    cout << "width: " << img.cols << endl;
    cout << "height: " << img.rows << endl;
    cout << "channels: " << img.channels() << endl;
    
    if(img.type() == CV_8UC1)
        cout << "img is grayscale image." << endl;
    else if(img.type() == CV_8UC3)
        cout << "img is truecolor image." << endl;
    
	float data[] = { 2.f, 1.414f, 3.f, 1.732f };
	Mat mat1(2, 2, CV_32FC1, data);
	cout << "mat1:\n" << mat1 << endl;
}

void MatOp6()
{
    float data[] = {1.23, 5.142, 2.156, 2.43 };
    Mat mat1(2, 2, CV_32FC1, data);
	cout << "mat1:\n" << mat1 << endl;

    // Inverse Matrix 
	Mat mat2 = mat1.inv();
	cout << "mat2:\n" << mat2 << endl;
    // if non-singular matrix
    mat1.inv(DECOMP_LU);
    // if singular matrix -> singular value decomposition(SVD) -> pseudo-inverse matrix
    mat1.inv(DECOMP_SVD);
    // Eigen value decomp & Cholesky decomp
    mat1.inv(DECOMP_EIG);
    mat1.inv(DECOMP_CHOLESKY);

    // Transpose
	cout << "mat1.t():\n" << mat1.t() << endl;
    cout << "mat1 + 3:\n" << mat1 + 3 << endl;
	cout << "mat1 + mat2:\n" << mat1 + mat2 << endl;
	// Matrix product
    cout << "mat1 * mat2:\n\n" << mat1 * mat2 << endl;
    
    Mat mat4 = (Mat_<float>(2, 2) << 1, 2, 3, 4);
    Mat mat5 = Mat_<float>({2,2}, {1, 2, 3, 4});
    
    // Elementwise Operator
    cout << mat4.mul(mat5) << endl;
    cout << "mat4 / 0.2 = \n\n" << (mat4 / 0.3) <<endl;
    cout << "3 / mat = \n\n" << (3/mat4) <<endl; 
    cout << "mat4 / mat5 elementalwise \n\n" << (mat4/mat5) <<endl;
}

void MatOp7() // 크기or타입을변환시키는멤버함수
{
	Mat img1 = imread("lenna.bmp", IMREAD_GRAYSCALE);

	Mat img1f;
	img1.convertTo(img1f, CV_32FC1);

	uchar data1[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12 };
	Mat mat1(3, 4, CV_8UC1, data1);
    
    // Share memory space with original one.
    // arg[0] -- 바꿀채널수,0이면유지
    // arg[1] -- 바꿀행수,0이면유지
	Mat mat2 = mat1.reshape(0, 1); 

	cout << "mat1:\n" << mat1 << endl;
	cout << "mat2:\n" << mat2 << endl;

	mat1.resize(5, 100); // Adjust mat1's row with arg[0], extra rows are filled with scalar arg[1].
	cout << "mat1:\n" << mat1 << endl;

	Mat mat3 = Mat::ones(1, 4, CV_8UC1) * 255;
	mat1.push_back(mat3);
	cout << "mat1:\n" << mat1 << endl;
    
    Mat mat4 = (Mat_<uchar>(1, 4) << 1, 2, 3, 4);
    mat1.push_back(mat4);
    cout << "mat1:\n" << mat1 << endl;

    uchar data2[] = {2, 3, 4, 5};
    Mat mat5(1, 4, CV_8UC1, data2);
    mat1.push_back(mat5);
    cout << "mat1:\n" << mat1 << endl;
}
