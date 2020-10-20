#ifndef MANAGERBASE_H_
#define MANAGERBASE_H_

class ManagerBase{
public:
    virtual ~ManagerBase(){};
    virtual void init()=0;
    virtual void destroy()=0;
    virtual void update()=0;
};

// ManagerBase* ManagerBase::_instance = nullptr;
#endif 