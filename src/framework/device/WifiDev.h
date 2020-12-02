/*
 * @Author: wimidev
 * @Date: 2020-10-19 14:52:45
 * @LastEditors: wimidev
 * @LastEditTime: 2020-12-02 11:08:48
 * @Description: WIFI设备
 */
#ifndef WIFIDEV_H
#define WIFIDEV_H
#include <ESP8266WiFi.h>
#include <functional>

typedef std::function<void (void)> ConnectCallback;

class WifiDev{
public:
    WifiDev();
    virtual ~WifiDev();
    void connect();
    void onConnect(ConnectCallback callback);
    void debugWifiModel(int modeId);
    int getStatus();
    bool getIsConnect();
    
private:
    void checkConnect();
    int status;
    ConnectCallback _funcConnect;
    unsigned int schCheck;
};

#endif