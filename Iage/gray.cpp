#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>
using namespace std;
using namespace cv;

int main( int argc, char** argv)
{
 char* imageName = argv[1];

 Mat image;
 image = imread( imageName, 1);

 if(argc != 2 || !image.data )
 {
  cout << " No image data \n";
  return -1;
 }
 
 Mat gray_image;
 cvtColor(image, gray_image, CV_BGR2GRAY );
 imwrite("Gray_Image.jpg", gray_image);

 namedWindow( imageName, CV_WINDOW_AUTOSIZE);
 namedWindow( "Gray image", CV_WINDOW_AUTOSIZE);
 
 imshow("Gray image", gray_image);
 imshow(imageName, image); 

 waitKey(0);
 return 0;
}
