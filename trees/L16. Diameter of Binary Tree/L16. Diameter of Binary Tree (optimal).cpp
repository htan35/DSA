// LeetCode 543: Diameter of Binary Tree (Optimized O(N) Approach)
// Time Complexity: O(N) -> Where N is the total number of nodes in the binary tree, as we visit each node exactly once
// Space Complexity: O(H) -> Where H is the height of the tree, representing the maximum call stack depth due to recursion
// Approach: Combine the height calculation pass with the diameter tracking pass using a single bottom-up post-order DFS. 
// At each node, calculate the left and right subtree heights. The local path passing through that node is (l + r). 
// Update the global maximum diameter reference variable `maxi` if this local path is greater, and return the node's actual height up to the parent.

#include <iostream>
#include <algorithm>

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
    int height(TreeNode *node, int &maxi) {
        // Base case: An empty tree has a height of 0
        if (node == NULL) return 0;
                
        // Recursively compute the max height of the left and right subtrees
        int l = height(node->left, maxi);
        int r = height(node->right, maxi);
        
        // Update the running global maximum diameter tracking variable with the path turning at the current node
        maxi = max(maxi, l + r);
        
        // Return the structural height of the current node up to its parent caller
        return 1 + max(l, r);
    }

    int diameterOfBinaryTree(TreeNode* root) {
        if (root == NULL) return 0;
        int maxi = 0;
        height(root, maxi); // Trigger the bottom-up combination pass
        return maxi;
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
    //            1
    //           / \
    //          2   3
    //             / \
    //            4   6
    //           /     \
    //          5       7
    //         /         \
    //        9           8
    TreeNode* root = new TreeNode(1);
    root->left = new TreeNode(2);
    root->right = new TreeNode(3);
    root->right->left = new TreeNode(4);
    root->right->right = new TreeNode(6);
    root->right->left->left = new TreeNode(5);
    root->right->right->right = new TreeNode(7);
    root->right->left->left->left = new TreeNode(9);
    root->right->right->right->right = new TreeNode(8);

    Solution sol;
    int diameter = sol.diameterOfBinaryTree(root);

    cout << "Diameter of Binary Tree: " << diameter << endl;

    // Expected Output:
    // Diameter of Binary Tree: 6

    deleteTree(root);

    return 0;
}