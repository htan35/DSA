/*
 * Approach: Divide and Conquer with Hash Map Optimization
 * --------------------------------------------------------
 * 1. Preorder traversal visits nodes in (Root -> Left -> Right) order, so the first element 
 *    `preorder[preStart]` is always the root of the current subtree.
 * 2. Inorder traversal visits nodes in (Left -> Root -> Right) order. We locate the root's 
 *    position (`inRoot`) in `inorder` using a Hash Map (`inMap`) for O(1) lookups.
 * 3. Calculate `numsLeft = inRoot - inStart`, which represents the total number of nodes in 
 *    the left subtree.
 * 4. Recursively build the left and right subtrees by passing appropriate boundary indices:
 *    - Left subtree:  preorder range [preStart + 1, preStart + numsLeft], 
 *                     inorder range  [inStart, inRoot - 1]
 *    - Right subtree: preorder range [preStart + numsLeft + 1, preEnd], 
 *                     inorder range  [inRoot + 1, inEnd]
 * 
 * Time Complexity:  O(N) - Building the map takes O(N) time, and each node is processed once during recursion.
 * Space Complexity: O(N) - O(N) space for hash map + recursion call stack (O(H) on average, O(N) in worst case).
 */

#include <iostream>
#include <vector>
#include <map>

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
    TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
        map<int, int> inMap;

        for (int i = 0; i < inorder.size(); i++) {
            inMap[inorder[i]] = i;
        }

        TreeNode* root = buildTree(preorder, 0, preorder.size() - 1,
                                   inorder, 0, inorder.size() - 1, inMap);
        return root;
    }

    TreeNode* buildTree(vector<int>& preorder, int preStart, int preEnd,
                        vector<int>& inorder, int inStart, int inEnd, map<int, int>& inMap) {
        if (preStart > preEnd || inStart > inEnd) return nullptr;

        TreeNode* root = new TreeNode(preorder[preStart]);

        int inRoot = inMap[root->val];
        int numsLeft = inRoot - inStart;

        root->left = buildTree(preorder, preStart + 1, preStart + numsLeft,
                               inorder, inStart, inRoot - 1, inMap);

        root->right = buildTree(preorder, preStart + numsLeft + 1, preEnd,
                                inorder, inRoot + 1, inEnd, inMap);

        return root;
    }
};

// Helper function to print tree in Level Order format
void printInorder(TreeNode* node) {
    if (!node) return;
    printInorder(node->left);
    cout << node->val << " ";
    printInorder(node->right);
}

int main() {
    /*
        Preorder = [3, 9, 20, 15, 7]
        Inorder  = [9, 3, 15, 20, 7]

        Constructed Tree:
               3
              / \
             9  20
               /  \
              15   7
    */

    vector<int> preorder = {3, 9, 20, 15, 7};
    vector<int> inorder = {9, 3, 15, 20, 7};

    Solution obj;
    TreeNode* root = obj.buildTree(preorder, inorder);

    cout << "Inorder of constructed tree: ";
    printInorder(root);
    cout << endl;

    return 0;
}