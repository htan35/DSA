//return node->val + max(0, max(l, r));
//"When returning to my parent, never carry a negative branch."
//ls = max(0, pathsum(root->left)); and rs = max(0, pathsum(root->right));
//"When forming a path through the current node, never include a negative subtree."
#include <iostream>
#include <algorithm>
using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;

    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *l, TreeNode *r) : val(x), left(l), right(r) {}
};

class Solution {
public:
    
// if(sum<0) sum =0;

    int pathsum(TreeNode *node){
        if(node == NULL) return 0;
        //if(sum < 0) sum = 0 ;
        
        // int l = pathsum(node->left, sum);
        // int r = pathsum(node->right, sum);
        int l = pathsum(node->left);
        int r = pathsum(node->right);
        // sum=l+r+node->val;

        return node->val + max(0,max(l,r));
    }

    int maxi = INT_MIN;

    int maxPathSum(TreeNode* root) {
        if(root == NULL) return 0;
        int sum = 0;

        int ls = max(0, pathsum(root->left));
        int rs = max(0, pathsum(root->right));
        // int ls = pathsum(root->left);
        // int rs = pathsum(root->right);

        maxi = max (maxi , ls+rs+root->val);

        int lt = maxPathSum(root->left);
        int rt = maxPathSum(root->right);

        return maxi;

        
    }
};

int main() {

    // Example Tree:
    //
    //          -10
    //         /   \
    //        9     20
    //             /  \
    //            15   7
    //
    // Answer = 42

    TreeNode* root = new TreeNode(-10);

    root->left = new TreeNode(9);

    root->right = new TreeNode(20);
    root->right->left = new TreeNode(15);
    root->right->right = new TreeNode(7);

    Solution obj;

    cout << "Maximum Path Sum = " << obj.maxPathSum(root);

    return 0;
}