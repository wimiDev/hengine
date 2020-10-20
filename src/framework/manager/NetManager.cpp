//#ifdef _ESP
#include "NetManager.h"

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

    }));
}

NetManager* NetManager::_instance = nullptr;

//#endif
