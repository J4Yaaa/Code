// 给定一个有n个正整数的数组A和一个正数sum,求选择数组A中部分数字和为sum的方案数
// 当两种选取方案有一个数字的下标不一样,我们就认为数不同的组成方案
// 1 <= n <= 1000
// 1 <= sum <= 1000
// 例如:
// 输入: 
//  5 15
//  5 5 10 2 3
// 输出:
//  4

#include <iostream>
using namespace std;
#include <vector>

int dp[1001][1001];

void backpack(const int& n, const int& sum, const vector<int>& A)
{
    // 首先将第一列全部置为1
    int i = 0;
    for(; i <= n; ++i)
    {
        dp[i][0] = 1;
    }
    // 将第一行全部置为 0, 除dp[0][0]
    int j = 1;
    for(; j <= sum; ++j)
    {
        dp[0][j] = 0;
    }
    // 动态规划
    for(i = 1; i <= n; ++i)
    {
        for(j = 1; j <= sum; ++j)
        {
            if(j < A[i])
            {
                dp[i][j] = dp[i-1][j];
            }
            else
            {
                dp[i][j] = dp[i-1][j]+dp[i-1][j-A[i]];
            }
        }
    }
    cout<<dp[n][sum]<<endl;
}

int main()
{
    int n; 
    cin>>n;
    int sum;
    cin>>sum;
    vector<int> A;
    A.resize(n+1);
    for(int i = 1; i <= n; ++i)
    {
        cin>>A[i];
    }
    backpack(n,sum,A);
    return 0;
}
