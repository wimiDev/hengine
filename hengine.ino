/*
 * @Author: wimidev
 * @Date: 2020-10-19 14:40:07
 * @LastEditors: wimidev
 * @LastEditTime: 2020-12-02 10:53:09
 * @Description: Arduino工程文件
 */
#include "src/framework/core.h"

Core core;

void setup() {
  Serial.begin(115200);
  core.init();
}

void loop() {
  core.update();
}

