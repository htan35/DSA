// LeetCode 257: Binary Tree Paths (String Copy Pass-by-Value Approach)
// Time Complexity: O(N * H) -> Where N is the total number of nodes and H is the tree height. We visit each node once, but passing the path string by value creates a copy of size proportional to the depth at each recursive step.
// Space Complexity: O(H^2) -> Due to the recursion stack of depth H, where each frame stores a unique path string copy of length up to O(H).
// Approach: Use a pre-order DFS traversal. Pass the accumulating `path` string by value to each recursive call. 
// Append the current node's value to the path string immediately. If a leaf node is encountered, add the current path directly to the global `res` vector. 
// When branching down to children, append the arrow delimiter `"->"` to the passed copy, eliminating the need for an explicit numeric backtracking pop step.

#include <iostream>
#include <vector>
#include <string>

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
    vector<string> res;

    void solve(TreeNode* root, string path) {
        // Base case: If we hit an empty node, terminate traversal along this branch
        if (root == NULL) {
            return;
        }

        // Action step: Append the current node value directly to this function frame's copy of the path string
        path += to_string(root->val);

        // Leaf Validation: If it's a leaf node, this specific tracking path sequence is complete
        if (root->left == NULL && root->right == NULL) {
            res.push_back(path);
        }

        // Branching Step: Forward a new path copy containing the arrow delimiter to the children.
        // Because 'path' is passed by value, returning up from a child automatically restores the path string to the parent's state without manual deletion.
        solve(root->left, path + "->");
        solve(root->right, path + "->");
    }

    vector<string> binaryTreePaths(TreeNode* root) {
        res.clear(); // Reset instance state variables before initiating execution sweep
        solve(root, "");
        return res;
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
    //       \
    //        5
    TreeNode* root = new TreeNode(1);
    root->left = new TreeNode(2);
    root->right = new TreeNode(3);
    root->left->right = new TreeNode(5);

    Solution sol;
    vector<string> result = sol.binaryTreePaths(root);

    cout << "Binary Tree Paths output:\n";
    for (const string& p : result) {
        cout << "[ " << p << " ]\n";
    }

    // Expected Output:
    // [ 1->2->5 ]
    // [ 1->3 ]

    deleteTree(root);
    return 0;
}