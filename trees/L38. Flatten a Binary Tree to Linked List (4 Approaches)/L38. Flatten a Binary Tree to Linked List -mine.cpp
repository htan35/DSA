/*
 * Approach: Preorder Traversal with Dummy Node (Pointer Reference Track)
 * ---------------------------------------------------------------------
 * 1. We use a helper function `solve` that accepts the current node and a reference to a `temp` pointer (`TreeNode*& temp`).
 * 2. Before rewiring pointers, we store `node->left` and `node->right` in temporary variables (`leftChild`, `rightChild`) 
 *    to prevent losing access to subtrees.
 * 3. We attach the current node to `temp->right`, set `temp->left = nullptr`, and advance `temp` to `node`.
 * 4. Recursively call `solve` on `leftChild` and `rightChild`.
 * 5. A `dummy` node is used to simplify initial link management (though `root` remains the start of the flattened tree).
 * 
 * Time Complexity:  O(N) - Every node in the binary tree is visited exactly once.
 * Space Complexity: O(H) - O(N) in the worst-case (skewed tree) or O(log N) in a balanced tree due to the recursion call stack.
 */

#include <iostream>
using namespace std;

// Definition for a binary tree node.
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;

    TreeNode(int x) {
        val = x;
        left = nullptr;
        right = nullptr;
    }
};

class Solution {
public:
    void solve(TreeNode* node, TreeNode*& temp) {
        if (!node) return;

        TreeNode* leftChild = node->left;
        TreeNode* rightChild = node->right;

        temp->right = node;
        temp->left = nullptr;
        temp = node;

        solve(leftChild, temp);
        solve(rightChild, temp);
    }

    void flatten(TreeNode* root) {
        if (!root) return;

        TreeNode* dummy = new TreeNode(-1);
        TreeNode* temp = dummy;

        solve(root, temp);
    }
};

// Print flattened tree
void printList(TreeNode* root) {
    while (root) {
        cout << root->val << " ";
        root = root->right;
    }
    cout << endl;
}

int main() {

    /*
            1
           / \
          2   5
         / \   \
        3   4   6

    Expected Flattened:
    1 -> 2 -> 3 -> 4 -> 5 -> 6
    */

    TreeNode* root = new TreeNode(1);

    root->left = new TreeNode(2);
    root->right = new TreeNode(5);

    root->left->left = new TreeNode(3);
    root->left->right = new TreeNode(4);

    root->right->right = new TreeNode(6);

    Solution obj;
    obj.flatten(root);

    cout << "Flattened Tree: ";
    printList(root);

    return 0;
}