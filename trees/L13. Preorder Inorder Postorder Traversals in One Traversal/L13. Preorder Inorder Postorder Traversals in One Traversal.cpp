// All-in-One Binary Tree Traversal (Preorder, Inorder, Postorder) in a Single Pass
// Time Complexity: O(3N) = O(N) -> Every node is pushed to/popped from the stack exactly 3 times (for state 1, 2, and 3).
// Space Complexity: O(N) -> For storing the stack frame during execution and returning traversal vectors.
// Approach: State-Based Iterative Traversal using a Stack
// We push pairs of {node, state} onto the stack:
// - State 1: Preorder -> Record value, increment state to 2, push left child (state 1) onto stack.
// - State 2: Inorder  -> Record value, increment state to 3, push right child (state 1) onto stack.
// - State 3: Postorder -> Record value, don't push current node back.

#include <iostream>
#include <vector>
#include <stack>

using namespace std;

// Definition for a binary tree node.
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution {
public:
    // Function that computes Preorder, Inorder, and Postorder traversals simultaneously
    vector<vector<int>> preInPostTraversal(TreeNode* root) {
        vector<int> pre, in, post;
        
        // Base case check for empty tree
        if (root == NULL) return {};

        stack<pair<TreeNode*, int>> st;
        st.push({root, 1});

        while (!st.empty()) {
            auto it = st.top();
            st.pop();

            // State 1: Part of Preorder
            // Increment state to 2, push back to stack, then push left child
            if (it.second == 1) {
                pre.push_back(it.first->val);
                it.second++;
                st.push(it);

                if (it.first->left != NULL) {
                    st.push({it.first->left, 1});
                }
            }
            // State 2: Part of Inorder
            // Increment state to 3, push back to stack, then push right child
            else if (it.second == 2) {
                in.push_back(it.first->val);
                it.second++;
                st.push(it);

                if (it.first->right != NULL) {
                    st.push({it.first->right, 1});
                }
            }
            // State 3: Part of Postorder
            // Don't push current node back to stack
            else {
                post.push_back(it.first->val);
            }
        }

        // Return all three traversals formatted together
        return {pre, in, post};
    }
};

int main() {
    // Constructing the Binary Tree:
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
    vector<vector<int>> result = sol.preInPostTraversal(root);

    vector<string> labels = {"Preorder", "Inorder", "Postorder"};
    for (int i = 0; i < result.size(); i++) {
        cout << labels[i] << ": ";
        for (int val : result[i]) {
            cout << val << " ";
        }
        cout << endl;
    }

    /*
     Expected Output:
     Preorder:  1 2 4 5 3 
     Inorder:   4 2 5 1 3 
     Postorder: 4 5 2 3 1 
    */

    return 0;
}