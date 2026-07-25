#include <bits/stdc++.h>
using namespace std;

struct TreeNode
{
    int val;
    TreeNode *left;
    TreeNode *right;

    TreeNode(int x)
    {
        val = x;
        left = right = NULL;
    }
};

class Solution
{
public:
    int ans = 1;

    void dfs(TreeNode *l, TreeNode *r, int lw, int rw)
    {
        if (!l && !r)
        {
            ans = max(ans, lw + rw);
            return;
        }

        ans = max(ans, lw + rw);

        TreeNode *nl = NULL;
        TreeNode *nr = NULL;

        int nlw = lw;
        int nrw = rw;

        // Left boundary
        if (l)
        {
            if (l->left)
            {
                nl = l->left;
                nlw++;
            }
            else if (l->right)
            {
                nl = l->right;
                nlw--;
            }
        }

        // Right boundary
        if (r)
        {
            if (r->right)
            {
                nr = r->right;
                nrw++;
            }
            else if (r->left)
            {
                nr = r->left;
                nrw--;
            }
        }

        dfs(nl, nr, nlw, nrw);
    }

    int widthOfBinaryTree(TreeNode *root)
    {
        if (!root)
            return 0;

        if (!root->left && !root->right)
            return 1;

        int lw = 0, rw = 0;

        TreeNode *l = NULL;
        TreeNode *r = NULL;

        if (root->left)
        {
            l = root->left;
            lw++;
        }

        if (root->right)
        {
            r = root->right;
            rw++;
        }

        ans = max(ans, lw + rw);

        dfs(l, r, lw, rw);

        return ans;
    }
};

int main()
{
    /*
            1
          /   \
         3     2
        /       \
       5         9
      /         /
     6         7
    */

    TreeNode *root = new TreeNode(1);

    root->left = new TreeNode(3);
    root->right = new TreeNode(2);

    root->left->left = new TreeNode(5);
    root->right->right = new TreeNode(9);

    root->left->left->left = new TreeNode(6);
    root->right->right->left = new TreeNode(7);

    Solution obj;

    cout << "Width = " << obj.widthOfBinaryTree(root) << endl;

    return 0;
}