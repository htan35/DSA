// LeetCode 100: Same Tree (Optimized Recursive DFS Approach)
// Time Complexity: O(N) -> Where N is the minimum number of nodes between both trees, visiting each node exactly once
// Space Complexity: O(H) -> Where H is the height of the smaller tree, representing the recursion stack depth
// Approach: Recursively traverse both trees simultaneously using a pre-order DFS pass. 
// At each node, evaluate if one or both pointers are NULL. If both pointers are valid, assert that their structural 
// values match, and recursively validate that both their left subtrees and right subtrees match.

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
public:
    bool isSameTree(TreeNode* p, TreeNode* q) {
        // Base case: If either tree node is NULL, return true only if BOTH are NULL (p == q)
        if (p == NULL || q == NULL) {
            return (p == q);
        }

        // Structural Check: Validate the value of the current matching positions, 
        // then recursively ensure that the left children match AND the right children match
        return (p->val == q->val)
            && isSameTree(p->left, q->left)
            && isSameTree(p->right, q->right);
    }
};

void deleteTree(TreeNode* root) {
    if (root == nullptr) return;
    deleteTree(root->left);
    deleteTree(root->right);
    delete root;
}

int main() {
    // Constructing Sample Tree P:
    //        1
    //       / \
    //      2   3
    TreeNode* p = new TreeNode(1);
    p->left = new TreeNode(2);
    p->right = new TreeNode(3);

    // Constructing Sample Tree Q (Identical to P):
    //        1
    //       / \
    //      2   3
    TreeNode* q = new TreeNode(1);
    q->left = new TreeNode(2);
    q->right = new TreeNode(3);

    Solution sol;
    bool result = sol.isSameTree(p, q);

    cout << "Are the trees identical: " << (result ? "True" : "False") << endl;

    // Expected Output:
    // Are the trees identical: True

    deleteTree(p);
    deleteTree(q);

    return 0;
}