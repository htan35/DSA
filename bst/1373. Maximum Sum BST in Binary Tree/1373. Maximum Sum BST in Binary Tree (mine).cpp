/*
 * Approach: Top-Down Recursion (O(N^2)) - Max Sum BST
 * ----------------------------------------------------
 * 1. `check`: Traverses every node in the binary tree (O(N)).
 * 2. `isbst`: For each node, checks if the subtree rooted at that node 
 *    forms a valid BST using boundary constraints (O(N)).
 * 3. If valid, `isbst` computes the subtree sum bottom-up through the reference parameter `currentSum`.
 * 4. We track and update `maxi` with the highest sum found.
 * 
 * Time Complexity:  O(N^2) - For each of the N nodes, we potentially traverse its subtree to validate and sum.
 * Space Complexity: O(H)   - Call stack depth equal to the height of the tree.
 */

#include <iostream>
#include <climits>
#include <algorithm>

using namespace std;

// Definition of TreeNode
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;

    TreeNode(int x) {
        val = x;
        left = right = NULL;
    }
};

class Solution {
public:
    // Helper function to validate BST and calculate subtree sum
    bool isbst(TreeNode* node, long long low, long long high, int& currentSum) {
        if (node == NULL) {
            currentSum = 0;
            return true;
        }

        if (node->val <= low || node->val >= high) {
            return false;
        }

        int leftSum = 0, rightSum = 0;

        if (!isbst(node->left, low, node->val, leftSum)) return false;
        if (!isbst(node->right, node->val, high, rightSum)) return false;

        currentSum = leftSum + rightSum + node->val;
        return true;
    }

    // Main top-down traversal checking every node
    void check(TreeNode* root, int& maxi) {
        if (root == NULL) return;

        int currentSum = 0;

        // If subtree rooted at 'root' is a valid BST, evaluate its sum
        if (isbst(root, LLONG_MIN, LLONG_MAX, currentSum)) {
            maxi = max(maxi, currentSum);
        }

        // Recursively check left and right subtrees
        check(root->left, maxi);
        check(root->right, maxi);
    }

    int maxSumBST(TreeNode* root) {
        int maxi = 0; // Per problem constraints, empty BST has sum 0
        check(root, maxi);
        return maxi;
    }
};

// 🔹 Driver Code
int main() {
    /*
            10
           /  \
          5    15
         / \   / \
        1   8 12 20
           /
          6
    */

    TreeNode* root = new TreeNode(10);

    root->left = new TreeNode(5);
    root->right = new TreeNode(15);

    root->left->left = new TreeNode(1);
    root->left->right = new TreeNode(8);
    root->left->right->left = new TreeNode(6);

    root->right->left = new TreeNode(12);
    root->right->right = new TreeNode(20);

    Solution obj;
    int result = obj.maxSumBST(root);

    cout << "Maximum Sum BST: " << result << endl;

    return 0;
}