/*
 * Approach: Iterative BST Traversal (Inorder Successor & Predecessor)
 * -------------------------------------------------------------------
 * 1. Successor (Smallest value strictly greater than target->val):
 *    - If `target->val >= root->val`, the successor must be in the right subtree.
 *      Move `root = root->right`.
 *    - If `target->val < root->val`, `root` is a candidate successor.
 *      Save it and move left to look for a smaller valid candidate.
 *
 * 2. Predecessor (Largest value strictly smaller than target->val):
 *    - If `target->val <= root->val`, the predecessor must be in the left subtree.
 *      Move `root = root->left`.
 *    - If `target->val > root->val`, `root` is a candidate predecessor.
 *      Save it and move right to look for a larger valid candidate.
 *
 * Time Complexity: O(H), where H is the height of the BST.
 * Space Complexity: O(1)
 */

#include <iostream>
#include<bits/stdc++.h>
#include <string>

using namespace std;

// Definition for a binary tree node.
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;

    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution {
public:
    TreeNode* inorderSuccessor(TreeNode* root, TreeNode* target) {
        TreeNode* successor = NULL;

        while (root != NULL) {
            if (target->val >= root->val) {
                root = root->right;
            } else {
                successor = root;
                root = root->left;
            }
        }

        return successor;
    }

    TreeNode* inorderPredecessor(TreeNode* root, TreeNode* target) {
        TreeNode* predecessor = NULL;

        while (root != NULL) {
            if (target->val <= root->val) {
                root = root->left;
            } else {
                predecessor = root;
                root = root->right;
            }
        }

        return predecessor;
    }
};

int main() {
    /*
             5
           /   \
          2     7
         / \   / \
        1   4 6   9
    */

    TreeNode* root = new TreeNode(5);
    root->left = new TreeNode(2);
    root->right = new TreeNode(7);
    root->left->left = new TreeNode(1);
    root->left->right = new TreeNode(4);
    root->right->left = new TreeNode(6);
    root->right->right = new TreeNode(9);

    Solution obj;

    // Target node
    TreeNode* target = root->left->right;   // Node with value 4

    TreeNode* pred = obj.inorderPredecessor(root, target);
    TreeNode* succ = obj.inorderSuccessor(root, target);

    cout << "Target Node: " << target->val << endl;
    cout << "Predecessor: " << (pred ? to_string(pred->val) : "NULL") << endl;
    cout << "Successor:   " << (succ ? to_string(succ->val) : "NULL") << endl;

    return 0;
}