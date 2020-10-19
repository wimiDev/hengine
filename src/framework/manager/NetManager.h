
#ifndef NETMANAGER_H_
#define NETMANAGER_H_
//#ifdef _ESP
#include <ESP8266WiFi.h>
#include <functional>

#include "ManagerBase.h"
#include "../device/WifiDev.h"
#include "../net/NtpClient.h"
#include "../net/HttpRequest.h"
#include "../math/Date.h"

class NetManager: public ManagerBase{
public: 
  virtual ~NetManager();
  void init();
  void destroy();
  void update();
  void connectToServer();
  void connectWifi();
  void timing();
  Date* timeNow();
  void sendHttpRequest(std::string reqStr, std::function<void (int code, void* data)> callback);
  static NetManager* getInstance();
private:
  NetManager();
  static NetManager* _instance;
  //wifi
  HttpRequest httpRequest;
  WifiDev devWifi;
  // WiFiClient wifiClient;
  NtpClient ntpClient;

  //date
  unsigned long int osClock;//完成授时后记录的系统时钟
  unsigned long int unixTmp;//授时之后的时间戳
};
//#endif

#endif
