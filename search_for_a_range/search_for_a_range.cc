#include <iostream>
using namespace std;
#include <vector>
#include <cstdio>

class Solution {
public:
    vector<int> searchRange(int A[], int n, int target) {
        vector<int> res;
        if(target < A[0] || target > A[n-1])
        {
            return vector<int> (2,-1);
        }
        int left = 0;
        int right = n-1;
        int mid = 0;
        while(left <= right)
        {
            mid = left + (right - left)/2;
            if(A[mid] > target)
            {
                right = mid - 1;
            }
            if(A[mid] < target)
            {
                left = mid + 1;
            }
            if(A[mid] == target)
            {
                break;
            }
        }
        if(left > right)
        {
            return vector<int> (2,-1);
        }
        printf("----%d----: mid = %d\n",__LINE__,mid);
        int tmp1 = mid;
        int tmp2 = mid;
        while(A[tmp1] == target || A[tmp2] == target)
        {
            if(A[tmp1] == target)
            {
                --tmp1;
            }
            if(A[tmp2] == target)
            {
                ++tmp2;
            }
        printf("----%d----: tmp1 = %d, tmp2 = %d\n",__LINE__,tmp1,tmp2);
        }
        if(tmp1 < 0)
        {
            tmp1 = -1;

        }
        if(tmp2 >= n)
        {
            tmp2 = n;

        }
        res.push_back(tmp1+1);
        res.push_back(tmp2-1);
        return res;
    }
};

int main()
{
    int arr[] = {1};
    Solution s;
    vector<int> v = s.searchRange(arr,sizeof(arr)/sizeof(arr[0]),1);
    int size = v.size();
    for(int i = 0; i < size; ++i)
    {
        cout<<v[i]<<" ";
    }
    cout<<endl;
    return 0;
}
