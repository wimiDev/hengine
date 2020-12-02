/*
 * @Author: wimidev
 * @Date: 2020-10-19 16:00:05
 * @LastEditors: wimidev
 * @LastEditTime: 2020-12-02 10:53:36
 * @Description: 管理器基类
 */
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