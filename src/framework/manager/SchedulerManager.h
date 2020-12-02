/*
 * @Author: wimidev
 * @Date: 2020-12-02 10:18:28
 * @LastEditors: wimidev
 * @LastEditTime: 2020-12-02 10:51:19
 * @Description: 定时服务管理器
 */
#ifndef SCHEDULERMANAGER_H
#define SCHEDULERMANAGER_H
#include <functional>
#include <vector>
#include "ManagerBase.h"

#define TIMER_LIMIT 50

typedef std::function<void (void)> TimerCallback;

enum TIMER_STATUS{
    STOP = 0,
    READY
};

struct TIMERCACHE{
    unsigned char isOnce:1;
    unsigned char status:3;
    unsigned char triggerCount:4;
};

struct Timer
{
    unsigned int inval;
    TimerCallback callback;
    TIMERCACHE cache; //珍惜内存，用位域实现了
    void* target;
    unsigned long lastTrigget;
};

class SchedulerManager: public ManagerBase{
public:
    virtual ~SchedulerManager();
    void init();
    void destroy();
    void update();

    static SchedulerManager* getInstance();

    void setTick(unsigned long _tick);
    unsigned int schedule(const TimerCallback& callback, void* target, unsigned int inval, bool trigeNow=false, bool isOnce=false);
    unsigned int scheduleOnce(const TimerCallback& callback, void* target, unsigned int inval);
    void unschdule(unsigned int timerId);
    void unschdule(void* target);
    
private:

    std::vector<Timer*> timerPool;
    static SchedulerManager* _instance;
    unsigned long tick;
    SchedulerManager();
};

#endif