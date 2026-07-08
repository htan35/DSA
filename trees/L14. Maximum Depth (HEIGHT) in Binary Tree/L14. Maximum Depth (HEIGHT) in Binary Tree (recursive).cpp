// LeetCode 104: Maximum Depth of Binary Tree
// Time Complexity: O(N) -> Where N is the total number of nodes in the binary tree, as we visit each node exactly once
// Space Complexity: O(H) -> Where H is the height of the tree, representing the maximum call stack depth due to recursion
// Approach: Recursively find the maximum height of the left and right subtrees. 
// The maximum depth at the current node is 1 plus the maximum of the two subtree heights.
// HEIGHT OF A TREE = NUMBER OF LEVELS = NUMBER OF ROWS IN LEVEL ORDER TRAVERSAL
// IF ONLY ROOT IS PRESENT, HEIGHT = 1

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
public:
    int maxDepth(TreeNode* root) {
        // Base case: An empty tree has a depth of 0
        if (root == NULL) return 0;
        
        // Compute depth of left and right subtrees independently via post-order bottom-up calculation
        int lh = maxDepth(root->left);
        int rh = maxDepth(root->right);

        // Add 1 to include the current node level itself along with the deepest path found below
        return 1 + max(lh, rh);
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
    //        3
    //       / \
    //      9  20
    //        /  \
    //       15   7
    TreeNode* root = new TreeNode(3);
    root->left = new TreeNode(9);
    root->right = new TreeNode(20);
    root->right->left = new TreeNode(15);
    root->right->right = new TreeNode(7);

    Solution sol;
    int depth = sol.maxDepth(root);

    cout << "Maximum Depth of Binary Tree: " << depth << endl;

    // Expected Output:
    // Maximum Depth of Binary Tree: 3

    deleteTree(root);

    return 0;
}