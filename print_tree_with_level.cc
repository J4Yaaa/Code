#include <iostream>
using namespace std;
#include <vector>
#include <queue>

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
    vector<vector<int> > Print(TreeNode* pRoot) {
        if(pRoot == NULL)
        {
            return vector<vector<int> >();
        }
        vector<vector<int> > res;
        queue<TreeNode*> q;
        q.push(pRoot);
        int level_count = 1;
        while(!q.empty())
        {
            int cur = 0;
            vector<int> v;
            while(level_count > 0)
            {
                TreeNode* f = q.front();
                v.push_back(f->val);
                q.pop();
                if(f->left != NULL)
                {
                    q.push(f->left);
                    ++cur;
                }
                if(f->right != NULL)
                {
                    q.push(f->right);
                    ++cur;
                }
                --level_count;
            }
            res.push_back(v);
            level_count = cur;
        }
        return res;
    }
};
