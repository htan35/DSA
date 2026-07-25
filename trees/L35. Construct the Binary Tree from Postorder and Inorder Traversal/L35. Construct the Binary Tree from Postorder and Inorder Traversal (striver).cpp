/*
 * Approach: Divide and Conquer with Hash Map Optimization (Inorder & Postorder)
 * -----------------------------------------------------------------------------
 * 1. Postorder traversal visits nodes in (Left -> Right -> Root) order, so the last element 
 *    `postorder[pe]` is always the root of the current subtree.
 * 2. Inorder traversal visits nodes in (Left -> Root -> Right) order. We locate the root's 
 *    position (`inRoot`) in `inorder` using a Hash Map (`hm`) for O(1) lookups.
 * 3. Calculate `numsLeft = inRoot - is`, which represents the number of nodes in the left subtree.
 * 4. Recursively build the left and right subtrees using boundary indices:
 *    - Left subtree:  inorder range  [is, inRoot - 1], 
 *                     postorder range [ps, ps + numsLeft - 1]
 *    - Right subtree: inorder range  [inRoot + 1, ie], 
 *                     postorder range [ps + numsLeft, pe - 1]
 * 
 * Time Complexity:  O(N) - Hash map construction takes O(N) time, and each node is processed once.
 * Space Complexity: O(N) - Space required for the hash map + recursion call stack (O(H) on average, O(N) in worst case).
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
    TreeNode* buildTree(vector<int>& inorder, vector<int>& postorder) {
        if (inorder.size() != postorder.size())
            return NULL;

        map<int, int> hm;

        for (int i = 0; i < inorder.size(); ++i)
            hm[inorder[i]] = i;

        return buildTreePostIn(inorder, 0, inorder.size() - 1, 
                               postorder, 0, postorder.size() - 1, hm);
    }

    TreeNode* buildTreePostIn(vector<int> &inorder, int is, int ie,
                             vector<int> &postorder, int ps, int pe,
                             map<int, int> &hm) {
        if (ps > pe || is > ie) return NULL;

        TreeNode* root = new TreeNode(postorder[pe]);

        int inRoot = hm[postorder[pe]];
        int numsLeft = inRoot - is;

        root->left = buildTreePostIn(inorder, is, inRoot - 1,
                                     postorder, ps, ps + numsLeft - 1, hm);

        root->right = buildTreePostIn(inorder, inRoot + 1, ie,
                                      postorder, ps + numsLeft, pe - 1, hm);

        return root;
    }
};

// Helper function to print tree in Preorder format to verify tree structure
void printPreorder(TreeNode* node) {
    if (!node) return;
    cout << node->val << " ";
    printPreorder(node->left);
    printPreorder(node->right);
}

int main() {
    /*
        Inorder   = [40, 20, 50, 10, 60, 30]
        Postorder = [40, 50, 20, 60, 30, 10]

        Constructed Tree:
               10
             /    \
           20      30
          /  \    /
        40   50  60
    */

    vector<int> inorder = {40, 20, 50, 10, 60, 30};
    vector<int> postorder = {40, 50, 20, 60, 30, 10};

    Solution obj;
    TreeNode* root = obj.buildTree(inorder, postorder);

    cout << "Preorder of constructed tree: ";
    printPreorder(root);
    cout << endl;

    return 0;
}