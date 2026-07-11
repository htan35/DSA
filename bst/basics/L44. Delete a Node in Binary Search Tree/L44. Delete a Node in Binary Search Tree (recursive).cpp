// LeetCode 450: Delete Node in a BST (Optimized Recursive Approach)
// Time Complexity: O(H) -> Where H is the height of the BST. Takes O(log N) for a balanced tree and O(N) for a skewed tree.
// Space Complexity: O(H) -> System call stack depth proportional to the height of the tree due to recursion.
// Approach:
// 1. Use the BST property to find the node to delete recursively.
// 2. Once the target node is found, handle the 3 standard deletion cases:
//    - Case 1: Node has no children (leaf node) -> Delete it and return nullptr.
//    - Case 2: Node has only one child -> Delete it and return its non-null child directly.
//    - Case 3: Node has two children -> Find its inorder successor (smallest node in the right subtree), 
//              replace the target node's value with the successor's value, and recursively delete that successor.

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
private:
    // Helper function to find the minimum value node in a given BST subtree
    TreeNode* findMin(TreeNode* root) {
        while (root->left != nullptr) {
            root = root->left;
        }
        return root;
    }

public:
    TreeNode* deleteNode(TreeNode* root, int key) {
        // Base Case: The key does not exist in the tree
        if (root == nullptr) {
            return nullptr;
        }

        // Step 1: Search for the target node to delete
        if (key < root->val) {
            root->left = deleteNode(root->left, key);
        } 
        else if (key > root->val) {
            root->right = deleteNode(root->right, key);
        } 
        // Step 2: Target node found (`root->val == key`)
        else {
            // Case 1 & 2: Leaf node or node with only one child
            if (root->left == nullptr) {
                TreeNode* temp = root->right;
                delete root;
                return temp; // Connects directly to parent frame
            } 
            else if (root->right == nullptr) {
                TreeNode* temp = root->left;
                delete root;
                return temp; // Connects directly to parent frame
            }

            // Case 3: Node with two children
            // Find the inorder successor (smallest element in the right subtree)
            TreeNode* temp = findMin(root->right);
            
            // Copy the successor's value to the current node
            root->val = temp->val;
            
            // Recursively delete the copied successor node from the right branch
            root->right = deleteNode(root->right, temp->val);
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
    // Constructing the exact Binary Search Tree from your context:
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

    cout << "In-order traversal after deleting node " << keyToDelete << " recursively:\n";
    printInOrder(root);
    cout << endl;

    // Expected Output:
    // 1 2 3 4 6 7 8 8 9 10 11 12 13 

    deleteTree(root);
    return 0;
}