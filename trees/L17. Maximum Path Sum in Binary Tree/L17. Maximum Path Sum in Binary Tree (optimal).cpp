// LeetCode 124: Binary Tree Maximum Path Sum
// Time Complexity: O(N) -> Where N is the total number of nodes in the binary tree, as we visit each node exactly once
// Space Complexity: O(H) -> Where H is the height of the tree, representing the maximum call stack depth due to recursion
// Approach: Perform a bottom-up post-order DFS traversal. For each node, compute the maximum path sums from its left and right subtrees.
// To handle negative node values, use `max(0, ...)` to ignore any branch that yields a negative contribution. 
// Update the global maximum path sum tracking variable `maxi` using the combined paths (`left + right + node->val`), and return the best single-branch path up to the parent.

#include <iostream>
#include <algorithm>
#include <climits>

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
    int maxPathDown(TreeNode* node, int &maxi) {
        if (node == NULL) return 0;

        // Compute the max path sum recursively for the left and right subtrees
        // Crucial step: Use max(0, value) to completely discard subtrees that contribute negative sums
        int left = max(0, maxPathDown(node->left, maxi));
        int right = max(0, maxPathDown(node->right, maxi));

        // Update the global maximum tracking variable by considering the path that curves through the current node
        maxi = max(maxi, left + right + node->val);

        // Return the maximum sum of a single straight path extending downward through either the left or right branch
        return max(left, right) + node->val;
    }

    int maxPathSum(TreeNode* root) {
        int maxi = INT_MIN; // Initialize with the lowest possible integer value to handle entirely negative trees
        maxPathDown(root, maxi);
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
    // Constructing a sample binary tree with negative values:
    //         -10
    //         /  \
    //        9    20
    //            /  \
    //           15   7
    TreeNode* root = new TreeNode(-10);
    root->left = new TreeNode(9);
    root->right = new TreeNode(20);
    root->right->left = new TreeNode(15);
    root->right->right = new TreeNode(7);

    Solution sol;
    int result = sol.maxPathSum(root);

    cout << "Maximum Path Sum: " << result << endl;

    // Expected Output:
    // Maximum Path Sum: 42

    deleteTree(root);

    return 0;
}