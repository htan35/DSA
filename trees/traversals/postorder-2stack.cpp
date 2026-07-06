// LeetCode 145: Binary Tree Postorder Traversal (Iterative 2-Stack Approach)
// Time Complexity: O(N) -> Where N is the total number of nodes in the binary tree
// Space Complexity: O(N) -> Where N is the number of elements stored in the auxiliary stack space (SC)
// Approach: Push root into st1. While st1 is not empty, pop a node, push it into st2, and push its left child then right child into st1.
// Finally, pop all elements from st2 to get the Left->Right->Root sequence.

#include <iostream>
#include <vector>
#include <stack>

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
    vector<int> postorderTraversal(TreeNode* root) {
        vector<int> postorder;
        if (root == NULL) return postorder;

        stack<TreeNode*> st1, st2;
        st1.push(root);

        while (!st1.empty()) {
            root = st1.top();
            st1.pop();
            st2.push(root); 

            // Push left before right into st1 so that right is popped first, 
            // causing right to enter st2 before left. This guarantees left is on top of st2.
            if (root->left != NULL) {
                st1.push(root->left);
            }
            if (root->right != NULL) {
                st1.push(root->right);
            }
        }

        // Empty st2 to extract elements in the correct Left-Right-Root postorder sequence
        while (!st2.empty()) {
            postorder.push_back(st2.top()->val);
            st2.pop();
        }

        return postorder;
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
    //        1
    //         \
    //          2
    //         /
    //        3
    TreeNode* root = new TreeNode(1);
    root->right = new TreeNode(2);
    root->right->left = new TreeNode(3);

    Solution sol;
    vector<int> result = sol.postorderTraversal(root);

    // Print output sequence
    cout << "Postorder Traversal output:\n[ ";
    for (int val : result) {
        cout << val << " ";
    }
    cout << "]\n";

    // Expected Output:
    // [ 3 2 1 ]

    // Clean up dynamic allocations
    deleteTree(root);

    return 0;
}