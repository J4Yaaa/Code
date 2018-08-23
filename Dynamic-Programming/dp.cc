#include <iostream>
using namespace std;
#include <vector>
#include <algorithm>
#include <string>
#include <map>
#include <unordered_set>

////////////////////////////////////////////////////////
// 1.斐波那契数列
// 递归版本
int fib(int n)
{
    if(n == 0)
    {
        return 0;
    }
    if(n == 1 || n == 2)
    {
        return 1;
    }
    return fib(n-1) + fib(n-2);
}

// 动态规划版本
int dp_fib(int n)
{
    if(n < 0)
    {
        return 0;
    }
    // 1.申请空间
    vector<int> f(n+1,0);
    // 2.初始化
    f[0] = 0;
    f[1] = 1;
    f[2] = 1;
    // 3.状态递推
    for(int i = 3; i <= n; ++i)
    {
        // f[i] = f[i-1] + f[i-2]
        f[i] = f[i-1] + f[i-2];
    }
    return f[n];
}

// O(1) 复杂度的动态规划
int dp1_fib(int n)
{
    if(n <= 0)
    {
        return 0;
    }
    // 1.初始化
    int fn1 = 0;
    int fn2 = 1;
    int fn3 = 1;
    for(int i = 2; i <= n; ++i)
    {
        // fn3 -- f[i]
        // fn2 -- f[i-1]
        // fn3 -- f[i-2]
        fn3 = fn1 + fn2;
        fn1 = fn2; // 使 f[i-2] -> f[i-1]
        fn2 = fn3;
    }
    return fn3;
}

////////////////////////////////////////////////////////
// 2.最大连续子数组的和
// 状态: f[i] 以v[i]结尾的连续子数组最大和
// 递推: f[i] = f[i-1]
int MaxSubStringSum(vector<int>& v)
{
    if(v.size() == 0)
    {
        return 0;
    }
    int res = v[0];
    int cur = v[0];
    for(size_t i = 1; i < v.size(); ++i)
    {
        cur = max(cur+v[i],v[i]);
        if(cur > res)
        {
            res = cur;
        }
    }
    return res;
}

////////////////////////////////////////////////////////
// 3.青蛙跳台阶的问题
// 可以跳一个，也可以跳N个
// 状态：青蛙跳上N级台阶的方法
// 递推：f[i] = f[i-1] + f[i-2] + ... + f[i-i]
//       f[i-1] = f[i-2] + f[i-3] + ... + f[i-i]
//       f[i] = f[i-1] + f[i-1] = 2 * f[i-1]
// 初始化：f[1] = 1
int stairs(int n)
{
    if(n < 1)
    {
        return 0;
    }
    // 初始化
    int total_num = 1;
    // 递推
    for(int i = 1; i < n; ++i)
    {
        total_num = 2 * total_num;
    }
    return total_num;
}

// 简单的非动态规划的方式
int stairs1(int n)
{
    if(n < 1)
    {
        return 0;
    }
    return 1lu << (n-1);
}

////////////////////////////////////////////////////////
// 4.给定一个字符串和一个词典dict,确定s是否可以根据词典中的词分成一个或多个单词
// 状态: f[i] 前 i 个字符能否被字典成功分隔
// 递推: f[i]: f[j] && j<i && substr(j+1,i)
// 初始值: 当没有初始值的时候,应该自己设置一个有意义的初始值
//  f[0] = true
//  f[1] 才表示第一个字符
// 返回: f[n]
bool wordBreak(string s,unordered_set<string>& dict)
{
    if(s.empty() || dict.empty())
    {
        return false;
    }
    // 初始化
    int n = s.size();
    vector<bool> can_break(n+1,false);
    can_break[0] = true;
    for(int i = 1; i <= n; ++i)
    {
        for(int j = 0; j < i; ++j)
        {
            // f[j] == true 就去字典里面找 dict[j+1,i] 存不存在
            if(can_break[j] && dict.find(s.substr(j,i-j)) != dict.end())
            {
                can_break[i] = true;
                break;
            }
        }
    }
    return can_break[n];
}

