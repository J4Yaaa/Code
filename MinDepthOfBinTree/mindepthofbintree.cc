#include <iostream>
using namespace std;

struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
    TreeNode(int x) :val(x), left(NULL), right(NULL) 
    {}
};

// 深度优先思想1:
// class Solution {
// public:
//     int run(TreeNode *root)
//     {
//         if(root == NULL)
//         {
//             return 0;
//         }
//         int l_high = run(root->left);
//         int r_high = run(root->right);
//         //分析斜树情况,如果左子树为空或者右子树为空,就返回另一个+1;
//         if(l_high == 0 || r_high == 0)
//         {
//             return 1 + l_high + r_high;
//         }
//         return l_high < r_high ? l_high + 1: r_high + 1;
//     }
// };

//  深度优先思想2:
//  class Solution {
//  public:
//      int run(TreeNode *root)
//      {
//          // 1.如果根节点为空,返回0
//          if(root == NULL)
//          {
//              return 0;
//          }
//          // 2.如果左子树为空,返回右子树的最小深度+1
//          if(root->left == NULL)
//          {
//              return run(root->right) + 1;
//          }
//          // 3.如果右子树为空,返回左子树的最小深度+1
//          if(root->right == NULL)
//          {
//              return run(root->left) + 1;
//          }
//          // 4.如果左右子树都不为空,返回左右子树中的最小值+1;
//          int l = run(root->left) + 1;
//          int r = run(root->right) + 1;
//          return l < r ? l : r;
//      }
//  };

// 深度优先思想遍历了整棵树,效率不高,这里可采用广度优先(层序遍历),找到第一个左右子树都为空的节点
#include <queue>
 class Solution {
 public:
     int run(TreeNode *root)
     {
         if(root == NULL)
         {
             return 0;
         }
         if(root->left == NULL && root->right == NULL)
         {
             return 1;
         }
         queue<TreeNode*> q;
         q.push(root);
         int mindepth = 0;
         while(!q.empty())
         {
             ++mindepth;
             int size = q.size();
             int i = 0;
             for(i = 0; i < size; ++i)
             {
                 TreeNode* cur = q.front();
                 q.pop();
                 if(cur->left == NULL && cur->right == NULL)
                 {
                     return mindepth;
                 }
                 if(cur->left != NULL)
                 {
                     q.push(cur->left);
                 }
                 if(cur->right != NULL)
                 {
                     q.push(cur->right);
                 }
             }
         }
         return mindepth;
     }
 };

 
int main()
{
    TreeNode* a = new TreeNode(1);
    TreeNode* b = new TreeNode(2);
//    TreeNode* c = new TreeNode(3);
//    TreeNode* d = new TreeNode(4);
//    TreeNode* e = new TreeNode(5);
//    TreeNode* f = new TreeNode(6);
//    TreeNode* g = new TreeNode(7); */
    a->left = b;

    Solution s;
    cout<<s.run(a)<<endl;
    return 0;
}
