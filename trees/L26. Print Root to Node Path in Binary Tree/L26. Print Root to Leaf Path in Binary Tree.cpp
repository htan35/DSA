// InterviewBit / LeetCode: Path to Given Node
// Time Complexity: O(N) -> Where N is the total number of nodes in the binary tree, as we visit each node at most once
// Space Complexity: O(H) -> Where H is the height of the tree, representing the maximum call stack depth due to recursion
// Approach: Use a backtracking pre-order DFS traversal. Unconditionally push the current node's value into the tracking array `arr`.
// If the current node contains the target value `x`, return true to signal the path has been successfully found. 
// Otherwise, recursively check the left and right subtrees. If both return false, backtrack by removing the current node from `arr` via `pop_back()` and return false.

#include <iostream>
#include <vector>

using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

class Solution {
public:
    bool getPath(TreeNode *root, vector<int> &arr, int x) {
        // Base Case: If we reach a NULL pointer, the target node does not exist along this path
        if (!root) return false;

        // Step 1: Assume the current node belongs to the path and push it to the tracker
        arr.push_back(root->val);

        // Target Found: If the current node matches target 'x', terminate early and propagate success upwards
        if (root->val == x) return true;

        // Step 2: Recursively look for the target node down the left OR right subtrees
        if (getPath(root->left, arr, x) || getPath(root->right, arr, x)) {
            return true;
        }

        // Backtracking Step: If execution reaches here, the target 'x' is not present in either subtree.
        // Remove the current node from our tracked path array before returning up to the caller.
        arr.pop_back();
        return false;
    }

    vector<int> solve(TreeNode* A, int B) {
        vector<int> arr;
        if (A == NULL) return arr;
        
        getPath(A, arr, B);
        return arr;
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
    //     / \
    //    4   5
    TreeNode* root = new TreeNode(1);
    root->left = new TreeNode(2);
    root->right = new TreeNode(3);
    root->left->left = new TreeNode(4);
    root->left->right = new TreeNode(5);

    Solution sol;
    int target = 5;
    vector<int> result = sol.solve(root, target);

    cout << "Path to Node " << target << ":\n[ ";
    for (int val : result) {
        cout << val << " ";
    }
    cout << "]\n";

    // Expected Output:
    // [ 1 2 5 ]

    deleteTree(root);
    return 0;
}