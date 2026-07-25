/*
 * Approach: Recursive Construction with Preorder Index Tracking (codestorywithMIK)
 * -------------------------------------------------------------------------------
 * 1. Maintain a running index `idx` (passed by reference) pointing to the current root node 
 *    in `preorder`.
 * 2. At each recursive call:
 *    - Store the root value from `preorder[idx]`.
 *    - Search for this root value in the current `inorder` range `[start, end]` using a loop.
 *    - Increment `idx` so that the next recursive calls process subsequent elements in `preorder`.
 * 3. Create the `root` node with `rootVal`.
 * 4. Recursively build `root->left` using the left range `[start, i - 1]`.
 * 5. Recursively build `root->right` using the right range `[i + 1, end]`.
 * 
 * Time Complexity:  O(N^2) - Finding the index in `inorder` takes O(N) linear search time in the worst case (e.g., skewed trees).
 * Space Complexity: O(H)   - O(N) in the worst-case (skewed tree) or O(log N) in a balanced tree due to the recursion stack.
 */

#include <iostream>
#include <vector>

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
    TreeNode* solve(vector<int>& preorder, vector<int>& inorder, int start, int end, int& idx) {
        if (start > end) {
            return NULL;
        }

        int rootVal = preorder[idx];
        int i = start;

        for (; i <= end; i++) {
            if (inorder[i] == rootVal) {
                break;
            }
        }

        idx++;
        TreeNode* root = new TreeNode(rootVal);
        root->left = solve(preorder, inorder, start, i - 1, idx);
        root->right = solve(preorder, inorder, i + 1, end, idx);

        return root;
    }

    TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
        int n = preorder.size();

        int idx = 0;

        return solve(preorder, inorder, 0, n - 1, idx);
    }
};

// Helper function to print tree in Inorder format
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