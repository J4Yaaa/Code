#include <iostream>
using namespace std;
#include <pthread.h>
#include <unistd.h>

// 经典懒汉模式(线程不安全)
// class Singleton
// {
// protected:
//     Singleton(){} //将构造函数设置为保护,便于其他类继承
// private:
//     Singleton(const Singleton& s) = delete; // 实现防拷贝
//     Singleton& operator=(const Singleton& s) = delete; // 实现防赋值
// public:
//     static Singleton* getInstance();
// private:
//     static Singleton* p;
// };
// 
// Singleton* Singleton::p = NULL;
// Singleton* Singleton::getInstance()
// {
//     if(p == NULL)
//     {// 在第一次调用的时候才去new一个对象
//         p = new Singleton();
//     }
//     return p;
// }
// 
// 线程安全的懒汉模式
// class Singleton
// {
// protected:
//     Singleton()
//     {// 初始化互斥锁
//         pthread_mutex_init(&lock_,NULL);
//     }
// private:
//     Singleton(const Singleton& s) = delete; // 实现防拷贝
//     Singleton& operator=(const Singleton& s) = delete; // 实现防赋值
// public:
//     static pthread_mutex_t lock_;
//     static Singleton* getInstance();
// private:
//     static Singleton* p; //加volatile防止编译器过度优化
// };
// 
// pthread_mutex_t Singleton::lock_;
// Singleton* Singleton::p = NULL;
// Singleton* Singleton::getInstance()
// {
//     if(p == NULL)
//     {
//         pthread_mutex_lock(&lock_);
//         if(p == NULL)
//         {
//             p = new Singleton();
//         }
//         pthread_mutex_unlock(&lock_);
//     }
//     return p;
// }
// 
// 内部静态变量实现懒汉模式
// class Singleton
// {
// protected:
//     Singleton()
//     {
//         pthread_mutex_init(&lock_,NULL);
//     }
// private:
//     Singleton(const Singleton& s) = delete;
//     Singleton* operator=(const Singleton& s) = delete;
// public:
//     static pthread_mutex_t lock_;
//     static Singleton* getInstance();
// };
// 
// pthread_mutex_t Singleton::lock_;
// Singleton* Singleton::getInstance()
// {
//     pthread_mutex_lock(&lock_);
//     static Singleton obj;
//     pthread_mutex_unlock(&lock_);
//     return &obj;
// }
// 
// 饿汉模式
class Singleton
{
protected:
    Singleton(){}
private:
    Singleton(const Singleton& s) = delete;
    Singleton* operator=(const Singleton& s) = delete;
private:
    static Singleton* p;
public:
    static Singleton* getInstance();
};

Singleton* Singleton::p = new Singleton();

Singleton* Singleton::getInstance()
{
    return p;
}
