#include "mylist.h"
#include "myvector.h"
#include <iostream>
using namespace std;

void test_myvector()
{
    MyVector<int> v;
    v.PushBack(1);
    v.PushBack(2);
    v.PushBack(3);
    MyVector<int>::Iterator it = v.Begin();
//    while(it != v.End())
//    {
//        if(*it % 2 == 0)
//        {
//            v.Erase(it);
//        }
//        else
//        {
//            ++it;
//        }
//    }

        it = v.Insert(it,0);

    it = v.Begin();
    while(it != v.End())
    {
        cout<<*it<<" ";
        ++it;
    }
    cout<<endl;
}

void test_mylist()
{
    MyList<int> l;
    l.PushBack(1);
    l.PushBack(2);
    l.PushBack(3);
    l.PushBack(4);
    l.PushBack(4);
    l.PushBack(5);

    MyList<int>::Iterator it = l.Begin();
    while(it != l.End())
    {
        if(*it % 2 == 0)
        {
            l.Erase(it);
        }
        ++it;
    }

    it = l.Begin();
    while(it != l.End())
    {
        cout<<*it<<" ";
        ++it;
    }
    cout<<endl;
}

int main()
{
    /* test_myvector(); */
    test_mylist();
    return 0;
}
