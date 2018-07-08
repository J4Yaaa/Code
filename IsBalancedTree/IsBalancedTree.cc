#include <iostream>
using namespace std;

struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
    TreeNode(int x) :val(x), left(NULL), right(NULL) 
    {}
};

// class Solution {
// public:
//     int Is_AvgTree(const TreeNode* root)
//     {
//         if(root == NULL)
//         {
//             return 0;
//         }
//         int l_high = Is_AvgTree(root->left) + 1;
//         int r_high = Is_AvgTree(root->right) + 1;
//         if(l_high - r_high > 1 || r_high - l_high > 1)
//         {
//             l_high = 0x80000000;
//             r_high = 0x80000000;
//         }
//         return l_high > r_high ? l_high : r_high;
//     }
// 
//     bool IsBalanced_Solution(TreeNode* pRoot) {
//         int ret = Is_AvgTree(pRoot);
//         cout<<"ret = "<<ret<<endl;
//         if(ret < 0)
//         {
//             return false;
//         }
//         return true;
//     }
// };

class Solution {
public:
    int Is_AvgTree(const TreeNode* root)
    {
        if (root == NULL)
            return 0;

        int left = Is_AvgTree(root->left);
        if (left == -1)
            return -1;

        int right = Is_AvgTree(root->right);
        if (right == -1)
            return -1;

        int max = left;
        int min = right;
        if(left < right)
        {
            max = right;
            min = left;
        }

        return (max - min > 1) ? -1 : 1 + max;
    }

    bool IsBalanced_Solution(TreeNode* pRoot) {
        return Is_AvgTree(pRoot) != -1;
    }
};

int main()
{
    TreeNode* a = new TreeNode(1);
    TreeNode* b = new TreeNode(2);
    TreeNode* c = new TreeNode(3);
    TreeNode* d = new TreeNode(4);
    TreeNode* e = new TreeNode(5);
    /* TreeNode* f = new TreeNode(6); */
    /* TreeNode* g = new TreeNode(7); */
    a->left = b;
    b->right = c;
    c->right = d;
    d->right = e;

    Solution s;
    cout<<s.IsBalanced_Solution(a)<<endl;
    return 0;
}
