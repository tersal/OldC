#include <opencv2/opencv.hpp>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>

int main()
{
 int fps;
 cv::Mat frame;
 cv::Mat gray;
 cv::VideoCapture cam(0);
 std::vector<cv::Rect> faces;

 if(!cam.isOpened())
 {
   std::cout << "Error en la camara" << std::endl;
   return 0;
 }
  
 //cv::Size size(320,240); 
 cv::Size csize(cam.get(CV_CAP_PROP_FRAME_WIDTH),cam.get(CV_CAP_PROP_FRAME_HEIGHT));
 cv::VideoWriter graba("video.avi", CV_FOURCC('F','M','P','4'), 8, csize, 1);

 if(!graba.isOpened())
 {
  std::cout << "Error de Grabación" << std::endl;
  return -1;
 }
 
 cv::CascadeClassifier cascade;

 if(!cascade.load("haarcascades/haarcascade_frontalface_alt.xml"))
 {
   std::cout << "Error al cargar cascade";
   return -1;
 }
 
 
 while (true) 
 {
 
  cam.read(frame);
  gray = frame.clone();
  cv::cvtColor(frame, gray, CV_BGR2GRAY);
  cv::equalizeHist(gray,gray);
  //cv::resize(gray, gray, size, 0, 0, CV_INTER_AREA);
  
  cascade.detectMultiScale(gray,faces);

  for (int i=0; i<faces.size(); i++)
  {
   cv::rectangle(frame, faces[i], (0, 255, 0), 1);
  }

  cv::imshow("Video", frame);
  graba.write(frame); 
 
  if(cv::waitKey(30) >=10)
   break;
 }
 graba.release();
 cam.release();
 return 0;

}


