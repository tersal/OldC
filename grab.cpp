#include <opencv2/opencv.hpp>
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <unistd.h>

cv::Mat manageImg(cv::Mat image)
{
 cv::Mat image2=image.clone();
 cv::Mat element = getStructuringElement(cv::MORPH_RECT, cv::Size(10,10), cv::Point(0,0)); 
 
 morphologyEx( image, image2, cv::MORPH_BLACKHAT, element); 
 return(image2);
}


int main() {
 int fps;
 
 cv::VideoCapture cam(0);

 if(!cam.isOpened())
 {
  std::cout << "Error de Camara" << std::endl;
  return -1;
 }
 
 fps = cam.get(CV_CAP_PROP_FPS);
 cv::Size size(cam.get(CV_CAP_PROP_FRAME_WIDTH), cam.get(CV_CAP_PROP_FRAME_HEIGHT));


 cv::VideoWriter graba("video.avi", CV_FOURCC('F','M','P','4'), fps, size);

 if(!graba.isOpened())
 {
  std::cout << "Error de Grabación" << std::endl;
  return -1;
 }
 
 while (true)
 {
  cv::Mat frame;
  cv::Mat gray;
  
  cam.read(frame);
  //cv::cvtColor(frame, gray, CV_BGR2GRAY);
  //cv::equalizeHist(gray,gray);
  

  gray = manageImg(frame);  
  
   
  graba.write(frame);
 
  cv::imshow("CAM", gray);
  if (cv::waitKey(30) >= 0)
  break;

  }

 graba.release();
 cam.release();
 return 0;
}
