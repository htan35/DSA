/*
 * Approach: Recursive Construction with Postorder Index Tracking (Decrementing)
 * -------------------------------------------------------------------------------
 * 1. Postorder traversal visits nodes in (Left -> Right -> Root) order. Traversing 
 *    backward from the end (`idx = n - 1`) gives root nodes in reverse order.
 * 2. Maintain a running index `idx` (passed by reference) starting from `n - 1`.
 * 3. At each recursive call:
 *    - Store the root value from `postorder[idx]`.
 *    - Search for `rootVal` in `inorder` within range `[start, end]` to find split index `i`.
 *    - Create the `root` node with `rootVal`.
 *    - Decrement `idx` (`idx--`) to move to the next root candidate in postorder.
 * 4. Build `root->right` BEFORE `root->left` because scanning postorder backward 
 *    encounters the right subtree roots before the left subtree roots.
 * 
 * Time Complexity:  O(N^2) - Linear search for root index in `inorder` takes O(N) in worst case (skewed trees).
 * Space Complexity: O(H)   - Recursion stack takes O(N) in worst case or O(log N) for balanced trees.
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
    TreeNode* solve(vector<int>& inorder, vector<int>& postorder, int start, int end, int& idx) {
        if (start > end) return NULL;

        int rootVal = postorder[idx];
        int i = start;
        for (; i <= end; i++) {
            if (inorder[i] == rootVal) break;
        }

        TreeNode* root = new TreeNode(rootVal);

        idx--;

        // Right subtree must be built first when moving backward in postorder
        root->right = solve(inorder, postorder, i + 1, end, idx);
        root->left  = solve(inorder, postorder, start, i - 1, idx);

        return root;
    }

    TreeNode* buildTree(vector<int>& inorder, vector<int>& postorder) {
        int n = postorder.size();
        int idx = n - 1;

        return solve(inorder, postorder, 0, n - 1, idx);
    }
};

// Helper function to print tree in Preorder format to verify standard structure
void printPreorder(TreeNode* node) {
    if (!node) return;
    cout << node->val << " ";
    printPreorder(node->left);
    printPreorder(node->right);
}

int main() {
    /*
        Inorder   = [9, 3, 15, 20, 7]
        Postorder = [9, 15, 7, 20, 3]

        Constructed Tree:
               3
              / \
             9  20
               /  \
              15   7
    */

    vector<int> inorder = {9, 3, 15, 20, 7};
    vector<int> postorder = {9, 15, 7, 20, 3};

    Solution obj;
    TreeNode* root = obj.buildTree(inorder, postorder);

    cout << "Preorder traversal of constructed tree: ";
    printPreorder(root);
    cout << endl;

    return 0;
}