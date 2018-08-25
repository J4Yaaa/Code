#pragma once
#include <stdlib.h>

template<class T>
class MyVector
{
public:
    typedef T* Iterator;
    typedef const T* ConstIterator;//const 迭代器
    MyVector():_start(nullptr),_finish(nullptr),_endofstorage(nullptr)
    {}

    ~MyVector()
    {
        if(_start)
        {
            delete _start;
            _start = _finish = _endofstorage;
        }
    }

    size_t Capacity() const
    {
        return _endofstorage - _start;
    }

    size_t Size() const 
    {
        return _finish - _start;
    }

    void Expand(size_t n)
    {
        //因为 resize reserve 不会缩容，所以得预先判断一下
        if(n > Capacity())
        {
            T* tmp = new T[n];
            size_t size = Size();
            for(size_t i = 0; i < size; ++i)
            {
                tmp[i] = _start[i];
            }
            delete _start;
            _start = tmp;
            _finish = _start + size;
            _endofstorage = _start + n;
        }
    }

    void PushBack(const T& x)
    {
        if(_finish == _endofstorage)
        {
            if(Capacity() == 0)
            {
                Expand(3);
            }
            else
            {
                Expand(2*Capacity());
            }
        }
        *_finish = x;
        ++_finish;
    }

    void PopBack()
    {
        assert(_finish > _start);
        --_finish;
    }

    void Reserve(size_t n)
    {
        if(n > Capacity())
        {
            Expand(n);
        }
    }

    void Resize(size_t n,T x = T())
    {
        if(n > Size())
        {
            if(n > Capacity())
            {
                Expand(n);
            }
            T* p = _finish;
            while(p != _endofstorage)
            {
                *p = x;
                ++p;
            }
        }
        else if(n <= Size())
        {
            _finish = _start + n;
        }
        _finish = _start + n;
    }

    T& operator[](size_t pos)
    {
        assert(pos < Size() && pos >= 0);
        return _start[pos];
    }

    const T& operator[](size_t pos)const
    {
        assert(pos < Size() && pos >= 0);
        return _start[pos];
    }

    Iterator Begin()
    {
        return _start;
    }

    Iterator End()
    {
        return _finish;
    }

    ConstIterator Begin() const
    {
        return _start;
    }

    ConstIterator End() const
    {
        return _finish;
    }
protected:
    Iterator _start;
    Iterator _finish;
    Iterator _endofstorage;
};
