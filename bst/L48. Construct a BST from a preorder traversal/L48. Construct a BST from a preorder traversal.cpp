/*
 * Approach: Construct BST from Preorder Traversal using Upper Bound
 * ----------------------------------------------------------------
 * 1. Maintain a global index `i` (passed by reference) that tracks the current root candidate in `preorder`.
 * 2. Pass an `upperbound` constraint to each recursive call:
 *    - For the left subtree, the upper bound is the current node's value (`root->val`).
 *    - For the right subtree, the upper bound remains the parent's upper bound (`bound`).
 * 3. Base Case:
 *    - If `i == preorder.size()` or `preorder[i] > bound`, return `NULL` (the current element cannot belong to this subtree).
 * 4. Create a new node with `preorder[i]`, increment `i`, and recursively build `left` and `right` subtrees.
 * 
 * Time Complexity:  O(N) - Every element in the preorder array is visited once.
 * Space Complexity: O(H) - Recursion stack space proportional to tree height H (O(log N) balanced, O(N) worst case).
 */

#include <iostream>
#include <vector>
#include <climits>

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
    TreeNode* bst(vector<int>& preorder, int& i, int bound) {
        if (i == preorder.size() || preorder[i] > bound) return NULL;

        TreeNode* root = new TreeNode(preorder[i]);
        i++;

        root->left = bst(preorder, i, root->val);
        root->right = bst(preorder, i, bound);

        return root;
    }

    TreeNode* bstFromPreorder(vector<int>& preorder) {
        int i = 0;
        return bst(preorder, i, INT_MAX);
    }
};

// Helper function to print tree level order for testing
void printInorder(TreeNode* root) {
    if (!root) return;
    printInorder(root->left);
    cout << root->val << " ";
    printInorder(root->right);
}

int main() {
    /*
        Preorder: [8, 5, 1, 7, 10, 12]
        
        Constructed BST:
                 8
               /   \
              5     10
             / \      \
            1   7      12
    */

    vector<int> preorder = {8, 5, 1, 7, 10, 12};

    Solution obj;
    TreeNode* root = obj.bstFromPreorder(preorder);

    cout << "Inorder traversal of constructed BST (should be sorted):" << endl;
    printInorder(root);
    cout << endl;

    return 0;
}