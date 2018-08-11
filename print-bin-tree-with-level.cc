#include <iostream>
using namespace std;
#include <vector>
#include <queue>

struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) 
    {}
};

class Solution {
public:
    vector<vector<int> > Print(TreeNode* pRoot) {
        if(pRoot == NULL)
        {
            return vector<vector<int> >();
        }
        vector<vector<int> > res;
        vector<int> v;
        queue<TreeNode*> q;
        q.push(pRoot);
        int now_level = 1;
        int next_level = 0;
        while(!q.empty())
        {
            while(now_level > 0)
            {
                TreeNode* f = q.front();
                v.push_back(f->val);
                q.pop();
                if(f->left != NULL)
                {
                    q.push(f->left);
                    ++next_level;
                }
                if(f->right != NULL)
                {
                    q.push(f->right);
                    ++next_level;
                }
                --now_level;
            }
            res.push_back(v);
            v.clear();
            now_level = next_level;
            next_level = 0;
        }
        return res;
    }
};

int main()
{
    TreeNode* root = new TreeNode(1);
    root->left = new TreeNode(2);
    root->left->left = new TreeNode(3);
    Solution s;
    s.Print(root);
    return 0;
}
