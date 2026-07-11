// LeetCode 450: Delete Node in a BST (Iterative Approach with Structural Rewiring)
// Time Complexity: O(H) -> Where H is the height of the BST. Takes O(log N) for a balanced tree and O(N) for a skewed tree.
// Space Complexity: O(1) -> Iterative structural restructuring eliminates any call stack overhead.
// Approach: 
// 1. Locate the target node containing `key` using standard iterative BST search rules while keeping a reference to the parent.
// 2. Pass the target node to the `helper` function to handle its deletion and restyle the tree links.
// 3. The `helper` logic works by grafting the right subtree onto the rightmost node of the left subtree, preserving the BST invariant.

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
    // Finds the rightmost (maximum value) node in a given subtree
    TreeNode* findLastRight(TreeNode* root) {
        if (root->right == nullptr) {
            return root;
        }
        return findLastRight(root->right);
    }

    // Deletes the node and re-wires its left and right branches structurally
    TreeNode* helper(TreeNode* root) {
        if (root->left == nullptr) {
            return root->right;
        } 
        else if (root->right == nullptr) {
            return root->left;
        }

        TreeNode* rightChild = root->right;
        // Locate the rightmost node of the left subtree (largest value smaller than root)
        TreeNode* lastRight = findLastRight(root->left);
        // Link the right child of the deleted node to this position
        lastRight->right = rightChild;

        return root->left;
    }

    TreeNode* deleteNode(TreeNode* root, int key) {
        if (root == nullptr) {
            return nullptr;
        }

        // Edge Case: If the root node itself holds the target key
        if (root->val == key) {
            TreeNode* newRoot = helper(root);
            delete root;
            return newRoot;
        }

        TreeNode* dummy = root;
        while (root != nullptr) {
            if (root->val > key) {
                // If the left child is the target, replace it with the restructured node
                if (root->left != nullptr && root->left->val == key) {
                    TreeNode* target = root->left;
                    root->left = helper(root->left);
                    delete target;
                    break;
                } else {
                    root = root->left;
                }
            } else {
                // If the right child is the target, replace it with the restructured node
                if (root->right != nullptr && root->right->val == key) {
                    TreeNode* target = root->right;
                    root->right = helper(root->right);
                    delete target;
                    break;
                } else {
                    root = root->right;
                }
            }
        }
        return dummy;
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
    // Constructing the exact Binary Search Tree from your screenshot:
    //             9
    //            / \
    //           8   12
    //          /   /  \
    //         5   10  13
    //        / \   \
    //       3   7   11
    //      / \ / \
    //     2  4 6  8
    //    /
    //   1
    TreeNode* root = new TreeNode(9);
    root->left = new TreeNode(8);
    root->right = new TreeNode(12);
    
    root->left->left = new TreeNode(5);
    root->right->left = new TreeNode(10);
    root->right->right = new TreeNode(13);
    
    root->left->left->left = new TreeNode(3);
    root->left->left->right = new TreeNode(7);
    root->right->left->right = new TreeNode(11);
    
    root->left->left->left->left = new TreeNode(2);
    root->left->left->left->right = new TreeNode(4);
    root->left->left->right->left = new TreeNode(6);
    root->left->left->right->right = new TreeNode(8);
    
    root->left->left->left->left->left = new TreeNode(1);

    Solution sol;
    int keyToDelete = 5;
    root = sol.deleteNode(root, keyToDelete);

    cout << "In-order traversal after deleting node " << keyToDelete << ":\n";
    printInOrder(root);
    cout << endl;

    // Expected Output:
    // 1 2 3 4 6 7 8 8 9 10 11 12 13 

    deleteTree(root);
    return 0;
}