////////////////////////////////////////////////////////
// 5.双序列动归
// 状态: f[i,j]: 从f[0,0]走到f[i,j]的最小路径和
// 递推: 中间: F[i,j] = min(f[i-1,j-1],f[i-1,j]) + f[i,j]
//       左边界: if(j==0) { F[i,0] = f[i-1,0] + f[i,0] }
//       右边界: if(i==j) { F[i,i] = f[i-1,i-1] + f[i,i] }
// 初始化: F[0,0] = f[0,0]
// 返回: min { F[n-1,0] F[n-1,1] ... F[n-1,n-1] }
int triangle(vector<vector<int> >& t)
{
    if(t.empty())
    {
        return 0;
    }
    vector<vector<int> > min_sum = t;
    // 递推
    for(size_t i = 1; i < t.size(); ++i)
    {
        for(size_t j = 0; j <= i; ++j)
        {
            // 处理左边界
            if(j == 0)
            {
                min_sum[i][j] = min_sum[i-1][j] + min_sum[i][j];
            }
            // 处理右边界
            if(i == j)
            {
                min_sum[i][j] = min_sum[i-1][j-1] + min_sum[i][j];
            }
            else
            {
                min_sum[i][j] = min(min_sum[i-1][j-1],min_sum[i-1][j]) + min_sum[i][j];
            }
        }
    }
    int size = t.size();
    int res = min_sum[size-1][0];
    for(size_t i = 0; i < t.size()-1; ++i)
    {
        res = min(res,min_sum[size-1][i]);
    }
    return res;
}

// 方法2
// 状态: f[i,j]: 从f[0,0]走到f[i,j]的最小路径和
// 递推: 中间: F[i,j] = min(f[i+1,j+1],f[i+1,j]) + f[i,j]
// 初始化: F[n-1,0] = f[n-1,0]
//         F[n-1,i] = f[n-1,i]
// 返回: F[0,0]
int triangle2(vector<vector<int> >& t)
{
    if(t.empty())
    {
        return 0;
    }
    // 初始化
    vector<vector<int> > min_sum = t;
    // 递推
    int line = t.size();
    for(int i = line-2; i >= 0; --i)
    {
        for(int j = 0; j <= i; ++j)
        {
            min_sum[i][j] = min(min_sum[i+1][j],min_sum[i+1][j+1]) + min_sum[i][j];
        }
    }
    return min_sum[0][0];
}

////////////////////////////////////////////////////////
// 6.机器人移动问题
// 在一个 m*n 的网格的左上角有一个机器人,机器人只能向下或者向右移动
// 机器人想到达右下角有多少条路径
// 状态: F[i,j] 从[0,0]到[i,j]的路径总数
// 递推: F[i,j] = f[i,j-1] + f[i-1,j]
// 初始化: F[0,i] = 1
//         F[i,0] = 1
// 返回: F[m-1,n-1]
int uniquePath(int m,int n)
{
    if(m < 1 || n < 1)
    {
        return 0;
    }
    vector<vector<int> > path_num(m,vector<int>(n,0));
    // 初始化第一行
    for(int i = 0; i < n; ++i)
    {
        path_num[0][i] = 1;
    }
    // 初始化第一列
    for(int i = 1; i < m; ++i)
    {
        path_num[i][0] = 1;
    }
    // 递推
    for(int i = 1; i < m; ++i)
    {
        for(int j = 1; j < n; ++j)
        {
            // F[i,j] = F[i,j-1] + F[i-1,j]
            path_num[i][j] = path_num[i][j-1] + path_num[i-1][j];
        }
    }
    return path_num[m-1][n-1];
}

// 在一个 m*n 的网格的左上角有一个机器人,机器人只能向下或者向右移动,并且不可走值为1的点
// 机器人想到达右下角有多少条路径
// 状态: F[i,j]: 从[0,0]到[i,j]的路径总数
// 递推: if(f[i,j] == 1) F[i,j] = 0
//       if(f[i,j] == 0) F[i,j] = F[i-1,j] + F[i,j-1]
// 初始化: if(f[i,0] == 1) F[i,0] = 0
//         if(F[i,0] == 0) F[i,0] = 1
int uniquePath2(vector<vector<int> >& obs)
{
    if(obs.empty())
    {
        return 0;
    }
    int m = obs.size(); // 行
    int n = obs[0].size(); // 列
    vector<vector<int> > path_num(m,vector<int>(n,0));
    // 初始化第一行
    for(int i = 0; i < n; ++i)
    {
        if(obs[0][i] == 1)
        {
            break;
        }
        else
        {
            path_num[0][i] = 1;
        }
    }
    // 第一列
    for(int i = 0; i < m; ++i)
    {
        if(obs[i][0] == 1)
        {
            break;
        }
        else
        {
            path_num[i][0] = 1;
        }
    }
    // 递推
    for(int i = 1; i < m; ++i)
    {
        for(int j = 1; j < n; ++j)
        {
            if(obs[i][j] == 1)
            {
                path_num[i][j] = 0;
            }
            else
            {
                path_num[i][j] = path_num[i-1][j] + path_num[i][j-1];
            }
        }
    }
    return path_num[m-1][n-1];
}

