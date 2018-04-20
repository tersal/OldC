#include <opencv2/opencv.hpp>
#include <iostream>
#include <Poco/URIStreamOpener.h>
#include <Poco/StreamCopier.h>
#include <Poco/Path.h>
#include <Poco/URI.h>
#include <Poco/Exception.h>
#include <Poco/Net/HTTPStreamFactory.h>
#include <memory>
#include <vector>
#include <string>
#include <sstream>
#include <stdio.h>
#include <malloc.h>

using Poco::URIStreamOpener;
using Poco::StreamCopier;
using Poco::Path;
using Poco::URI;
using Poco::Exception;
using Poco::Net::HTTPStreamFactory;
using namespace std;
static bool factoryLoaded = false;

cv::Mat cargar(string url)
{
  if(!factoryLoaded){
   HTTPStreamFactory::registerFactory();
   factoryLoaded=true;
  }
 
 URI uri(url);
 std::auto_ptr<std::istream> pStr(URIStreamOpener::defaultOpener().open(uri));
 
 string str;
 StreamCopier::copyToString(*pStr.get(),str);
 vector<char> data(str.begin(), str.end() );
 cv::Mat data_mat(data);
 cv::Mat image(cv::imdecode(data_mat,1));
 return image;
};

int main()
{
 stringstream stre;
 vector<cv::Rect> faces;
 try
 {
  cv::Mat image = cargar("http://10.42.0.32/jpg/image.jpg?resolution=800x600");
  cv::Mat gray;
  cv::Mat rec;
  if(!image.data)
  {
    cout << "Error de imagen" << endl;
    return -1;
  }
  cv::cvtColor(image,gray,CV_BGR2GRAY);
  cv::equalizeHist(gray,gray);
  vector<int> comp;
  comp.push_back(CV_IMWRITE_JPEG_QUALITY);
  comp.push_back(40);

  cv::CascadeClassifier cascade;
 
  if(!cascade.load("haarcascades/haarcascade_frontalface_alt.xml"))
  {
   cout << "Error Cargando archivo";
   return -1;
  }
 
  cascade.detectMultiScale(gray, faces, 1.1 , 3, 0|CV_HAAR_SCALE_IMAGE, cv::Size(50,50));
  for(int i=0; i<faces.size();i++)
  {
   gray(cv::Rect(faces[i].x, faces[i].y, faces[i].width, faces[i].height)).copyTo(rec);
   stre << i << ".jpg";
   cv::imwrite(stre.str(),rec,comp);
   stre.str("");
  }
  
 }
 catch (exception& e)
 {
  cout << "Exception: " << e.what() << endl;
 }
 return 0;

}
 



