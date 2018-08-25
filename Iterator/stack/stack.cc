#include <iostream>
using namespace std;
#include <stack>
#include <queue>

//适配器不支持迭代器的遍历
void test_stack()
{
    stack<int> s;
    s.push(1);
    s.push(2);
    s.push(3);
    s.push(4);
    while(!s.empty())
    {
        cout<<s.top()<<" ";
        s.pop();
    }
    cout<<endl;
}


int main()
{
    test_stack();
    return 0;
}
