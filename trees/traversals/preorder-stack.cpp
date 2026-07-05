// LeetCode 144: Binary Tree Preorder Traversal (Iterative)
// Time Complexity: O(N) -> Where N is the total number of nodes in the binary tree
// Space Complexity: O(N) -> In the worst-case scenario (e.g., a skewed tree), the stack can hold up to N nodes
//push root, pop root, print value, push right child, push left child, repeat until stack is empty
#include <iostream>
#include <vector>
#include <stack>

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
    // Core iterative function matching the exact structure from your screenshot
    vector<int> preorderTraversal(TreeNode* root) {
        vector<int> preorder;
        if(root == NULL) return preorder; // Base condition: if tree is empty, return empty vector

        stack<TreeNode*> st; // Stack tracking nodes iteratively
        st.push(root); // Initialize by pushing the root node

        while(!st.empty()){
            root = st.top(); 
            st.pop(); 
            
            preorder.push_back(root->val); // Process the current node value (Root)

            // CRITICAL: Push the right child first so that the left child is popped and processed first (LIFO)
            if(root->right != NULL){
                st.push(root->right); // Push right child if it exists
            }
            if(root->left != NULL){
                st.push(root->left); // Push left child if it exists
            }
        }
        return preorder; // Return the final preorder traversal list
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
    // Constructing a sample binary tree to test:
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
    vector<int> result = sol.preorderTraversal(root);

    // Print out the accumulated sequence
    cout << "Iterative Pre-order Traversal output: ";
    for (int val : result) {
        cout << val << " ";
    }
    // Expected Output: 1 2 4 5 3
    cout << "\n";

    // Clean up dynamic memory
    deleteTree(root);

    return 0;
}