////////////////////////////////////////////////////////
// 7.一个 m*n 的网格,找出从上到下的最小路径和
// 只能向右和向下走
// 状态: F[i,j]: 从 F[0,0] 到 F[i,j] 的最小路径和
// 递推: min(F[i-1,j],F[i,j-1]) + F[i,j]
//       第一行 F[0,i] = F[0,i-1] + [0,i]
//       第一列 F[i,0] = F[i-1,0] + [i,0]
// 初始化: F[0,0] = (0,0)
// 返回: F[m-1][n-1]
int minPathSum(vector<vector<int> >& grid)
{
    if(grid.empty())
    {
        return 0;
    }
    int m = grid.size();
    int n = grid[0].size();
    vector<vector<int> > min_sum(m,vector<int>(n,0));
    // 初始化
    min_sum[0][0] = grid[0][0];
    // 递推
    // 第一行
    for(int i = 1; i < n; ++i)
    {
        min_sum[0][i] = min_sum[0][i-1] + grid[0][i];
    }
    // 第一列
    for(int i = 1; i < m; ++i)
    {
        min_sum[i][0] = min_sum[i-1][0] + grid[i][0];
    }
    // 其他元素
    for(int i = 1; i < m; ++i)
    {
        for(int j = 1; j < n; ++j)
        {
            min_sum[i][j] = min(min_sum[i-1][j],min_sum[i][j-1]) + grid[i][j];
        }
    }
    return min_sum[m-1][n-1];
}

////////////////////////////////////////////////////////
// 8.回文串分隔
// 给一个字符串,将字符串分为多个子串,保证每个字符串都是会问字符串
// 并返回最小分隔数
// 状态: F[i]: 字符串前 i 个字符的最小分隔数
// 递推: F[i] = min(F[j] + 1,F[i]) j < i substr(j+1,i) 还是回文串
// 初始化: F[i] = i - 1
//         F[0] = -1 // 为处理重复的回文串
// 返回: F[n]

bool ispal(string s)
{
    string rs = s;
    reverse(s.begin(),s.end());
    return rs == s;
}

// 可以将上面的函数也改编成动态规划
// 状态: F[i,j] 从i到j区间是不是回文串
// 递推: F[i,j] = (s[i] == s[j] && F[i+1,j-1]
// 初始化: F[i,i] = true
// 返回: 二维矩阵(存储的是是否为回文串的结果)
vector<vector<bool> > ispal2(string& s)
{
    int n = s.size();
    vector<vector<bool> > is_pal(n,vector<bool>(n,false));
    for(int i = n-1; i >= 0; --i)
    {
        for(int j = i;j < n; ++j)
        {
            if(j == i)
            {
                is_pal[i][j] = true;
            }
            // 连续的两个字符
            else if(j == i+1)
            {
                is_pal[i][j] = (s[i] == s[j]);
            }
            // 剩余 j>i+1 的,就是不相邻的
            else
            {
                is_pal[i][j] = (s[i] == s[j] && is_pal[i+1][j-1]);
            }
        }
    }
    return is_pal;
}

int minCut(string& s)
{
    if(s.empty())
    {
        return 0;
    }
    vector<int> cut;
    int n = s.size();
    for(int i = 0; i <= n; ++i)
    {
        // F[i] = i - 1 初始化每一个位置都是最大值,一个长为n的串,最多分 n-1 次就一定保证每个都是回文串
        cut.push_back(i-1);
    }
    // 递推
    for(int i = 1; i <= n; ++i)
    {
        for(int j = 0; j < i; ++j)
        {
            // 从第 j+1 到第 i 个字符串是否为回文串
            if(ispal(s.substr(j,i-j)))
            {
                cut[i] = min(cut[j]+1,cut[i]);
            }
        }
    }
    return cut[n];
}

