#include <opencv2/opencv.hpp>
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <unistd.h>

//#COMENTARIO 1 soy david y amo al fili

int main()
{
 std::stringstream aux;
 std::vector<cv::Rect> faces;
 int j=0;
 try
 { 
  cv::VideoCapture cam("http://172.19.0.210/mjpg/video.mjpg");
  if(!cam.isOpened())
  {
    std::cout << "Error de Camara" << std::endl;
    return -1;
  }

  cv::CascadeClassifier cascade;
 
  if(!cascade.load("haarcascades/haarcascade_frontalface_alt.xml"))
  {
   std::cout << "Error cargando el clasificador";
   return -1;
  }
  
  cv::VideoWriter graba("video.avi", cam.get(CV_CAP_PROP_FOURCC), 10, cv::Size(320,240));
  
  if(!graba.isOpened())
  {
   std::cout << "Error: Video de Salida";
   return -1;
  }


  while (true) {
  cv::Mat frame;
  cv::Mat gray;
  cv::Mat cop;

  cam.read(frame);
  cv::cvtColor(frame,gray,CV_BGR2GRAY);
  cv::equalizeHist(gray,gray);
  
  cascade.detectMultiScale(gray, faces, 1.1, 3, 0|CV_HAAR_SCALE_IMAGE, cv::Size(20,20));
  
  for (int i=0; i<faces.size(); i++)
  {
   cv::rectangle(frame, faces[i], (0, 255, 0), 1);
  }
  
  graba.write(frame);
  
  

  cv::imshow("CAM",frame);
  if (cv::waitKey(30) >=0)
  break;
  
  }
  
 graba.release();
 cam.release(); 

 }
 
 catch (...)
 {
  std::cout << "Exception: " << std::endl;
 }
 
 
 return 0;

}
  
  
