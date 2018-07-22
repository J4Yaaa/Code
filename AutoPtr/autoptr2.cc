#include <iostream>
#include <cstdio>
#include <cstdlib>
using namespace std;

template<class T>
class AutoPtr
{
public:
    AutoPtr(T* ptr = nullptr)
        :_ptr(ptr)
         ,_owner(true)
    {
        cout<<"AutoPtr()"<<endl;
        if(_ptr == nullptr)
            _owner = false;
    }
    ~AutoPtr()
    {
        if(_owner && _ptr)
        {
            cout<<"~AutoPtr()"<<endl;
            delete _ptr;
            _ptr = nullptr;
            _owner = false;
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
    
    AutoPtr(const AutoPtr<T>& ap)
        :_ptr(ap._ptr)
         ,_owner(ap._owner)
    {
        ap._owner = false;
    }

    AutoPtr<T>& operator=(const AutoPtr<T>& ap)
    {
        if(this != &ap)
        {
            if(_owner && _ptr) 
                delete _ptr;
            _owner = ap._owner;
            _ptr = ap._ptr; 
            ap._owner = false;
        }
        return *this;
    }

public:
    T* _ptr;
    mutable bool _owner; // 为解决交出资源管理权的问题,_owner表示当前是不是这个对象 管理着资源
};

void Test1()
{
    AutoPtr<int> ap1(new int);
    AutoPtr<int> ap2(ap1);
    AutoPtr<int> ap3(new int);
    ap2 = ap3;
}

int main()
{
    Test1();
    return 0;
}
