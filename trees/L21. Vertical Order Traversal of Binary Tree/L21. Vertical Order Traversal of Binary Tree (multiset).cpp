// LeetCode 987: Vertical Order Traversal of a Binary Tree (Map of Maps with Multiset Approach)
// Time Complexity: O(N log N) -> Where N is the total number of nodes, dictated by insertions into the sorted maps and multisets
// Space Complexity: O(N) -> Used by the nested map data structure and the BFS queue to store node references
// Approach: Perform a Level Order Traversal (BFS) using a tracking coordinate system where x represents the column and y represents the row layer. 
// Store nodes inside a nested `map<int, map<int, multiset<int>>> nodes`. The outer map automatically orders columns from left to right. 
// The inner map handles vertical row depth levels from top to bottom. The `multiset` acts as a value container that handles overlapping coordinate values.

#include <iostream>
#include <vector>
#include <queue>
#include <map>
#include <set>

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
    vector<vector<int>> verticalTraversal(TreeNode* root) {
        // Structured storage: map[column][row] -> multiset of values sorted ascendingly
        map<int, map<int, multiset<int>>> nodes;
        
        // Queue stores: {current_node, {column_index (x), row_index (y)}}
        queue<pair<TreeNode*, pair<int, int>>> todo;
        
        if (root == nullptr) return {};
        todo.push({root, {0, 0}});

        while (!todo.empty()) {
            auto p = todo.front();
            todo.pop();
            
            TreeNode* node = p.first;
            int x = p.second.first;  // Column axis index
            int y = p.second.second; // Row axis index

            // Automatically handles key creation and inserts the node value sorted into the multiset container
            nodes[x][y].insert(node->val);

            // Left child decrements column index by 1 (left shift) and increments row level depth by 1
            if (node->left) {
                todo.push({node->left, {x - 1, y + 1}});
            }
            // Right child increments column index by 1 (right shift) and increments row level depth by 1
            if (node->right) {
                todo.push({node->right, {x + 1, y + 1}});
            }
        }

        // Flatten the sorted grid map structures out sequentially into the final nested vector matching output constraints
        vector<vector<int>> ans;
        for (auto p : nodes) {
            vector<int> col;
            for (auto q : p.second) {
                // Insert all elements from the multiset at the current (column, row) into the current column vector
                col.insert(col.end(), q.second.begin(), q.second.end());
            }
            ans.push_back(col);
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
    vector<vector<int>> result = sol.verticalTraversal(root);

    cout << "Vertical Traversal output:\n";
    for (const auto& col : result) {
        cout << "[ ";
        for (int val : col) {
            cout << val << " ";
        }
        cout << "]\n";
    }

    // Expected Output:
    // [ 9 ]
    // [ 3 15 ]
    // [ 20 ]
    // [ 7 ]

    deleteTree(root);
    return 0;
}