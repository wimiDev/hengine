/*
 * @Author: wimidev
 * @Date: 2020-12-02 10:32:14
 * @LastEditors: wimidev
 * @LastEditTime: 2020-12-02 10:52:41
 * @Description: 核心,主要负责应用生命周期管理和提供一些通用功能。
 */
#ifndef CORE_H
#define CORE_H

//arduino
#include <Arduino.h>

// manager
#include "manager/SchedulerManager.h"
#include "manager/NetManager.h"

// interface
#include "interface/IRuntime.h"

//core
class Core: public IRuntime{
public:
    Core(){

    }

    virtual ~Core(){

    }

    void init() override{
        SchedulerManager::getInstance()->init();
        NetManager::getInstance()->init();
    }

    void update() override{
        unsigned long tickStart = millis();
        SchedulerManager::getInstance()->setTick(tickStart);
        SchedulerManager::getInstance()->update();
        NetManager::getInstance()->update();
    }

    void destroy() override{

    }

};
extern Core core;

#endif