#include <iostream>
using namespace std;
#include <vector>
#include <list>

//迭代器失效:
//迭代器被删除以后已经无效，对其结果不能进行解引用和++
//解决方法：
//接收返回值

void test_list()
{
    //删除链表中所有的偶数项
    list<int> l;
    l.push_back(1);
    l.push_back(2);
    l.push_back(3);
    l.push_back(4);
    l.push_back(4);
    l.push_back(4);
    l.push_back(5);
    l.push_back(6);

//以下操作是错误的，因为迭代器失效，it已经不再链表上了，已经被删除掉了(类似于野指针问题)
//    list<int>::iterator it = l.begin();
//    while(it != l.end())
//    {
//        if(*it % 2 == 0)
//        {
//            l.erase(it);
//        }
//        ++it;
//    }

    //解决方法：erase会返回所删除的节点的下一个位置，所以把返回值保存起来就好
    list<int>::iterator it = l.begin();
    while(it != l.end())
    {
        if(*it % 2 == 0)
        {
            it = l.erase(it);
        }
        else
        {
            ++it;
        }
    }

    list<int>::iterator it1 = l.begin();
    while(it1 != l.end())
    {
        cout<<*it1<<" ";
        ++it1;
    }
    cout<<endl;
}

void test_vector()
{
    vector<int> v;
    v.push_back(1);
    v.push_back(2);
    v.push_back(3);
    v.push_back(4);
    v.push_back(4);
    v.push_back(5);
    v.push_back(6);

//迭代器失效：同上
//可能会少删
//    vector<int>::iterator it = v.begin();
//    while(it != v.end())
//    {
//        if(*it % 2 == 0)
//        {
//            v.erase(it);
//        }
//        ++it;
//    }

    //解决方法：接收返回值
    vector<int>::iterator it = v.begin();
    while(it != v.end())
    {
        if(*it % 2 == 0)
        {
            it = v.erase(it);
        }
        else
        {
            ++it;
        }
    }

    //vector 在插入的时候都有可能迭代器失效
    //和扩容有关，会开辟新的空间，将原先数据拷贝出去，it指针以被释放，所以迭代器失效

    it = v.begin();
    while(it != v.end())
    {
        cout<<*it<<" ";
        ++it;
    }
    cout<<endl;
}

int main()
{
    /* test_list(); */
    test_vector();
    return 0;
}
