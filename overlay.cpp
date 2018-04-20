#include <opencv2/opencv.hpp>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

int main()
{
 cv::Mat smiley.imread("./smiley.png");
 cv::Mat picture.imread("./beatles02.jpg");
 cv::CascadeClassifier cascade;
 std::vector<cv::Rect> faces;

 if(!cascade.load("haarcascades/haarcascade_frontalface_alt.xml");
 {
  std::cout << "Error al cargar Haarcascade";
  return -1;
 }
 
 cascade.detectMultiScale(picture, faces, 1.1, 3, 0, cv::Size(20,20));

 return 0;
} 
  
 
 
 
