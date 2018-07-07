#include <iostream>
using namespace std;
#include <vector>

struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
    TreeNode(int x) :val(x), left(NULL), right(NULL) 
    {}
};

class Solution {
public:
    void _postorder(TreeNode* root, vector<int>& v)
    {
        if(root == NULL)
        {
            return;
        }
        _postorder(root->left,v);
        _postorder(root->right,v);
        v.push_back(root->val);
    }
    vector<int> postorderTraversal(TreeNode *root) {
        vector<int> v;
        _postorder(root,v);
        return v;
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
    vector<int> v = s.postorderTraversal(a);
    vector<int>::iterator it = v.begin();
    while(it != v.end())
    {
        cout<<*it<<" ";
        ++it;
    }
    cout<<endl;
    return 0;
}
