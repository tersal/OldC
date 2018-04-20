#include <opencv2/opencv.hpp>
#include <iostream>
#include <string>
#include <vector>
#include <thread>
#include <mutex>
// Librerias SOCKET
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>

#define PORT 9080

std::mutex locker;
cv::Mat image;
cv::Mat gray;
bool ready = false;
 
int ssock;
int csock;
bool cancel=true;

void streamServer();

int main( int argc, char** argv)
{
 std::cout << "Iniciando Hilo de servidor." << std::endl;
 std::thread servidor;
 std::vector<cv::Rect> faces;
 cv::VideoCapture cam(0);
 cv::Size size;
 cv::namedWindow("Video", CV_WINDOW_AUTOSIZE);
 if(!cam.isOpened())
 {
   std::cout << "Error en la cámara" << std::endl;
   return -1;
 }
 //size = cv::Size(cam.get(CV_CAP_PROP_FRAME_WIDTH), cam.get(CV_CAP_PROP_FRAME_HEIGHT));
  size = cv::Size(320,240);
 // Inicio de la grabación y establecimiento de cascadas aqui.
 
 cam.read(image);
 gray = cv::Mat::zeros(size, CV_8UC1);
 
 servidor = std::thread(streamServer);

 while (true)
 {
  cam.read(image);
  locker.lock();
  //Tratamiento de imagen para grabación o transmisión
  cv::resize(image, image, size, cv::INTER_LINEAR);
  cv::cvtColor(image,gray,CV_BGR2GRAY,1);
  ////
  ready=true;
  locker.unlock();
  
  cv::imshow("Video", gray);
  if (cv::waitKey(30) >= 10)
  {
    cancel=false;
    break;
  }
  usleep(100000);
 }
 servidor.join();
 cam.release();
 cv::destroyWindow("Video");
 if(csock) close(csock);
 if(ssock) close(ssock);
 ~gray;
 ~image;
 return 0;
}

void streamServer(void)
{
 int len;
 int bytes;
 std::vector<uchar> buf;
 std::vector<int> param;
 param.push_back(CV_IMWRITE_JPEG_QUALITY);
 param.push_back(75);
 struct sockaddr_in server;

 ssock = socket(AF_INET, SOCK_STREAM, 0);
 if(ssock == -1)
 {
   std::cout << "SOCKET Failed" << std::endl;
   return;
 }

 memset(&server, 0 , sizeof(server));

 server.sin_family = AF_INET;
 server.sin_port = htons(PORT);
 server.sin_addr.s_addr = INADDR_ANY;

 if (bind(ssock, (struct sockaddr *)&server, sizeof(server)) == -1)
 {
   std::cout << "bind() failed" << std::endl;
   return;
 }
 
 if (listen(ssock, 5) == -1) 
 {
  std::cout << "listen() failed" << std::endl;
  return;
 }

 if ((csock = accept(ssock, NULL, NULL)) == -1) 
 {
  std::cout << "accept() failed" << std::endl;
  return;
 }

 while(cancel)
 {
  locker.lock();
  if (ready)
  {
    cv::imencode(".jpg", gray, buf, param);
    len=buf.size();
    bytes = send(csock, &len, 4, 0);
    usleep(200);
    bytes = send(csock, &buf[0], buf.size(),0);
    std::cout << bytes  << " : " << buf.size() << std::endl ;
    ready = false;
  }
  locker.unlock();
  
  if (bytes != buf.size())
  {
     std::cout << "Connection closed" << std::endl;
     return;
  }
  usleep(1000);
 }

}  
