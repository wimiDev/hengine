// #include "framework/device/WifiDev.h"

// void setup() {
//   WifiDev().connect();
// }

// void loop() {

// }

#include "framework/manager/NetManager.h"

void setup() {
  NetManager::getInstance()->init();
}

void loop() {

}

