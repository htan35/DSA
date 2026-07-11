// LeetCode 101: Symmetric Tree
// Time Complexity: O(N) -> Where N is the total number of nodes in the binary tree, as we visit each node exactly once
// Space Complexity: O(H) -> Where H is the height of the tree, representing the maximum depth of the recursive call stack
// Approach: A tree is symmetric if its left and right subtrees are mirror images of each other. 
// We check this recursively by comparing two nodes at a time: their values must be equal, the left child of the first node 
// must match the right child of the second node, and the right child of the first node must match the left child of the second node.

#include <iostream>

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
    // Helper function to check if two subtrees are structural mirrors of each other
    bool symm(TreeNode *p, TreeNode *q){
        // Base case: If both nodes are NULL, they match perfectly
        if(p == NULL && q == NULL) return true;
        
        // Base case: If only one node is NULL, the structures do not match
        if(p == NULL || q == NULL) return false;

        // Mirror condition: Values must match, and outer branches (p->left, q->right) 
        // must mirror each other, along with the inner branches (p->right, q->left).
        return (p->val == q->val) 
            && symm(p->left, q->right) 
            && symm(p->right, q->left);
    }

    bool isSymmetric(TreeNode* root) {
       
        if(root == NULL) return true;
        
        // Split the validation check between the left and right structural paths
        return symm(root->left, root->right);
    }
};

void deleteTree(TreeNode* root) {
    if (root == nullptr) return;
    deleteTree(root->left);
    deleteTree(root->right);
    delete root;
}

int main() {
    // Constructing a sample symmetric binary tree:
    //        1
    //       / \
    //      2   2
    //     / \ / \
    //    3  4 4  3
    TreeNode* root = new TreeNode(1);
    root->left = new TreeNode(2);
    root->right = new TreeNode(2);
    root->left->left = new TreeNode(3);
    root->left->right = new TreeNode(4);
    root->right->left = new TreeNode(4);
    root->right->right = new TreeNode(3);

    Solution sol;
    bool result = sol.isSymmetric(root);

    cout << "Is the tree symmetric: " << (result ? "True" : "False") << endl;

    // Expected Output:
    // Is the tree symmetric: True

    deleteTree(root);
    return 0;
}