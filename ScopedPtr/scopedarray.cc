#include <iostream>
#include <cstdio>
#include <cstdlib>
using namespace std;

template<class T>
class ScopedArray
{
public:
    ScopedArray(T* ptr = nullptr)
        :_ptr(ptr)
    {
        cout<<"ScopedArray()"<<endl;
    }
    ~ScopedArray()
    {
        cout<<"~ScopedArray()"<<endl;
        if(_ptr)
        {
            delete _ptr;
            _ptr = nullptr;
        }
    }

    // 数组支持随机访问
    T& operator[](size_t index)
    {
        return _ptr[index];
    }

    const T& operator[](size_t index)const
    {
        return _ptr[index];
    }
    
private:
    ScopedArray(const ScopedArray<T>&);
    ScopedArray<T>& operator=(const ScopedArray<T>&);

private:
    T* _ptr;
};

void Test1()
{
    ScopedArray<int> sap(new int[10]);
    sap[0] = 0;
    cout<<sap[0]<<endl;
}

int main()
{
    Test1();
    return 0;
}