////////////////////////////////////////////////////////
// 9.编辑距离
// 给定两个单词,找到最小的修改步数,将 word1 修改为 word2,可进行插入,删除,替换
// 状态: F[i,j]: 将 word1 的前 i 个字符转换成 word2 的前 j 个字符需要的最小操作数
//       如果: word1[i] == word2[j]
//             F[i,j] <---- F[i-1,j-1]
//             word1[i] != word[j]
//             F[i,j] <---- F[i-1,j-1] + 1 ----> 替换
//       F[i,j] <---- F[i-1,j] + 1 ----> 删除
//       F[i,j] <---- F[i,j-1] + 1 ----> 插入
// 递推: min(F[i-1,j]+1, F[i,j-1]+1, F[i-1,j-1]+(word1[i]==word2[i]?0:1))
// 初始化: F[0,i] = i ----> 插入
//         F[i,0] = i ----> 删除
// 返回: F[m,n]

int minDistance(string word1,string word2)
{
    if(word1.empty() || word2.size())
    {
        return max(word1.size(),word2.size());
    }
    int m = word1.size(); // word1的size,行
    int n = word2.size(); // word2的size,列
    vector<vector<int> > min_dis(m+1,vector<int>(n+1,0));
    // 行初始化,第一行表示word1空串
    for(int i = 0; i <= m; ++i)
    {
        min_dis[i][0] = i;
    }
    // 列初始化,第一列表示word2空串
    for(int i = 0; i <= n; ++i)
    {
        min_dis[0][i] = i;
    }
    // 递推
    // F[i,j] = min(F[i-1,j] + 1,F(i,j-1)+1,F(i-1,j-1)+(word1[i]==word2[j]?0:1))
    for(int i = 1; i <= m; ++i)
    {
        for(int j = 1; j <= n; ++j)
        {
            min_dis[i][j] = 1 + min(min_dis[i-1][j],min_dis[i][j-1]);
            // 判断插入的情况 word1第i个元素是否和word2第j个元素相等
            if(word1[i-1] == word2[j-1])
            {
                min_dis[i][j] = min(min_dis[i][j],min_dis[i-1][j-1]);
            }
            else
            {
                min_dis[i][j] = min(min_dis[i][j],min_dis[i-1][j-1]+1);
            }
        }
    }
    // 返回 F[m][n]
    return min_dis[m][n];
}

////////////////////////////////////////////////////////
// 10.给定两个字符串 S 和 T,求 S 中有多少个子序列和 T 相同
// S 的子串表示 S 中去掉0个或多个字符后的串
// 状态: F[i,j]: 由S的前i个字符组成的子序列和T的前j个字符相同的个数
// 递推: 
//      当 S[i] == T[j]
//       1.使用S[i]去匹配T[j] ---> F[i,j] = F[i-1,j-1]
//       2.不使用S[i]去匹配T[j] ---> F[i,j] = F[i-1,j]
//      F[i,j] = F[i-1,j-1] + F[i-1,j]
//      当 S[i] != T[j]
//       F[i,j] = F[i-1,j]
// 初始化: 
//      F[i,0] = 1
//      F[0,i] = 0
// 返回: F[m,n]
int numDistance(const string& S,const string& T)
{
    if(T.empty())
    {
        return 1;
    }
    if(S.empty())
    {
        return 0;
    }
    if(S.size() < T.size())
    {
        return 0;
    }
    int m = S.size(); // 行
    int n = T.size(); // 列
    vector<vector<int> > num_dis(m+1,vector<int>(n+1,0));
    // 初始化
    // 在S中找空串
    for(int i = 0; i < m; i++)
    {
        num_dis[i][0] = 1;
    }
    // 在空串中找T,已经初始化过了,就不用写了
    // 递推
    for(int i = 1; i <= m; ++i)
    {
        for(int j = 1; j <= n; ++j)
        {
            // S的第i个元素是否和T的第j个元素相同
            if(S[i-1] == T[j-1])
            {
                num_dis[i][j] = num_dis[i-1][j-1] + num_dis[i-1][j];
            }
            else // S[i-1] != T[j-1]
            {
                num_dis[i][j] = num_dis[i-1][j];
            }
        }
    }
    return num_dis[m][n];
}

int main()
{
    // cout<<uniquePath(2,3)<<endl;
    
    // vector<vector<int> > obs{{0,0,0},{0,1,0},{0,0,0}};
    // cout<<uniquePath2(obs)<<endl;
    
    // vector<vector<int> > g{{1,2,3},{4,5,6},{7,8,9}};
    // cout<<minPathSum(g)<<endl;
    
    // string s("aabccbaa");
    // cout<<minCut(s)<<endl;

    // 有问题
    // string word1("abc");
    // string word2("abc");
    // cout<<minDistance(word1,word2)<<endl;

    string S("rabbbit");
    string T("rabit");
    cout<<numDistance(S,T)<<endl;
    return 0;
}
