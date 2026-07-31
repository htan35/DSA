/*
 * Approach: Bottom-Up Post-Order Traversal (Optimal O(N))
 * -----------------------------------------------------
 * 1. Define a helper class `NodeValue` that stores:
 *    - `minNode`: Smallest value in the subtree.
 *    - `maxNode`: Largest value in the subtree.
 *    - `maxSize`: Size of the largest BST within this subtree.
 * 
 * 2. Base Case:
 *    - For an empty tree (`!root`), return `NodeValue(INT_MAX, INT_MIN, 0)`. 
 *      This inverted boundary guarantees any parent node can comfortably satisfy BST conditions.
 * 
 * 3. Bottom-Up Validation:
 *    - Process left and right subtrees first.
 *    - If `left.maxNode < root->val` AND `root->val < right.minNode`, the current subtree forms a valid BST!
 *      Return updated bounds along with size: `left.maxSize + right.maxSize + 1`.
 *    - Otherwise, return `NodeValue(INT_MIN, INT_MAX, max(left.maxSize, right.maxSize))` to signal 
 *      to parent nodes that this subtree is invalid (by setting maxNode to INF and minNode to -INF).
 * 
 * Time Complexity:  O(N) - Every node in the binary tree is visited exactly once.
 * Space Complexity: O(H) - Auxiliary call stack space proportional to tree height H (O(log N) balanced, O(N) worst case).
 */

#include <iostream>
#include <climits>
#include <algorithm>

using namespace std;

// Definition for a binary tree node.
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;

    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

class NodeValue {
public:
    int maxNode, minNode, maxSize;

    NodeValue(int minNode, int maxNode, int maxSize) {
        this->maxNode = maxNode;
        this->minNode = minNode;
        this->maxSize = maxSize;
    }
};

class Solution {
private:
    NodeValue largestBSTSubtreeHelper(TreeNode* root) {
        // An empty tree is a BST of size 0.
        if (!root) {
            return NodeValue(INT_MAX, INT_MIN, 0);
        }

        // Get values from left and right subtree of current tree.
        auto left = largestBSTSubtreeHelper(root->left);
        auto right = largestBSTSubtreeHelper(root->right);

        // Current node is greater than max in left AND smaller than min in right, it is a BST.
        if (left.maxNode < root->val && root->val < right.minNode) {
            // It is a BST.
            return NodeValue(
                min(root->val, left.minNode),
                max(root->val, right.maxNode),
                left.maxSize + right.maxSize + 1
            );
        }

        // Otherwise, return [-inf, inf] so that parent can't be valid BST
        return NodeValue(INT_MIN, INT_MAX, max(left.maxSize, right.maxSize));
    }

public:
    int largestBSTSubtree(TreeNode* root) {
        return largestBSTSubtreeHelper(root).maxSize;
    }
};

int main() {
    /*
             50
           /    \
         30      60
        /  \    /  \
       5   20  45   70
                   /  \
                  65  80

       The largest BST subtree is rooted at node 60 with size = 5:
             60
            /  \
           45   70
               /  \
              65  80
    */

    TreeNode* root = new TreeNode(50);
    root->left = new TreeNode(30);
    root->right = new TreeNode(60);

    root->left->left = new TreeNode(5);
    root->left->right = new TreeNode(20);

    root->right->left = new TreeNode(45);
    root->right->right = new TreeNode(70);
    root->right->right->left = new TreeNode(65);
    root->right->right->right = new TreeNode(80);

    Solution obj;
    cout << "Size of Largest BST Subtree: " << obj.largestBSTSubtree(root) << endl;

    return 0;
}