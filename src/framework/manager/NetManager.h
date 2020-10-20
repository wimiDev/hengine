
#ifndef NETMANAGER_H_
#define NETMANAGER_H_
//#ifdef _ESP
#include <ESP8266WiFi.h>
#include <functional>

#include "ManagerBase.h"
#include "../device/WifiDev.h"

class NetManager: public ManagerBase{
public: 
  virtual ~NetManager();
  void init();
  void destroy();
  void update();
  void connectWifi();
  static NetManager* getInstance();
private:
  NetManager();
  static NetManager* _instance;
  //wifi
  WifiDev devWifi;
};
//#endif

#endif
