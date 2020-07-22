#include "opencv2/ts.hpp"
#include "opencv2/features2d.hpp"

using namespace opencv_test;


int main() {
    Ptr<FeatureDetector> fd = ORB::create(10000, 1.2f, 8, 31, 0, 2, ORB::HARRIS_SCORE, 31, 20);
    Ptr<DescriptorExtractor> de = fd;

    Mat image = imread("./lenna.png", CV_8UC1);
    assert(!image.empty());

    cout << image.size() << endl;

    if (!image.empty())
    {
        imshow("img", image);
        waitKey();
    }

    Mat roi(image.size(), CV_8UC1, Scalar(0));

    Point poly[] = { Point(6, 6), Point(6, 506), Point(506, 506), Point(506, 6) };
    fillConvexPoly(roi, poly, int(sizeof(poly) / sizeof(poly[0])), Scalar(255));

    std::vector<KeyPoint> keypoints;
    fd->detect(image, keypoints, roi);
    Mat descriptors;
    de->compute(image, keypoints, descriptors);

    image.setTo(Scalar(255,255,255), roi);

    int roiViolations = 0;
    for (std::vector<KeyPoint>::const_iterator kp = keypoints.begin(); kp != keypoints.end(); ++kp)
    {
        int x = cvRound(kp->pt.x);
        int y = cvRound(kp->pt.y);


         if (roi.at<uchar>(y,x))
         {
             roiViolations++;
             circle(image, kp->pt, 3, Scalar(0,0,255));
         }
    }

    cout << roiViolations << endl;

    if(roiViolations)
    {
        imshow("img", image);
        waitKey();
    }

    return 0;
}