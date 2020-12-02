/*
 * @Author: wimidev
 * @Date: 2020-12-02 11:00:34
 * @LastEditors: wimidev
 * @LastEditTime: 2020-12-02 11:01:16
 * @Description: 生命周期接口
 */
#ifndef IRUNTIME_H
#define IRUNTIME_H

class IRuntime{
public:
   virtual ~IRuntime(){};
   virtual void init()=0;
   virtual void destroy()=0;
   virtual void update()=0;
};

#endif