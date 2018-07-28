#include <iostream>
#include <cstdio>
#include <cstdlib>
using namespace std;

template<class T>
class ScopedPtr
{
    // 防不胜防系列(1)
    // friend void Test1();
    // ScopedPtr(const ScopedPtr<T>& ap){}
    // ScopedPtr<T>& operator=(const ScopedPtr<T>& ap){}
public:
    ScopedPtr(T* ptr = nullptr):_ptr(ptr)
    {
        cout<<"ScopedPtr()"<<endl;
    }
    ~ScopedPtr()
    {
        cout<<"~ScopedPtr()"<<endl;
        if(_ptr)
        {
            delete _ptr;
            _ptr = nullptr;
        }
    }

    T& operator*()
    {
        return *_ptr;
    }
    T* operator->()
    {
        return _ptr;
    }
    
// 依旧防不胜防系列(2) - 在类外定义
// public:
//     ScopedPtr(const ScopedPtr<T>& ap);
//     ScopedPtr<T>& operator=(const ScopedPtr<T>& ap);

// 还是防不胜防系列(3) - 虽然我即是私有成员,又只声明不定义
//                      但是你竟然可以即和我友元,又给我在类外定义 ( emmm...脑壳疼 )
    friend void Test1();
private:
    ScopedPtr(const ScopedPtr<T>& ap);
    ScopedPtr<T>& operator=(const ScopedPtr<T>& ap);

private:
    T* _ptr;
};

// template<class T>
// ScopedPtr<T>::ScopedPtr(const ScopedPtr<T>& ap)
// {
//     _ptr = ap._ptr;
// }
// 
// template<class T>
// ScopedPtr<T>& ScopedPtr<T>::operator=(const ScopedPtr<T>& ap)
// {
//     (void)ap;
// }

void Test1()
{
    ScopedPtr<int> p1(new int);
    ScopedPtr<int> p2(p1);
    p1 = p2;
}

int main()
{
    Test1();
    return 0;
}
