// LeetCode 94: Binary Tree Inorder Traversal (Iterative Approach)
// Time Complexity: O(N) -> Where N is the total number of nodes in the binary tree
// Space Complexity: O(H) -> Where H is the height of the tree, representing the auxiliary stack space (SC)
// push into stack until reaching the leftmost node, when null then pop and process nodes, moving to the right child
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
    // Core iterative function matching the exact structure and annotations from your screenshot
    vector<int> inorderTraversal(TreeNode* root) {
        stack<TreeNode*> st;       
        TreeNode* node = root;     
        vector<int> inorder;       

        while(true) {              
            if(node != NULL) {     
                st.push(node);     // st.push(node); -> Stack space (SC)
                node = node->left; 
            } 
            else {                 
                if(st.empty() == true) break; 
                
                node = st.top();   
                st.pop();          
                
                inorder.push_back(node->val); 
                node = node->right;           
            }
        }
        return inorder;           
    }
};

// Helper function to safely clean up tree allocations
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
    vector<int> result = sol.inorderTraversal(root);

    // Print out the gathered sequence
    cout << "Iterative In-order Traversal output: ";
    for (int val : result) {
        cout << val << " ";
    }
    // Expected Output: 4 2 5 1 3
    cout << "\n";

    // Clean up dynamic memory
    deleteTree(root);

    return 0;
}