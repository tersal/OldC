#include <opencv2/opencv.hpp>
#include <iostream>

int main()
{
 int fps;
 cv::Mat frame;
 cv::Mat frame2;
 
 cv::VideoCapture cam(0);

 if (!cam.isOpened())
 {
   std::cout << "Camara" << std::endl;
   return -1;
 }
  
 //cv::Size size(320,240); 
 cv::Size size(cam.get(CV_CAP_PROP_FRAME_WIDTH),cam.get(CV_CAP_PROP_FRAME_HEIGHT));
 cv::VideoWriter graba("video.avi", CV_FOURCC('F','L','V','1'), 20, size, 0);
 
 if(!graba.isOpened())
 {
  std::cout << "Grabación" << std::endl;
  return -1;
 }
 
 while (true)
 {
  cam.read(frame);
  cv::cvtColor(frame, frame2, CV_BGR2GRAY);
  //cv::resize(frame2, frame2, size, 0, 0, CV_INTER_AREA);

  cv::imshow("Video", frame2);
  graba.write(frame2);
 
  if (cv::waitKey(30) >= 10) break;
 
 }
 graba.release();
 cam.release();
 ~frame;
 ~frame2;
 return 0;
}
