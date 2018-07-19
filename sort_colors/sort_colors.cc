// Given an array with n objects colored red, white or blue
// sort them so that objects of the same color are adjacent, with the colors in the order red, white and blue.
// Here, we will use the integers 0, 1, and 2 to represent the color red, white, and blue respectively.
// 
// Note: 
// You are not suppose to use the library's sort function for this problem.
// 
// Follow up: 
// A rather straight forward solution is a two-pass algorithm using counting sort.
// First, iterate the array counting number of 0's, 1's, and 2's, then overwrite array with total number of 0's, then 1's and followed by 2's.
// 
// Could you come up with an one-pass algorithm using only constant space?
#include <iostream>
using namespace std;
#include <vector>

class Solution {
public:
    void sortColors(int A[], int n)
    {
        if(n == 0 || n == 1)
        {
            return;
        }
        if(n == 2)
        {
            if(A[0] > A[1])
            {
                int tmp = A[0];
                A[0] = A[1];
                A[1] = tmp;
            }
            return;
        }
        // 思路：
        // 使用三个正式先将数组中 0,1,2好下标的值保存下来，并且将这里的值置为0
        // 从下表为3的位置开始遍历数组
        // 如果值为0，就将0号下标的值加加
        // 如果值为1，就将1号下标的值加加
        // 如果值为2，就将2号下标的值加加
        // 不要忘记自己保存的三个数也需要加加到对应的数组下标中
        // 最后根据0,1,2数组下标将数据填满
        int pos_zero = A[0];
        int pos_one = A[1];
        int pos_two = A[2];
        A[0] = A[1] = A[2] = 0;
        ++A[pos_zero];
        ++A[pos_one];
        ++A[pos_two];
        int i = 3;
        for(; i < n; ++i)
        {
            ++A[A[i]];
        }
        pos_zero = A[0];
        pos_one = A[1];
        pos_two = A[2];
        i = 0;
        while(pos_zero != 0)
        {
            A[i] = 0;
            --pos_zero;
            ++i;
        }
        while(pos_one != 0)
        {
            A[i] = 1;
            --pos_one;
            ++i;
        }
        while(pos_two != 0)
        {
            A[i] = 2;
            --pos_two;
            ++i;
        }
        for(i = 0; i < n; ++i)
        {
            cout<<A[i]<<" ";
        }
        cout<<endl;
    }
};

int main()
{
    Solution s;
    int a[] = {0,0,0}; 
    s.sortColors(a,sizeof(a)/sizeof(a[0]));
    return 0;
}

