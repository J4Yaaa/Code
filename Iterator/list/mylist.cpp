#include <iostream>
using namespace std;
#include "mylist.h"
#include <list>

//依旧可以修改
//template<class T>
//void PringList(const MyList<T>& l)
//{
//    MyList<int>::Iterator it1 = l.Begin();
//    while(it1 != l.End())
//    {
//      //普通指针可以改变其值
//        *it1 = 10;
//        cout<<*it1<<" ";
//        ++it1;
//    }
//    cout<<endl;
//}

template<class T>
void PringList(const MyList<T>& l)
{
    MyList<int>::ConstIterator it1 = l.Begin();
    while(it1 != l.End())
    {
        //当前就不可以改变值了
        //*it1 = 10;
        cout<<*it1<<" ";
        ++it1;
    }
    cout<<endl;
}

void test_iterator()
{
    MyList<int> l;
    l.PushBack(1);
    l.PushBack(2);
    l.PushBack(3);
    l.PushBack(4);
    l.PushBack(5);
    PringList(l);
}

void link_sort()
{
    list<int> l;
    l.push_back(4);
    l.push_back(5);
    l.push_back(1);
    l.push_back(3);
    l.push_back(7);
    l.push_back(6);
    l.push_back(0);
    l.sort();
    list<int>::iterator it1 = l.begin();
    while(it1 != l.end())
    {
        cout<<*it1<<" ";
        ++it1;
    }
    cout<<endl;
}

int main()
{
    /* test_iterator(); */
    link_sort();
    return 0;
}
