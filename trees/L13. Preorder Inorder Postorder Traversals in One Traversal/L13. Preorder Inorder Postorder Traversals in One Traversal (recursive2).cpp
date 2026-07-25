#include <iostream>
#include <vector>

using namespace std;

// Definition for a binary tree node.
struct TreeNode {
    int data;
    TreeNode* left;
    TreeNode* right;

    TreeNode(int val) {
        data = val;
        left = nullptr;
        right = nullptr;
    }
};

class Solution {
private:
    void solve(TreeNode* node, vector<int>& ino, vector<int>& pre, vector<int>& post) {
        if (node == nullptr) return;

        // 1. Preorder (Root -> Left -> Right)
        pre.push_back(node->data);

        // Process Left Subtree
        solve(node->left, ino, pre, post);

        // 2. Inorder (Left -> Root -> Right)
        ino.push_back(node->data);

        // Process Right Subtree
        solve(node->right, ino, pre, post);

        // 3. Postorder (Left -> Right -> Root)
        post.push_back(node->data);
    }

public:
    vector<vector<int>> treeTraversal(TreeNode* root) {
        vector<int> ino, pre, post;
        
        solve(root, ino, pre, post);

        vector<vector<int>> ans;
        // Standard Output Order: [Inorder, Preorder, Postorder]
        ans.push_back(ino);
        ans.push_back(pre);
        ans.push_back(post);

        return ans;
    }
};

// Helper function to print results
void printVector(const string& label, const vector<int>& vec) {
    cout << label << ": ";
    for (int val : vec) {
        cout << val << " ";
    }
    cout << endl;
}

int main() {
    /*
            1
           / \
          2   3
         / \
        4   5
    */

    TreeNode* root = new TreeNode(1);
    root->left = new TreeNode(2);
    root->right = new TreeNode(3);
    root->left->left = new TreeNode(4);
    root->left->right = new TreeNode(5);

    Solution sol;
    vector<vector<int>> traversals = sol.treeTraversal(root);

    printVector("Inorder  ", traversals[0]);
    printVector("Preorder ", traversals[1]);
    printVector("Postorder", traversals[2]);

    return 0;
}