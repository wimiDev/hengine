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
};

#endif