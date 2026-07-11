// GeeksforGeeks: Top View of Binary Tree
// Time Complexity: O(N log N) -> Where N is the total number of nodes in the binary tree, due to insertion operations in the sorted map
// Space Complexity: O(N) -> Due to the queue used for Breadth-First Search (BFS) and the map structure tracking unique vertical lines
// Approach: Perform a Level Order Traversal (BFS) using a coordinate system tracking the vertical line index (root starts at line 0).
// Maintain a sorted `map<int, int>` to record the very first node value discovered on each unique vertical line index.
// Because BFS processes layers from top to bottom, the first node encountered on any vertical line is guaranteed to be the topmost visible node.

#include <iostream>
#include <vector>
#include <queue>
#include <map>

using namespace std;

struct Node {
    int data;
    Node *left;
    Node *right;
    Node(int x) : data(x), left(nullptr), right(nullptr) {}
};

class Solution {
public:
    vector<int> topView(Node *root) {
        vector<int> ans;
        if (root == NULL) return ans;

        // Map automatically sorts unique vertical lines from left to right: map[vertical_line_index] = node_data
        map<int, int> mpp;
        
        // Queue tracks the structural configuration: pair<current_node, vertical_line_index>
        queue<pair<Node*, int>> q;
        q.push({root, 0});

        while (!q.empty()) {
            auto it = q.front();
            q.pop();

            Node* node = it.first;
            int line = it.second; // Current vertical line index representation

            // Visibility Check: Only insert the node if it's the very first time we see this vertical line index
            if (mpp.find(line) == mpp.end()) {
                mpp[line] = node->data;
            }

            // Moving left shifts the vertical axis column line to the left (-1)
            if (node->left != NULL) {
                q.push({node->left, line - 1});
            }
            // Moving right shifts the vertical axis column line to the right (+1)
            if (node->right != NULL) {
                q.push({node->right, line + 1});
            }
        }

        // Extract elements sequentially from left to right out of our sorted line mappings
        for (auto it : mpp) {
            ans.push_back(it.second);
        }
        return ans;
    }
};

void deleteTree(Node* root) {
    if (root == nullptr) return;
    deleteTree(root->left);
    deleteTree(root->right);
    delete root;
}

int main() {
    // Constructing a sample binary tree:
    //         1
    //       /   \
    //      2     3
    //       \     \
    //        4     6
    //         \
    //          5
    Node* root = new Node(1);
    root->left = new Node(2);
    root->right = new Node(3);
    root->left->right = new Node(4);
    root->left->right->right = new Node(5);
    root->right->right = new Node(6);

    Solution sol;
    vector<int> result = sol.topView(root);

    cout << "Top View output:\n[ ";
    for (int val : result) {
        cout << val << " ";
    }
    cout << "]\n";

    // Expected Output:
    // [ 2 1 3 6 ]

    deleteTree(root);
    return 0;
}