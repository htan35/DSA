// LeetCode 102: Binary Tree Level Order Traversal
// Time Complexity: O(N) -> Where N is the total number of nodes in the binary tree
// Space Complexity: O(N) -> Due to the queue data structure used for Breadth-First Search (BFS)
#include <iostream>
#include <vector>
#include <queue>

using namespace std;

// Definition for a binary tree node structure provided in your screenshot
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
    // Core function matching the exact implementation logic from your image
    vector<vector<int>> levelOrder(TreeNode* root) {
        vector<vector<int>> ans;
        if (root == NULL) return ans; // Base condition: check if the tree is empty

        queue<TreeNode*> q;
        q.push(root); // Initialize queue by pushing the root node

        while (!q.empty()) {
            int size = q.size(); // Identify the number of elements present at the current level
            vector<int> level;

            // Iterate precisely through all elements of the current level
            for (int i = 0; i < size; i++) {
                TreeNode *node = q.front();
                q.pop(); // Pop out the front node

                // Push children nodes into the queue if they exist
                if (node->left != NULL) q.push(node->left);   //
                if (node->right != NULL) q.push(node->right); //

                level.push_back(node->val); // Store node values for this particular level row
            }
            ans.push_back(level); // Append the completed level row to our final nested answer matrix
        }
        return ans; // Return the 2D matrix level sequence tracking
    }
};

// Helper function to safely delete tree nodes and free allocated memory
void deleteTree(TreeNode* root) {
    if (root == nullptr) return;
    deleteTree(root->left);
    deleteTree(root->right);
    delete root;
}

int main() {
    // Constructing a sample binary tree matching standard structures:
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
    vector<vector<int>> result = sol.levelOrder(root);

    // Print output grouped level-by-level
    cout << "Level Order Traversal output:\n";
    for (const auto& level : result) {
        cout << "[ ";
        for (int val : level) {
            cout << val << " ";
        }
        cout << "]\n";
    }
    // Expected Output:
    // [ 3 ]
    // [ 9 20 ]
    // [ 15 7 ]

    // Clean up dynamic allocations
    deleteTree(root);

    return 0;
}