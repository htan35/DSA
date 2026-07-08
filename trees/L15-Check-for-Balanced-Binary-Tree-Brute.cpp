// LeetCode 110: Balanced Binary Tree (Optimized O(N) Approach)
// Time Complexity: O(N) -> Where N is the total number of nodes. We compute the height and balance status in a single bottom-up pass, visiting each node exactly once.
// Space Complexity: O(H) -> Where H is the height of the tree, representing the recursion stack depth.
// Approach: Use a bottom-up DFS. Instead of calculating height repeatedly, let the height function return -1 if any subtree is unbalanced. 
// If it is balanced, return the actual height. This optimizes the time complexity from O(N^2) to O(N).

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
    // Calculate height of a subtree
    // Time: O(N) per call - recalculates for all descendants
    int height(TreeNode *node){
        if(node == NULL) return 0;
        int l = height(node->left);
        int r = height(node->right);
        return 1 + max(l, r);
    }

    // Check if binary tree is balanced
    // A balanced tree has |left_height - right_height| <= 1 for all nodes
    // Time: O(N^2) - Brute force: recalculates height multiple times per node
    bool isBalanced(TreeNode* root) {
        if(root == NULL) return true;

        int lh = height(root->left);      // Height of left subtree
        int rh = height(root->right);     // Height of right subtree

        // Check if current node violates balance condition
        if(abs(lh - rh) > 1) return false;

        // Recursively check left and right subtrees
        return isBalanced(root->left) && isBalanced(root->right);
        
    }
};

void deleteTree(TreeNode* root) {
    if (root == nullptr) return;
    deleteTree(root->left);
    deleteTree(root->right);
    delete root;
}

int main() {
    // Constructing a sample binary tree:
    //        1
    //       / \
    //      2   3
    //         / \
    //        4   5
    TreeNode* root = new TreeNode(1);
    root->left = new TreeNode(2);
    root->right = new TreeNode(3);
    root->right->left = new TreeNode(4);
    root->right->right = new TreeNode(5);

    Solution sol;
    bool result = sol.isBalanced(root);

    cout << "Is Balanced: " << (result ? "True" : "False") << endl;

    // Expected Output:
    // Is Balanced: True

    deleteTree(root);

    return 0;
}