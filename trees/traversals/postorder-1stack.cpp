// LeetCode 145: Binary Tree Postorder Traversal (Iterative Using 1 Stack)
// Time Complexity: O(N) -> Where N is the total number of nodes in the tree, visiting each node at most twice
// Space Complexity: O(H) -> Where H is the height of the tree, representing the maximum size of the stack
// Approach: Go left as much as possible, pushing nodes to the stack. When hitting NULL, check the right child of the stack's top node.
// If a right child exists and hasn't been processed, move to it. Otherwise, process the current node, pop it, and ensure we don't re-enter already completed subtrees.

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
        stack<TreeNode*> st;
        TreeNode* cur = root;

        // Traverse the tree until both the current pointer and the stack are completely empty
        while (cur != NULL || !st.empty()) {
            if (cur != NULL) {
                st.push(cur);  // Keep track of the path to look back during backtracking
                cur = cur->left; // Deep dive down the left branch first
            } else {
                // Left boundary hit, check the right subtree of the node currently at the top of the stack
                TreeNode* temp = st.top()->right;

                if (temp != NULL) {
                    // Right child exists, so switch our focus to process this right subtree first
                    cur = temp;
                } else {
                    // No right child exists; we can safely process the current leaf/subtree root node
                    temp = st.top();
                    st.pop();
                    postorder.push_back(temp->val);

                    // Backtrack up the tree, popping parent nodes whose right subtrees have just been fully processed
                    while (!st.empty() && temp == st.top()->right) {
                        temp = st.top();
                        st.pop();
                        postorder.push_back(temp->val);
                    }
                }
            }
        }
        return postorder;
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
    //          1
    //         / \
    //        2   7
    //       /   /
    //      3   8
    //     /
    //    4
    //     \
    //      5
    //       \
    //        6
    TreeNode* root = new TreeNode(1);
    root->left = new TreeNode(2);
    root->right = new TreeNode(7);
    root->left->left = new TreeNode(3);
    root->right->left = new TreeNode(8);
    root->left->left->left = new TreeNode(4);
    root->left->left->left->right = new TreeNode(5);
    root->left->left->left->right->right = new TreeNode(6);

    Solution sol;
    vector<int> result = sol.postorderTraversal(root);

    cout << "Postorder Traversal output:\n[ ";
    for (int val : result) {
        cout << val << " ";
    }
    cout << "]\n";

    // Expected Output:
    // [ 6 5 4 3 2 8 7 1 ]

    deleteTree(root);

    return 0;
}