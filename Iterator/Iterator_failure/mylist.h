#pragma once
#include <list>
#include <assert.h>

template<class T>
struct ListNode
{
    ListNode<T>* _prev;
    ListNode<T>* _next;
    T _data;
    ListNode(const T& x):_prev(nullptr),_next(nullptr),_data(x)
    {}
};

template<class T,class Ref,class Ptr>
struct __ListIterator
{
    typedef ListNode<T> Node;
    typedef __ListIterator<T,Ref,Ptr> Self;//为了便于书写，将自己写为Self
    Node* _node;

    __ListIterator(Node* node):_node(node)
    {}

    //只有operator* 和 operator-> 可能去改变链表的值
    //所以只要保证operator* 和 operator-> 返回的是const值就好
    //但是这样就得实现两分逻辑相同的类，只有* 和 -> 的操作不一样
    //为了不那么冗余，于是模板参数中有 Ref 和 Ptr
    //<T,const T&, const T*>
    Ref operator*()
    {
        return _node->_data;
    }

    Ptr operator->()
    {
        return &(operator*());
    }

    Self& operator++()
    {
        _node = _node->_next;
        return *this; 
    }

    Self& operator++(int)
    {
        Self tmp(*this);
        _node = _node->_next;
        return tmp;
    }

    Self& operator--()
    {
        _node = _node->_prev;
        return *this;
    }

    Self& operator--(int)
    {
        Self tmp(*this);
        _node = _node->_prev;
        return tmp;
    }

    bool operator!=(const Self& s)const
    {
        return (_node != s._node);
    }

    bool operator==(const Self& s)const
    {
        return (_node == s._node);
    }
};

template<class T>
class MyList
{
    typedef ListNode<T> Node;
public:
    typedef __ListIterator<T,T&,T*> Iterator;
    typedef __ListIterator<T,const T&, const T*> ConstIterator;
    MyList():_head(new Node(T()))
    {
        _head->_next = _head;
        _head->_prev = _head;
    }

    void PushBack(const T& x)
    {
        Insert(End(),x);
    }

    void PopBack()
    {
        Erase(--End());
    }

    void PushFront(const T& x)
    {
        Insert(Begin(),x);
    }

    void PopFront()
    {
        Erase(Begin());
    }

    Iterator Begin()
    {
        return Iterator(_head->_next);
    }

    Iterator End()
    {
        return Iterator(_head);
    }

    ConstIterator Begin() const
    {
        return ConstIterator(_head->_next);
    }

    ConstIterator End() const
    {
        return ConstIterator(_head);
    }

    Iterator Insert(Iterator pos,const T& x)
    {
        Node* cur = pos._node;
        Node* pre = cur->_prev;
        Node* new_node = new Node(x);

        new_node->_next = cur;
        cur->_prev = new_node;

        pre->_next = new_node;
        new_node->_prev = pre;
        return new_node;
    }

    Iterator Erase(Iterator pos)
    {
        assert(pos != Iterator(_head));//构造了一个_head的你明对象
        Node* to_delete = pos._node;
        Node* pre = to_delete->_prev;
        Node* next = to_delete->_next;
        
        pre->_next = next;
        next->_prev = pre;
        delete to_delete;
        return next;
    }

    //不接收返回值也不会导致迭代器失效 -  传引用
//    Iterator Erase(Iterator pos)
//    {
//        assert(pos != Iterator(_head));
//        Node* to_delete = pos._node;
//        Node* pre = to_delete->_prev;
//        Node* next = to_delete->_next;
//        
//        pre->_next = next;
//        next->_prev = pre;
//        delete to_delete;
//        pos = pre;
//        return pre;
//    }

protected:
    Node* _head;
};
