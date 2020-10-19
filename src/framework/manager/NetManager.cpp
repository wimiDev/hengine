//#ifdef _ESP
#include "NetManager.h"
#include "../../sdk/weather/WeatherNow.h"
#include "../core.h"

NetManager::NetManager(){
	
}

NetManager::~NetManager(){

}

NetManager* NetManager::getInstance(){
    if(_instance == nullptr){
        _instance = new NetManager();
    }
    return _instance;
}

void NetManager::init(){
    connectWifi();
}

void NetManager::destroy(){
  delete _instance;
}

void NetManager::update(){

}

void NetManager::connectWifi(){
    devWifi.connect();
    devWifi.onConnect(std::bind([this](){
        // connectToServer();
        timing();
    }));
}

void NetManager::connectToServer(){
//     const char* host = "192.168.0.137";
//     const int port = 18001;
//     if(wifiClient.connected()){
//     if (wifiClient.available())
//       {
//         String line = wifiClient.readStringUntil('\n');
//         Serial.println(line);
//       }
//      wifiClient.print("hello\n");
//   }else{
//     wifiClient.connect(host, port);
//     Serial.printf("connected to %s:%d\n", host, port);
//   }
}

void NetManager::timing(){
    // const char* ntpServerName = "time.nist.gov";
    const char* ntpServerName = "ntp4.aliyun.com";
    IPAddress timeServerIP;
    WiFi.hostByName(ntpServerName, timeServerIP);
    ntpClient.requireTime(timeServerIP, std::bind([this](unsigned long int tmp){
        osClock = millis(); //系统是钟，秒
        unixTmp = tmp;
        EventManager::getInstance()->dispatch((unsigned int)CoreEventIdx::NTP_SU , nullptr);
    }, std::placeholders::_1));
}

Date* NetManager::timeNow(){
    Date* date = new Date();
    date->init((millis() - osClock)/1000 + unixTmp);
    return date;
}

void NetManager::sendHttpRequest(std::string reqStr, std::function<void (int code, void* data)> callback){
    httpRequest.request(reqStr, callback);
}

NetManager* NetManager::_instance = nullptr;

//#endif
