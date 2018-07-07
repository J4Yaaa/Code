#include <iostream>
using namespace std;

class Solution {
public:
    int searchInsert(int A[], int n, int target) {
        if(target < A[0])
        {
            return 0;
        }
        if(target > A[n - 1])
        {
            return n;
        }
        int left = 0;
        int right = n;
        int mid = 0;
        while(left < right)
        {
            mid = left + (right - left)/2;
            if(A[mid] < target)
            {
                left = mid+1;
            }
            if(A[mid] > target)
            {
                right = mid;
            }
            if(A[mid] == target)
            {
                return mid;
            }
        }
        if(A[mid] > target)
        {
            return mid;
        }
        else
        {
            return mid+1;
        }
    }
};

int main()
{
    Solution s;
    int arr[] = {1,2,3,5,6};
    int ret = s.searchInsert(arr,sizeof(arr)/sizeof(arr[0]),4);
    cout<<ret<<endl;
    return 0;
}
