// LeetCode 236: Lowest Common Ancestor of a Binary Tree (Optimized O(N) DFS Approach)
// Time Complexity: O(N) -> Where N is the total number of nodes in the binary tree, as we visit each node at most once
// Space Complexity: O(H) -> Where H is the height of the tree, representing the maximum call stack depth due to recursion
// Approach: Perform a bottom-up post-order DFS traversal. If the current node matches either target node `p` or `q`, or is NULL, return it.
// The left and right subtrees evaluate recursively. If both returns (`left` and `right`) are non-NULL, it implies one target was found in 
// the left branch and the other in the right, making the current node the LCA. Otherwise, cascade the non-NULL child upward.

#include <iostream>

using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

class Solution {
public:
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        // Base case: If we hit a NULL pointer, or if we find either of the target nodes p or q, 
        // return the current node immediately to signal a match to the parent caller.
        if (root == NULL || root == p || root == q) {
            return root;
        }

        // Recursively look for target nodes in the left and right subtrees
        TreeNode* left = lowestCommonAncestor(root->left, p, q);
        TreeNode* right = lowestCommonAncestor(root->right, p, q);

        // Result evaluations based on returned indicators:
        // Case 1: If left branch yields nothing, the answer or matching nodes must reside entirely in the right branch
        if (left == NULL) {
            return right;
        }
        // Case 2: If right branch yields nothing, the answer or matching nodes must reside entirely in the left branch
        else if (right == NULL) {
            return left;
        }
        // Case 3: If both left and right are NOT null, it means one target node was found on the left side 
        // and the other was found on the right side. Thus, the current root is their lowest common ancestor.
        else {
            return root;
        }
    }
};

void deleteTree(TreeNode* root) {
    if (root == nullptr) return;
    deleteTree(root->left);
    deleteTree(root->right);
    delete root;
}

int main() {
    // Constructing the exact sample binary tree from your image context:
    //            1
    //          /   \
    //         2     3
    //        / \   / \
    //       4   5 8   9
    //          / \
    //         6   7
    TreeNode* root = new TreeNode(1);
    root->left = new TreeNode(2);
    root->right = new TreeNode(3);
    root->left->left = new TreeNode(4);
    root->left->right = new TreeNode(5);
    root->right->left = new TreeNode(8);
    root->right->right = new TreeNode(9);
    root->left->right->left = new TreeNode(6);
    root->left->right->right = new TreeNode(7);

    TreeNode* p = root->left->left;          // Node 4
    TreeNode* q = root->left->right->right;   // Node 7

    Solution sol;
    TreeNode* result = sol.lowestCommonAncestor(root, p, q);

    if (result != nullptr) {
        cout << "LCA(" << p->val << ", " << q->val << ") = " << result->val << endl;
    }

    // Expected Output:
    // LCA(4, 7) = 2

    deleteTree(root);
    return 0;
}