// LeetCode 701: Insert into a Binary Search Tree (Iterative Approach)
// Time Complexity: O(H) -> Where H is the height of the BST. Takes O(log N) for a balanced tree and O(N) for a skewed tree.
// Space Complexity: O(1) -> Uses a constant amount of extra space since we traverse using a loop rather than recursion stack frames.
// Approach: Maintain a `curr` pointer to traverse down the tree and a `parent` pointer to track the last non-null node.
// We guide `curr` left or right using the standard BST properties until it hits a `NULL` slot. 
// Finally, we hook the new node to either the left or right pointer of the `parent` node.

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
    TreeNode* insertIntoBST(TreeNode* root, int val) {
        // Edge Case: If the tree is entirely empty, the new node becomes the root
        if (root == nullptr) {
            return new TreeNode(val);
        }

        TreeNode* curr = root;
        TreeNode* parent = nullptr;

        // Step 1: Traverse down the tree to locate the correct empty position
        while (curr != nullptr) {
            parent = curr; // Keep track of the current node before moving down
            
            if (val < curr->val) {
                curr = curr->left;  // BST Rule: Smaller values go left
            } else {
                curr = curr->right; // BST Rule: Larger values go right
            }
        }

        // Step 2: Hook up the new node to the parent we tracked
        if (val < parent->val) {
            parent->left = new TreeNode(val);
        } else {
            parent->right = new TreeNode(val);
        }

        return root;
    }
};

void printInOrder(TreeNode* root) {
    if (root == nullptr) return;
    printInOrder(root->left);
    cout << root->val << " ";
    printInOrder(root->right);
}

void deleteTree(TreeNode* root) {
    if (root == nullptr) return;
    deleteTree(root->left);
    deleteTree(root->right);
    delete root;
}

int main() {
    // Constructing a standard Binary Search Tree (BST):
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
    int newValue = 5;
    root = sol.insertIntoBST(root, newValue);

    cout << "In-order traversal after inserting " << newValue << ":\n";
    printInOrder(root);
    cout << endl;

    // Expected Output:
    // 1 2 3 4 5 7 

    deleteTree(root);
    return 0;
}