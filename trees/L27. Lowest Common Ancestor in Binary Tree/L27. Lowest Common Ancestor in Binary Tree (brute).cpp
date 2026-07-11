// LeetCode 236: Lowest Common Ancestor of a Binary Tree (Path Comparison Approach)
// Time Complexity: O(N) -> Where N is the total number of nodes, as we find individual paths using two O(N) DFS sweeps and then match arrays
// Space Complexity: O(N) -> Due to storing the path sequences inside `path1` and `path2` vectors, alongside the recursion stack frames
// Approach: Find the path from the root to node `p` and root to node `q` using a backtracking pre-order DFS helper function.
// Once both paths are filled into vectors, traverse them concurrently. The last node value that is identical in both path arrays 
// before a divergence occurs is the Lowest Common Ancestor (LCA).

#include <iostream>
#include <vector>

using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

class Solution {
private:
    // Backtracking helper to discover and record the path sequence leading to a target node
    bool getPath(TreeNode* node, vector<TreeNode*> &arr, TreeNode* target) {
        if (!node) return false;

        arr.push_back(node); // Assume current node is part of the path

        if (node == target) return true;

        if (getPath(node->left, arr, target) || getPath(node->right, arr, target)) {
            return true;
        }

        // Backtrack: remove the current node if the target is not found in either subtree branch
        arr.pop_back();
        return false;
    }

public:
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        vector<TreeNode*> path1, path2;

        // Extract structural path sequences starting from root down to targets p and q
        if (!getPath(root, path1, p) || !getPath(root, path2, q)) {
            return nullptr;
        }

        TreeNode* lca = nullptr;
        int i = 0;

        // Iterate through both paths simultaneously until they diverge
        while (i < path1.size() && i < path2.size()) {
            if (path1[i] == path2[i]) {
                lca = path1[i]; // Track the common ancestor node mapping
                i++;
            } else {
                break; // Paths have diverged; stop the iteration sweep
            }
        }

        return lca;
    }
};

void deleteTree(TreeNode* root) {
    if (root == nullptr) return;
    deleteTree(root->left);
    deleteTree(root->right);
    delete root;
}

int main() {
    // Constructing the exact sample binary tree from your image:
    //            1
    //          /   \
    //         2     3
    //        / \   / \
    //       4   5 8   9
    //          / \
    //         6   7
    TreeNode* root = new TreeNode(1);
    root->left = new TreeNode(2);
    root->right = new TreeNode(3);
    root->left->left = new TreeNode(4);
    root->left->right = new TreeNode(5);
    root->right->left = new TreeNode(8);
    root->right->right = new TreeNode(9);
    root->left->right->left = new TreeNode(6);
    root->left->right->right = new TreeNode(7);

    TreeNode* p = root->left->left;          // Node 4
    TreeNode* q = root->left->right->right;   // Node 7

    Solution sol;
    TreeNode* result = sol.lowestCommonAncestor(root, p, q);

    if (result != nullptr) {
        cout << "LCA(" << p->val << ", " << q->val << ") = " << result->val << endl;
    }

    // Expected Output:
    // LCA(4, 7) = 2

    deleteTree(root);
    return 0;
}