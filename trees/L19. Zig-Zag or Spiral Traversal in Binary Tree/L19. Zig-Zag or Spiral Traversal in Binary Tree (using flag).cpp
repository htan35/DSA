// LeetCode 103: Binary Tree Zigzag Level Order Traversal
// Time Complexity: O(N) -> Where N is the total number of nodes in the binary tree, as we visit each node exactly once and reverse level vectors of size bounded by N
// Space Complexity: O(N) -> Due to the queue data structure used for standard Breadth-First Search (BFS) and storing the output
// Approach: Perform a standard level-order traversal using a queue. Track the traversal direction of each level 
// using a boolean flag `flip`. For every alternate layer where `flip` is true, reverse the row's vector before appending it to the final result.

#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

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
    vector<vector<int>> zigzagLevelOrder(TreeNode* root) {
        vector<vector<int>> ans;
        if (root == nullptr) return ans;

        queue<TreeNode*> q;
        q.push(root);
        
        // Flag to toggle direction: false means Left-to-Right, true means Right-to-Left
        bool flip = false;

        while (!q.empty()) {
            int s = q.size(); // Capture current level's size before children injection
            vector<int> level;

            for (int i = 0; i < s; i++) {
                TreeNode* node = q.front();
                q.pop();

                level.push_back(node->val);

                if (node->left != nullptr) q.push(node->left);
                if (node->right != nullptr) q.push(node->right);
            }

            // If the direction flag is set, reverse the current horizontal level vector
            if (flip) {
                reverse(level.begin(), level.end());
            }
            
            // Toggle the direction flag for the next deep horizontal layer
            flip = !flip;
            ans.push_back(level);
        }
        return ans;
    }
};

void deleteTree(TreeNode* root) {
    if (root == nullptr) return;
    deleteTree(root->left);
    deleteTree(root->right);
    delete root;
}

int main() {
    // Constructing a sample binary tree:
    //        3
    //       / \
    //      9  20
    //        /  \
    //       15   7
    TreeNode* root = new TreeNode(3);
    root->left = new TreeNode(9);
    root->right = new TreeNode(20);
    root->right->left = new TreeNode(15);
    root->right->right = new TreeNode(7);

    Solution sol;
    vector<vector<int>> result = sol.zigzagLevelOrder(root);

    cout << "Zigzag Level Order Traversal output:\n";
    for (const auto& level : result) {
        cout << "[ ";
        for (int val : level) {
            cout << val << " ";
        }
        cout << "]\n";
    }

    // Expected Output:
    // [ 3 ]
    // [ 20 9 ]
    // [ 15 7 ]

    deleteTree(root);

    return 0;
}