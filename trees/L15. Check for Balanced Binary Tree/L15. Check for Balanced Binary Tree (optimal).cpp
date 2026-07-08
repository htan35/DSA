// LeetCode 110: Balanced Binary Tree (Optimized Bottom-Up DFS Approach)
// Time Complexity: O(N) -> Where N is the total number of nodes in the binary tree, as we visit each node exactly once
// Space Complexity: O(H) -> Where H is the height of the tree, representing the maximum call stack depth due to recursion
// Approach: Traverse down to the leaf nodes via post-order DFS. Each subtree returns its height if balanced.
// If any node breaches the balance rule (abs(lh - rh) > 1), it returns -1. This error state cascades up immediately, cutting off extra work.

#include <iostream>
#include <algorithm>
#include <cmath>

using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

class Solution {
public:
    int dfsHeight(TreeNode *root) {
        // Base case: An empty tree has a valid height of 0
        if (root == NULL) return 0;

        // Recursively compute the left subtree's height
        int leftHeight = dfsHeight(root->left);
        if (leftHeight == -1) return -1; // Cascade failure immediately if the left branch is unbalanced

        // Recursively compute the right subtree's height
        int rightHeight = dfsHeight(root->right);
        if (rightHeight == -1) return -1; // Cascade failure immediately if the right branch is unbalanced

        // Balance Check: If the absolute height difference between branches exceeds 1, return -1 to signal an invalid tree
        if (abs(leftHeight - rightHeight) > 1) return -1;

        // Current subtree is balanced; compute its height and return it up to the caller
        return max(leftHeight, rightHeight) + 1;
    }

    bool isBalanced(TreeNode* root) {
        // The tree is balanced if and only if our bottom-up helper completes without returning the -1 error flag
        return dfsHeight(root) != -1;
    }
};

void deleteTree(TreeNode* root) {
    if (root == nullptr) return;
    deleteTree(root->left);
    deleteTree(root->right);
    delete root;
}

int main() {
    // Constructing an unbalanced sample binary tree to test the cascade logic:
    //        1
    //       / \
    //      2   3
    //     /
    //    4
    //   /
    //  5
    TreeNode* root = new TreeNode(1);
    root->left = new TreeNode(2);
    root->right = new TreeNode(3);
    root->left->left = new TreeNode(4);
    root->left->left->left = new TreeNode(5);

    Solution sol;
    bool result = sol.isBalanced(root);

    cout << "Is Balanced: " << (result ? "True" : "False") << endl;

    // Expected Output:
    // Is Balanced: False

    deleteTree(root);

    return 0;
}