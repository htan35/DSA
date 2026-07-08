// LeetCode 543: Diameter of Binary Tree (Brute Force Approach)
// Time Complexity: O(N^2) -> Where N is the total number of nodes. We calculate the height of left and right subtrees for every single node in the tree via a separate O(N) path computation.
// Space Complexity: O(H) -> Where H is the height of the tree, representing the maximum depth of the recursive call stack.
// Approach: The diameter passing through a specific node is the sum of the maximum heights of its left and right subtrees (lh + rh).
// We update a global maximum diameter variable at each node, and then recursively call the function on both left and right children to check every possible turning point.

#include <iostream>
#include <algorithm>

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
private:
    int maxi = 0; // Tracks the global maximum diameter found across all nodes processed

    // Helper function to find the maximum height of a subtree
    int findHeight(TreeNode* node) {
        if (node == nullptr) return 0;
        int lh = findHeight(node->left);
        int rh = findHeight(node->right);
        return 1 + max(lh, rh);
    }

public:
    void findMax(TreeNode* node) {
        if (node == NULL) return;

        // Calculate the longest path branches down the left and right subtrees from the current node
        int lh = findHeight(node->left);
        int rh = findHeight(node->right);

        // Update the global maximum if the path passing through the current node (lh + rh) is longer
        maxi = max(maxi, lh + rh);

        // Recursively run the same diameter check on left and right children to find other turning points
        findMax(node->left);
        findMax(node->right);
    }

    int diameterOfBinaryTree(TreeNode* root) {
        maxi = 0; // Reset global state before starting traversal
        findMax(root);
        return maxi;
    }
};

void deleteTree(TreeNode* root) {
    if (root == nullptr) return;
    deleteTree(root->left);
    deleteTree(root->right);
    delete root;
}

int main() {
    // Constructing the exact sample binary tree from your image:
    //            1
    //           / \
    //          2   3
    //             / \
    //            4   6
    //           /     \
    //          5       7
    //         /         \
    //        9           8
    TreeNode* root = new TreeNode(1);
    root->left = new TreeNode(2);
    root->right = new TreeNode(3);
    root->right->left = new TreeNode(4);
    root->right->right = new TreeNode(6);
    root->right->left->left = new TreeNode(5);
    root->right->right->right = new TreeNode(7);
    root->right->left->left->left = new TreeNode(9);
    root->right->right->right->right = new TreeNode(8);

    Solution sol;
    int diameter = sol.diameterOfBinaryTree(root);

    cout << "Diameter of Binary Tree: " << diameter << endl;

    // Expected Output:
    // Diameter of Binary Tree: 6

    deleteTree(root);

    return 0;
}