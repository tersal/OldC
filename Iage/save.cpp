#include <opencv2/core/core.hpp>
#include <iostream>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/opencv.hpp>
#include <vector>
#include <string>
#include <sstream>

using namespace cv;
using namespace std;

int main()
{
 stringstream stre;
 vector<Rect> faces;
 Mat image;
 Mat gray;
 Mat rec;
 image=imread("picture.jpg",CV_LOAD_IMAGE_COLOR);
 
 if( !image.data )
 {
  cout << "Error de Imagen" << endl;
  return -1; 
 }

 cvtColor(image,gray,CV_BGR2GRAY);
 vector<int> comp;
 comp.push_back(CV_IMWRITE_JPEG_QUALITY);
 comp.push_back(60);
 
 CascadeClassifier cascade;
 
 if( !cascade.load( "haarcascades/haarcascade_frontalface_alt.xml"))
 {
  cout << "Error Cargando archivo";
  return -1;
 }
 cascade.detectMultiScale( gray,faces,1.1, 3,0|CV_HAAR_SCALE_IMAGE, Size(20,20)); 
 for( int i = 0; i < faces.size(); i++)
 {
  image(Rect(faces[i].x, faces[i].y, faces[i].width, faces[i].height)).copyTo(rec);
  stre << i << ".jpg";
  imwrite(stre.str(),rec,comp);
  stre.str("");
 }

 return 0;

}
