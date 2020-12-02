/*
 * @Author: wimidev
 * @Date: 2020-12-02 10:18:28
 * @LastEditors: wimidev
 * @LastEditTime: 2020-12-02 11:45:15
 * @Description: 定时服务管理器
 */
#include "SchedulerManager.h"
#include <Arduino.h>

Timer* createTimer(TimerCallback callback, void* target, unsigned int inval=0, unsigned int once=0){
    Timer* newTimer = new Timer();
    newTimer->cache.status = TIMER_STATUS::STOP;
    newTimer->inval = inval;
    newTimer->callback = callback;
    newTimer->cache.isOnce = once;
    newTimer->cache.triggerCount = 0;
    newTimer->target = target;
    return newTimer;
}

SchedulerManager::SchedulerManager(){
    timerPool = std::vector<Timer*>();
    tick = 0;
}

SchedulerManager::~SchedulerManager(){
    
}

SchedulerManager* SchedulerManager::getInstance(){
    if(_instance == nullptr){
        _instance = new SchedulerManager();
    }
    return _instance;
}

void SchedulerManager::init(){

}

void SchedulerManager::destroy(){
    delete _instance;
}

void SchedulerManager::setTick(unsigned long _tick){
    tick = _tick;
}

void SchedulerManager::update(){
    for(int idx = 0; !timerPool.empty() && idx < timerPool.size(); idx++){
        TIMERCACHE* cache = &timerPool[idx]->cache;
        if(tick > 0 && cache->status == TIMER_STATUS::READY && 
        tick - timerPool[idx]->lastTrigget > timerPool[idx]->inval || 
        timerPool[idx]->inval == 0){
            TimerCallback callback = timerPool[idx]->callback;
            if(cache->isOnce){
                unschdule(idx);
            }
            timerPool[idx]->lastTrigget = tick;
            if(callback != nullptr) callback();
        }
    }
}

unsigned int SchedulerManager::schedule(const TimerCallback& callback, void* target, unsigned int inval, bool trigeNow, bool isOnce){
    Timer* timer = createTimer(callback, target, inval);
    //是否只触发一次
    if (isOnce) {
        timer->cache.isOnce = 1;
    }
    else{
        timer->cache.isOnce = 0;
    }
    timer->cache.status = TIMER_STATUS::READY;
    timer->cache.triggerCount = 0;
    if (trigeNow == true) {
        (timer->callback)();
    }
    timerPool.push_back(timer);
    unsigned int timerId = reinterpret_cast<unsigned int>(timer);
    Serial.printf("schdule su!, timerId = %d, size = %d\n", timerId, timerPool.size());
    return timerId;
}

unsigned int SchedulerManager::scheduleOnce(const TimerCallback& callback, void* target, unsigned int inval){
    return schedule(callback, target, inval, false, true);
}

void SchedulerManager::unschdule(void* target){
    unsigned int delCount = 0;
    for(int idx = timerPool.size()-1; !timerPool.empty() && idx >= 0; idx--){
       if(timerPool[idx]->target == target){
            timerPool.erase(timerPool.begin()+idx);
            delCount++;
            Serial.printf("unschdule su!, target = %d, size = %d\n", reinterpret_cast<unsigned int>(target), timerPool.size());
       }
    }
    if(delCount == 0){
        Serial.printf("fial to unschdule fail!, target = %d, size = %d\n", reinterpret_cast<unsigned int>(target), timerPool.size());
    }
}

void SchedulerManager::unschdule(unsigned int timerId){
    unsigned int delCount = 0;
    for (int idx = timerPool.size() - 1; !timerPool.empty() && idx >= 0; idx--) {
        if(timerId == reinterpret_cast<unsigned int> (timerPool[idx])) {
            timerPool.erase(timerPool.begin() + idx);
            delCount++;
            Serial.printf("unschdule su! timerid = %d, size = %d\n", timerId, timerPool.size());
        }
    }
    if (delCount == 0) {
        Serial.printf("fial to unschdule fail!, timerid = %d, size = %d\n", timerId, timerPool.size());
    }
}

SchedulerManager* SchedulerManager::_instance;