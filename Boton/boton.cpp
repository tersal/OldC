#include <iostream>
#include <string>
#include <sstream>
#include <Poco/Net/HTTPRequest.h>
#include <Poco/Net/HTTPClientSession.h>
#include <Poco/Net/HTTPResponse.h>
#include <Poco/StreamCopier.h>
#include <Poco/Path.h>
#include <Poco/URI.h>
#include <Poco/Exception.h>
#include <fstream>

int main() 
{
 std::cout << "Alarm Activated";
 string util;
 int ID;
 ifstream file ("/root/v2/DroneID");
 url="http://192.168.2.250/Services/Json/eDemo/EmergenciasService.svc/SetEmergency/?DroneID=";

 if (file.is_open())
 {
  getline(file,util);
  stringstream(utli) >> ID;
  file.close();
 }

 Poco::URI uri(url);
 Poco::Net::HTTPClientSession session(uri.getHost(), uri.getPort());

 string path(uri.getPathAndQuery());
 if (util.empty()) path="/";

 Poco::Net::HTTPRequest req(Poco::Net::HTTPRequest::HTTP_GET, path, HTTPMessage::HTTP_1_1);
 req.setContentType("application/json");
 string body("\'{\"DroneID\": 1}\'");
 req.setContentLength(body.length());
 session.sendRequest(req) << body;

}
  
