// LeetCode 257: Binary Tree Paths
// Time Complexity: O(N) -> Where N is the total number of nodes in the binary tree, as we visit each node exactly once
// Space Complexity: O(H) -> Where H is the height of the tree, representing the maximum recursion depth due to backtracking stack frames
// Approach: Use a backtracking pre-order DFS traversal. Track the current path by pushing each node's value into a `temp` vector.
// Upon reaching a leaf node, record a snapshot of the completed path sequence into `ans`. 
// Pop the node from `temp` before returning up to allow correct path exploration along alternate branches. Finally, format the paths into strings using "->".

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
    bool isleaf(TreeNode *node){
        if(node->left == NULL && node->right == NULL) return true;
        return false;
    }
    
    void path(TreeNode* node, vector<int> &temp, vector<vector<int>>&ans){
        if(node == NULL) return;

        // Pre-order processing step: push the current node value onto the tracking path container
        temp.push_back(node->val);

        // Base case validation: if it's a leaf node, record the full completed path snapshot
        if(isleaf(node)){
            ans.push_back(temp);
            temp.pop_back(); // Backtrack: remove the leaf node before returning up to the parent caller
            return;
        }

        // Recursively traverse the left branch if it exists
        if(node->left != NULL){
            path(node->left, temp, ans);
        }
        
        // Recursively traverse the right branch if it exists
        if(node->right != NULL){
            path(node->right, temp, ans);
        }

        // Backtrack: remove the current node value as we finish exploring both its children completely
        temp.pop_back();
        return;
    }

    vector<string> binaryTreePaths(TreeNode* root) {
        vector<vector<int>> ans;
        vector<int> temp;
        vector<string> s;
        
        if(root == NULL) return s;
        
        // Collect all numeric paths using the backtracking DFS engine
        path(root, temp, ans);
        
        // Post-processing Phase: Convert the collected paths into formatted string sequences
        for (int i = 0; i < ans.size(); i++) {
            string str = "";
            for (int j = 0; j < ans[i].size(); j++) {
                str += to_string(ans[i][j]);
                if (j != ans[i].size() - 1) str += "->";
            }
            s.push_back(str);
        }
        return s;  
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