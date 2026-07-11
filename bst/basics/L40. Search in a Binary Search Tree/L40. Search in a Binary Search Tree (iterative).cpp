// LeetCode 700: Search in a Binary Search Tree (Iterative Approach)
// Time Complexity: O(H) -> Where H is the height of the BST. Takes O(log N) for a balanced tree and O(N) for a skewed tree.
// Space Complexity: O(1) -> Eliminates the recursion call stack by tracking the path using a single pointer variable.
// Approach: Utilize the structural sorted property of a Binary Search Tree (BST) within a loop.
// While our tracking pointer is not NULL and has not hit the target value, we shift it down:
// moving left if the target is smaller than the current node's value, or right if it's larger.

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
    TreeNode* searchBST(TreeNode* root, int val) {
        TreeNode* curr = root;

        // Traverse down the tree until we hit a NULL boundary or find the matching value
        while (curr != nullptr && curr->val != val) {
            if (val < curr->val) {
                curr = curr->left;  // BST Rule: Target is smaller, so search left branch
            } else {
                curr = curr->right; // BST Rule: Target is larger, so search right branch
            }
        }

        // Returns either the matching node pointer or nullptr if it wasn't found
        return curr;
    }
};

void deleteTree(TreeNode* root) {
    if (root == nullptr) return;
    deleteTree(root->left);
    deleteTree(root->right);
    delete root;
}

int main() {
    // Constructing a standard sample Binary Search Tree (BST):
    //        4
    //       / \
    //      2   7
    //     / \
    //    1   3
    TreeNode* root = new TreeNode(4);
    root->left = new TreeNode(2);
    root->right = new TreeNode(7);
    root->left->left = new TreeNode(1);
    root->left->right = new TreeNode(3);

    Solution sol;
    int target = 2;
    TreeNode* result = sol.searchBST(root, target);

    if (result != NULL) {
        cout << "Subtree rooted at found node: " << result->val << endl;
    } else {
        cout << "Node not found." << endl;
    }

    // Expected Output:
    // Subtree rooted at found node: 2

    deleteTree(root);
    return 0;
}