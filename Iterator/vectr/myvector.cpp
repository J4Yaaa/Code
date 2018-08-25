#include "myvector.h"
#include <iostream>
using namespace std;
#include <sys/time.h>
#include <assert.h>
#include <vector>
#include <string>
#include <algorithm>

void PrintVector(const MyVector<int>& v1)
{
    cout<<"size = "<<v1.Size()<<endl;
    cout<<"capacity = "<<v1.Capacity()<<endl;
    MyVector<int>::ConstIterator it1 = v1.Begin();
    while(it1 != v1.End())
    {
        cout<<*it1<<" ";
        ++it1;
    }
    cout<<endl;
}

void test_myvector()
{
    MyVector<int> v1;
    v1.PushBack(5);
    v1.PushBack(4);
    v1.PushBack(3);
    v1.PushBack(2);
    v1.PushBack(1);

    PrintVector(v1);

    cout<<v1[10]<<endl;
}

static int64_t GetUs() {
    struct timeval time;
    gettimeofday(&time, NULL);
    return 1000000 * time.tv_sec + time.tv_usec;

}

void TestReserve()
{
    const int N = 1000*1000*10;
    MyVector<int> v1;
    int64_t start_time = GetUs();
    for(int i = 0; i < N; ++i)
    {
        v1.PushBack(i);
    }
    int64_t finish_time = GetUs();
    printf("v1 time: %ld\n",finish_time - start_time);

    MyVector<int> v2;
    start_time = GetUs();
    v2.Reserve(N);
    for(int i = 0; i < N; ++i)
    {
        v2.PushBack(i);
    }
    finish_time = GetUs();
    printf("v2 time: %ld\n",finish_time - start_time);
}

void test_riterator()
{
    vector<string> v;
    v.push_back("aaaa");
    v.push_back("bbbb");
    v.push_back("cccc");
    v.push_back("dddd");
    vector<string>::reverse_iterator rit = v.rbegin();
    while(rit != v.rend())
    {
        cout<<*rit<<" ";
        ++rit;
    }
    cout<<endl;
}

void test_resize_assign()
{
    vector<int> v1;
    v1.push_back(1);
    v1.push_back(2);
    v1.resize(10,9);
    vector<int>::iterator it1 = v1.begin();
    while(it1 != v1.end())
    {
        cout<<*it1<<" ";
        ++it1;
    }
    cout<<endl;

    vector<int> v2;
    v2.push_back(1);
    v2.push_back(2);
    v2.assign(10,9);
    vector<int>::iterator it2 = v2.begin();
    while(it2 != v2.end())
    {
        cout<<*it2<<" ";
        ++it2;
    }
    cout<<endl;
}

void test_insert_find()
{
    vector<int> v1;
    v1.push_back(1);
    v1.push_back(2);
    v1.push_back(3);
    v1.push_back(4);
    v1.push_back(5);

    /* int arr[] = {11,22,33,44}; */

    vector<int>::iterator pos = find(v1.begin(),v1.end(),3);
    if(pos != v1.end())
    {
        /* v1.insert(pos,3); */
        /* v1.insert(pos,arr,arr+4); */
        /* v1.insert(pos,5,10); */
        /* v1.erase(pos); */
        v1.erase(pos,v1.end());
    }

    vector<int>::iterator it1 = v1.begin();
    while(it1 != v1.end())
    {
        cout<<*it1<<" ";
        ++it1;
    }
    cout<<endl;
}

void test_clear()
{
    vector<int> v1;
    v1.push_back(1);
    v1.push_back(2);
    v1.push_back(3);
    v1.push_back(4);
    v1.push_back(5);

    // clear 不会清空间,只会清数据
    v1.clear();
    cout<<"size = "<<v1.size()<<endl;
    cout<<"capcity = "<<v1.capacity()<<endl;

    //如何请空间
    {
        vector<int> tmp;
        tmp.swap(v1);
    } 
    cout<<"size = "<<v1.size()<<endl;
    cout<<"capcity = "<<v1.capacity()<<endl;
}

void test_sort()
{
    vector<int> v1;
    v1.push_back(5);
    v1.push_back(1);
    v1.push_back(3);
    v1.push_back(2);
    v1.push_back(4);

    sort(v1.begin(),v1.end(),std::greater<int>());

    vector<int>::iterator it1 = v1.begin();
    while(it1 != v1.end())
    {
        cout<<*it1<<" ";
        ++it1;
    }
    cout<<endl;
}

int main()
{
    /* test_myvector(); */
    /* TestReserve(); */
    /* test_riterator(); */
    /* test_resize_assign(); */
    /* test_insert_find(); */
    /* test_clear(); */
    test_sort();
    return 0;
}
