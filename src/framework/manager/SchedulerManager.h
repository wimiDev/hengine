#ifndef SCHEDULERMANAGER_H
#define SCHEDULERMANAGER_H
#include <functional>
#include <vector>
#include "ManagerBase.h"

#define TIMER_LIMIT 50
// typedef void (*TimerCallback)();
// #define TimerCallback std::function<void (void)>
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
    // unsigned int schedule(TimerCallback callback, unsigned int inval, bool trigeNow=false, bool isOnce=false);
    unsigned int schedule(const TimerCallback& callback, void* target, unsigned int inval, bool trigeNow=false, bool isOnce=false);
    unsigned int scheduleOnce(const TimerCallback& callback, void* target, unsigned int inval);
    void unschdule(unsigned int timerId);
    void unschdule(void* target);
private:
    //Timer timerPool[TIMER_LIMIT];
    std::vector<Timer*> timerPool;
    static SchedulerManager* _instance;
    unsigned long tick;
    SchedulerManager();
};

#endif