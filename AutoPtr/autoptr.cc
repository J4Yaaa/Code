#include <iostream>
#include <cstdio>
#include <cstdlib>
using namespace std;

bool doSomething()
{
    // 如果时间执行失败了就返回false
    return false;
}

// 为了避免内存泄漏和文件描述符泄漏,我们需要写出以下这样冗余的代码
// 我们需要一种方法让他自动的释放掉
void Test1()
{
    int* p1 = new int[2];
    FILE* pf = fopen("test","r");
    // 1.如果打开文件失败,就需要释放p1的空间
    if(pf == NULL)
    {
        delete[] p1;
    }

    // 2.如果执行事件失败,就需要释放p1的空间,并且关闭pf文件
    if(!doSomething())
    {
        delete[] p1;
        fclose(pf);
        return;
    }

    // 3.如果抛出了异常,我们捕获异常以后,也需要释放p1的空间,并且关闭文件描述符
    try
    {
        throw 1;
    }
    catch(int err)
    {
        delete[] p1;
        fclose(pf);
        return;
    }

    // 4.逻辑正常结束,也需要释放空间和关闭文件
    delete[] p1;
    fclose(pf);
    return;
}

// 智能指针主要就是解决动态申请内存和自动释放资源的问题
// 1.管理指针
// 2.像指针一样来使用
template<class T>
class AutoPtr
{
public:
    // 管理指针的操作
    AutoPtr(T* ptr):_ptr(ptr = nullptr)
    {
        cout<<"AutoPtr()"<<endl;
    }
    ~AutoPtr()
    {
        cout<<"~AutoPtr()"<<endl;
        if(_ptr)
            delete _ptr;
    }

    // 像指针一样使用的操作
    // a) 解引用操作
    T& operator*()
    {
        return *_ptr;
    }
    // b) 通过成员访问符去访问成员
    T* operator->()
    {
        return _ptr;
    }
    
    // 成员函数
    // c)拷贝构造函数的解决方法
    //   让 ap 交出对资源的管理权限给this
    AutoPtr(AutoPtr<T>& ap)
        :_ptr(ap._ptr)
    {
        ap._ptr = nullptr; // 这个解决浅拷贝的方法真是.....一言难尽....防不胜防啊....
    }

    AutoPtr<T>& operator=(AutoPtr<T>& ap)
    {
        if(this != &ap)
        {
            // 如果当前_ptr管理了空间,那么其他对象一定不会管理这块空间 
            // 因为拷贝构造会将原对象的资源管理权会交出
            // 也就述说 AutoPtr 中一个资源只能被一个对象所管理
            if(_ptr) 
                delete _ptr;
            _ptr = ap._ptr; 
            ap._ptr = nullptr;
        }
        return *this;
    }

private:
    T* _ptr;
};

class A
{
public:
    int _a;
};

void Test2()
{
    // 这时候把指针交给类来管理
    // a)
    AutoPtr<int> ap1(new int);
    *ap1 = 10;
    cout<<"*ap1 = "<<*ap1<<endl;
    // b)
    AutoPtr<A> ap2(new A);
    ap2->_a = 10;
    // operator->->_a; 理论上应该写为 ap2->->_a,但是编译器优化以后,我们就可以只写一个箭头
    cout<<"ap2->_a = "<<ap2->_a<<endl;

}

void Test3()
{
    // c) 拷贝构造 - 会有浅拷贝的问题
    AutoPtr<int> ap3(new int);
    AutoPtr<int> ap4(ap3);

    // d) 复制运算符的重载
    AutoPtr<int> ap5(new int);
    ap4 = ap5;

    // 原生指针在赋值以后,两个指针都可以操作指向的空间
    // 但是因为 AutoPtr 中运用交出管理权的方法
    // 那么原本的指针就会为NULL,就不可以管理那段空间了
}

int main()
{
    /* Test2(); */
    /* Test3(); */
    return 0;
}
