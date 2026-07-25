/*
 * Approach: Level Order Traversal (BFS) with Index Normalization
 * -------------------------------------------------------------
 * 1. Perform a Level Order Traversal (BFS) using a queue to store pairs of {node, index}.
 * 2. Assign heap-like 0-based indices to nodes at each level:
 *    - Left child index  = 2 * parent_index + 1
 *    - Right child index = 2 * parent_index + 2
 * 3. To prevent integer overflow in deep/skewed trees, normalize indices at the start of each 
 *    level by subtracting the minimum index (`mini`) of that level (`cur = q.front().second - mini`).
 * 4. The width of each level is calculated as `(last_index - first_index + 1)`.
 * 5. Track and return the maximum width across all levels.
 * 
 * Time Complexity:  O(N) - Every node in the binary tree is visited exactly once.
 * Space Complexity: O(W) - O(N) in the worst-case, where W is the maximum width of the tree (maximum nodes stored in the queue at any level).
 */

#include <iostream>
#include <queue>
#include <algorithm>

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
    int widthOfBinaryTree(TreeNode* root) {
        if (!root) return 0;

        long long ans = 0;
        queue<pair<TreeNode*, unsigned long long>> q;
        q.push({root, 0});

        while (!q.empty()) {
            int sz = q.size();
            unsigned long long mini = q.front().second;
            unsigned long long first = 0, last = 0;

            for (int i = 0; i < sz; i++) {
                unsigned long long cur = q.front().second - mini;
                TreeNode* node = q.front().first;
                q.pop();

                if (i == 0) first = cur;
                if (i == sz - 1) last = cur;

                if (node->left)
                    q.push({node->left, 2 * cur + 1});

                if (node->right)
                    q.push({node->right, 2 * cur + 2});
            }

            ans = max(ans, (long long)(last - first + 1));
        }

        return (int)ans;
    }
};

int main() {
    /*
            1
           / \
          3   2
         /     \
        5       9
       /         \
      6           7

    Expected Maximum Width: 8 (Level 4: Node 6 to Node 7 including null spaces)
    */

    TreeNode* root = new TreeNode(1);
    root->left = new TreeNode(3);
    root->right = new TreeNode(2);

    root->left->left = new TreeNode(5);
    root->right->right = new TreeNode(9);

    root->left->left->left = new TreeNode(6);
    root->right->right->right = new TreeNode(7);

    Solution obj;
    cout << "Maximum Width of Binary Tree: " << obj.widthOfBinaryTree(root) << endl;

    return 0;
}