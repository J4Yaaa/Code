#include <iostream>
using namespace std;

template<class T,size_t N>
struct __DequeIterator
{
    typedef __DequeIterator<T,N> Self;
    T* _first;
    T* _last;
    T* _cur;
    T** _node;
    T& operator* ()
    {
        return *_cur;
    }
    T& operator++()
    {
        ++_cur;
        if(_cur == _last)//已经到结尾了
        {
            ++_node;
            _first = *_node;
            _last = _first + N;
            _cur = _first;
        }
        return _cur;
    }
    bool operator==(Self& s)
    {
        return _cur == s._cur;
    }
};

template<class T,size_t N = 10> //10表示每个buf的大小
class Deque
{
public:
    typedef __DequeIterator<T,N> Iterator;
    T** _ptrArr; //中控的指针数组
    size_t size;
    Iterator _start;
    Iterator _finish;
};
