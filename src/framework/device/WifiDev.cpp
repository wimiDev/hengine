/*
 * @Author: wimidev
 * @Date: 2020-10-19 14:52:45
 * @LastEditors: wimidev
 * @LastEditTime: 2020-12-02 11:44:00
 * @Description: WIFI设备
 */
#include "WifiDev.h"
#include <Arduino.h>
#include "../manager/SchedulerManager.h"

int connectCount = 0;
WifiDev::WifiDev(){
    status = -1;
    _funcConnect = nullptr;
    schCheck = 0xffff;
}

WifiDev::~WifiDev(){

}

void WifiDev::connect(){
    //用定时器来检测网络连接状态
    schCheck = SchedulerManager::getInstance()->schedule(std::bind(&WifiDev::checkConnect, this), this, 1000, true);
}

void WifiDev::checkConnect(){
    status = WiFi.status();
    if(status != WL_CONNECTED){
        if(connectCount == 0){
            const char* ssid = "Input-your-ssid";
            const char* pass = "Input-your-pwd";
            debugWifiModel(WiFi.getMode());

            WiFi.mode(WIFI_STA);
            WiFi.begin(ssid, pass);
            Serial.println("WiFi.begin run.");
            Serial.print("Connecting\n");
        }
        connectCount++;
        debugWifiModel(WiFi.getMode());
        Serial.printf("status: %d \n", status);
        if(connectCount > 10){
             connectCount = 0; 
             Serial.printf("wifi connect timeout.");  
        }
        //现在有定时服务了就不需要在这里递归的去调用自己了
        // delay(1000); //临时用这个来做个延迟，后面换成别的
        // checkConnect();
    }else{
        Serial.print("Connected, IP address: ");
        Serial.println(WiFi.localIP());
        if(_funcConnect != nullptr) _funcConnect();
        //连上网之后注销定时器
        SchedulerManager::getInstance()->unschdule(schCheck);
    }
}

void WifiDev::debugWifiModel(int modeId){
    if(modeId == WIFI_AP){
        Serial.printf("wifi model: %s\n", "WIFI_AP");
    }
    else if(modeId == WIFI_STA){
    Serial.printf("wifi model: %s\n", "WIFI_STA");
    }
    else if(modeId == WIFI_AP_STA){
    Serial.printf("wifi model: %s\n", "WIFI_AP_STA");
    }
    else if(modeId == WIFI_OFF){
    Serial.printf("wifi model: %s\n", "WIFI_OFF");
    }
}

int WifiDev::getStatus(){
    return status;
}

bool WifiDev::getIsConnect(){
    //    0 : WL_IDLE_STATUS when Wi-Fi is in process of changing between statuses
    //    1 : WL_NO_SSID_AVAILin case configured SSID cannot be reached
    //    3 : WL_CONNECTED after successful connection is established
    //    4 : WL_CONNECT_FAILED if password is incorrect
    //    6 : WL_DISCONNECTED if module is not configured in station mode
    return status == WL_CONNECTED;
}

void WifiDev::onConnect(ConnectCallback callback){
    _funcConnect = callback;
}
