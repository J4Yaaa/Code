#include <iostream>
using namespace std;

struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
    TreeNode(int x) :val(x), left(NULL), right(NULL) 
    {}
};

class Solution {
public:
    void Mirror(TreeNode *pRoot) {
        if(pRoot == NULL)
        {
            return;
        }
        if(pRoot->left != NULL)
        {
            Mirror(pRoot->left);
        }
        if(pRoot->right != NULL)
        {
            Mirror(pRoot->right);
        }
        TreeNode* tmp = pRoot->left;
        pRoot->left = pRoot->right;
        pRoot->right = tmp;
    }

    int TreeDepth(TreeNode* pRoot)
    {
        if(pRoot == NULL)
        {
            return 0;
        }
        int left = TreeDepth(pRoot->left);
        int right = TreeDepth(pRoot->right);
        return left > right ? left + 1 : right + 1;
    }
};

int main()
{
    return 0;
}
