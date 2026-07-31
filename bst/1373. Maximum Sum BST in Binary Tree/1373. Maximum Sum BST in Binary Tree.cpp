/*
 * Approach: Bottom-Up Post-Order Traversal (O(N) Optimal)
 * --------------------------------------------------------
 * 1. Define helper class `Nodevalue` storing:
 *    - `minNode`: Smallest node value in current subtree.
 *    - `maxNode`: Largest node value in current subtree.
 *    - `sum`    : Sum of node values in current subtree if it forms a valid BST.
 * 
 * 2. Base Case:
 *    - Empty node (`!root`) returns `Nodevalue(INT_MAX, INT_MIN, 0)`.
 *    - Boundary inversion (min=INT_MAX, max=INT_MIN) lets any valid parent node satisfy:
 *      `left.maxNode < root->val` and `root->val < right.minNode`.
 * 
 * 3. Validation & Fallback:
 *    - If subtree is a valid BST: return updated bounds and `left.sum + right.sum + root->val`.
 *      Update global `maxSum` using `max(currSum, maxSum)`.
 *    - If invalid BST: return `Nodevalue(INT_MIN, INT_MAX, 0)` so parent subtrees
 *      are invalidated while ignoring this node's sum contribution.
 * 
 * Time Complexity:  O(N) - Single post-order traversal visiting every node once.
 * Space Complexity: O(H) - Auxiliary stack space proportional to tree height H.
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

class Nodevalue {
public:
    int maxNode, minNode, sum;

    Nodevalue(int minNode, int maxNode, int sum) {
        this->maxNode = maxNode;
        this->minNode = minNode;
        this->sum = sum;
    }
};

class Solution {
private:
    int maxSum = 0;

    Nodevalue largestBSTSubtreeHelper(TreeNode* root) {
        // An empty tree is a BST of size 0 / sum 0.
        if (!root) {
            return Nodevalue(INT_MAX, INT_MIN, 0);
        }

        // Get values from left and right subtree of current tree.
        auto left = largestBSTSubtreeHelper(root->left);
        auto right = largestBSTSubtreeHelper(root->right);

        // Current node is greater than max in left AND smaller than min in right, it is a BST.
        if (left.maxNode < root->val && root->val < right.minNode) {
            // It is a BST.
            int currSum = left.sum + right.sum + root->val;
            maxSum = max(currSum, maxSum);

            return Nodevalue(
                min(root->val, left.minNode),
                max(root->val, right.maxNode),
                currSum
            );
        }

        // Otherwise, return [-inf, inf] so that parent can't be valid BST.
        // sum = 0 says "ignore this subtree's sum completely"
        return Nodevalue(INT_MIN, INT_MAX, 0);
    }

public:
    int maxSumBST(TreeNode* root) {
        maxSum = 0;
        largestBSTSubtreeHelper(root);
        return maxSum;
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

       Valid BST with max sum is rooted at node 5:
             5
            / \
           1   8
              /
             6
       Sum = 5 + 1 + 8 + 6 = 20
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
    cout << "Maximum Sum BST: " << obj.maxSumBST(root) << endl;

    return 0;
}