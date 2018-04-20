//Librerias SOCKET
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
//Librerias estándar y OpenCV
#include <opencv2/opencv.hpp>
#include <iostream>
#include <string>
#include <vector>
#include <thread>
#include <mutex>

#define PORT 9080

std::mutex locker;
cv::Mat frame;
bool ready =false;
bool cancel = true;
int sock;
std::string server_ip = "172.19.0.252";

void streamClient(void);

int main(int argc, char** argv)
{
 std::cout << "Iniciando Transmisión." << std::endl;
 std::thread cliente;
 cv::namedWindow("Streaming", CV_WINDOW_AUTOSIZE);
 cv::Size size = cv::Size(320,240);
 cliente = std::thread(streamClient);
 frame = cv::Mat::zeros(size, CV_8UC1);
 
 while(true)
 {
 
  locker.lock();
  if(ready)
  {
   cv::imshow("Streaming", frame);
   ready=false;
  }
  locker.unlock();
  
  if(cv::waitKey(30)>=10)
  {
    cancel=false;
    break;
  }
 }
 cliente.join();
 cv::destroyWindow("Streaming");
 ~frame;
 return 0;
}


void streamClient(void)
{
 struct sockaddr_in server;
 std::vector<uchar> swap(10000);
 int len;
 int i;
 int bytes;
 cv::Mat code;
 sock=socket(AF_INET, SOCK_STREAM, 0);
 if (sock < 0)
 { 
  std::cout << "SOCKET Failed" << std::endl;
  return;
 }
 
 memset(&server, 0, sizeof(server));
 server.sin_family = AF_INET;
 server.sin_port = htons(PORT);
 server.sin_addr.s_addr = inet_addr(&server_ip[0]);
 
 if (connect(sock, (struct sockaddr*)&server, sizeof(server)) < 0)
 {
   std::cout << "Error de Conexión" << std::endl;
   return;
 }
 
 while(cancel)
 {
   bytes = recv(sock, &len, 4, 0);
   std::cout << bytes << " ; " << len << std::endl;
   bytes=0;
   for(i=0; i < len; i+=bytes)
   {
    bytes = recv(sock, &swap[bytes],(len-bytes), 0);
    if (bytes < 0)
    {
     std::cout << "Error de Lectura" << std::endl;
     return;
    }
   }
   swap.shrink_to_fit();
 
  locker.lock();
  code=cv::Mat(swap);
  frame=cv::imdecode(code,0);
  std::cout << swap.size() << " : " << bytes << std::endl;
  ready=true;
  locker.unlock();
  usleep(1000);
 }
return;
} 
 
 
 
 
 
 
  
 
