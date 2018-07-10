/*
 * 给定一个无序数组,包含正数,负数和0
 * 要求从中找出三个数的乘积
 * 使得乘积最大
 * 例如: 
 *
 * 输入:
 * 4
 * 1 2 3 5
 * 输出:
 * 30
 */

#include <iostream>
using namespace std;
#include <algorithm>
#include <vector>

int FindMaxMul(vector<int>& max,vector<int>& min)
{
    if(max.size() == 0)
    {
        return min[0] * min[1] * min[2];
    }
    else
    {
        while(max.size() < 3 || min.size() < 2)
        {
            if(max.size() < 3)
            {
                max.push_back(1);
            }
            if(min.size() < 2)
            {
                min.push_back(1);
            }
        }
        max.resize(3);
        min.resize(3);
        int mul1 = 1;
        int mul2 = 1;
        for(size_t i = 0; i < 3; ++i)
        {
            mul1 *= max[i];
            if(i < 2)
            {
                mul2 *= min[i];
            }
            if(i == 2)
            {
                mul2 *= max[0];
            }
        }
        return mul1 > mul2 ? mul1 : mul2;
    }
}

int main()
{
    int n;
    cin>>n;
    int a;
    vector<int> max;
    vector<int> min;
    while(n--)
    {
        cin>>a;
        if(a >= 0)
        {
            max.push_back(a);
        }
        else
        {
            min.push_back(a);
        }
    }
    sort(max.begin(),max.end(),greater<int>());
    sort(min.begin(),min.end(),less<int>());
    int res = FindMaxMul(max,min);
    cout<<"res = "<<res<<endl;
    return 0;
}
