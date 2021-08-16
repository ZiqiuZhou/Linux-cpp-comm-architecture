//
// Created by dietrich on 8/5/21.
//

#ifndef LINUX_CPP_COMM_ARCHITECTURE_NGX_C_MEMORY_H
#define LINUX_CPP_COMM_ARCHITECTURE_NGX_C_MEMORY_H

#include <stddef.h>  //NULL
//内存相关类
class CMemory
{
private:
    CMemory() {}  //构造函数，因为要做成单例类，所以是私有的构造函数

public:
    ~CMemory(){};

private:
    static CMemory *m_instance;

public:
    static CMemory* GetInstance() //单例
    {
        if(m_instance == nullptr)
        {
            //锁
            if(m_instance == nullptr)
            {
                m_instance = new CMemory(); //第一次调用不应该放在线程中，应该放在主进程中，以免和其他线程调用冲突从而导致同时执行两次new CMemory()
                static CGarhuishou cl;
            }
            //放锁
        }
        return m_instance;
    }
    class CGarhuishou
    {
    public:
        ~CGarhuishou()
        {
            if (CMemory::m_instance)
            {
                delete CMemory::m_instance; //这个释放是整个系统退出的时候，系统来调用释放内存的哦
                CMemory::m_instance = nullptr;
            }
        }
    };
    //-------

public:
    void *AllocMemory(int memCount,bool ifmemset);
    void FreeMemory(void *point);

};

#endif //LINUX_CPP_COMM_ARCHITECTURE_NGX_C_MEMORY_H