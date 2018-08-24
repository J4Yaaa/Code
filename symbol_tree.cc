#include <iostream>

struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
    TreeNode(int x) :
        val(x), left(NULL), right(NULL) {
        }
};

class Solution {
public:
    bool isSymmetrical(TreeNode* pRoot)
    {
        if(pRoot == NULL)
        {
            return true;
        }
        return _isSymmetrical(pRoot->left,pRoot->right);
    }
    bool _isSymmetrical(TreeNode* left,TreeNode* right)
    {
        if(left == NULL)
        {
            return right == NULL;
        }
        if(right == NULL)
        {
            return left == NULL;
        }
        if(left->val != right->val)
        {
            return false;
        }
        return _isSymmetrical(left->left,right->right) && _isSymmetrical(left->right,right->left);
    }
};
