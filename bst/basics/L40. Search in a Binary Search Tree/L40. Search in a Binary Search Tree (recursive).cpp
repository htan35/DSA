// LeetCode 700: Search in a Binary Search Tree
// Time Complexity: O(H) -> Where H is the height of the BST. In the best case (balanced tree), it takes O(log N); in the worst case (skewed tree), it takes O(N).
// Space Complexity: O(H) -> Due to the recursive call stack space proportional to the height of the tree.
// Approach: Utilize the structural properties of a Binary Search Tree (BST). 
// If the target value is smaller than the current node's value, recursively narrow the search path down to the left subtree.
// If the target value is larger, branch right. Terminate and return the node if a match is hit, or return NULL if the path runs empty.

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
        // Base case: Target is not present if we drop down to a NULL pointer boundary
        if (root == NULL) return NULL;

        // Success condition: Target matching node is successfully located
        if (root->val == val) return root;

        // BST Rule: Values smaller than the parent reside strictly inside the left subtree branch
        if (val < root->val) {
            return searchBST(root->left, val);
        }

        // BST Rule: Values larger than the parent reside strictly inside the right subtree branch
        return searchBST(root->right, val);
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