// GeeksforGeeks: Bottom View of Binary Tree
// Time Complexity: O(N log N) -> Where N is the total number of nodes in the binary tree, due to insertion/update operations in the sorted map
// Space Complexity: O(N) -> Due to the queue used for Breadth-First Search (BFS) and the map structure tracking unique vertical lines
// Approach: Perform a Level Order Traversal (BFS) using a coordinate system tracking the vertical line index (root starts at line 0).
// Maintain a sorted `map<int, int>` to track the node data for each line. Since BFS moves level-by-level from top to bottom, 
// unconditionally overwriting the value for a vertical line ensures that the map always preserves the last (bottom-most) node seen on that line.

#include <iostream>
#include <vector>
#include <queue>
#include <map>

using namespace std;

struct Node {
    int data;
    Node* left;
    Node* right;
    Node(int val) {
        data = val;
        left = right = nullptr;
    }
};

class Solution {
public:
    vector<int> bottomView(Node *root) {
        vector<int> ans;
        if(root == NULL) return ans;
        
        // Queue tracks the structural configuration: pair<current_node, vertical_line_index>
        queue<pair<Node*, int>> q;
        
        // Map automatically sorts unique vertical lines from left to right: map[vertical_line_index] = node_data
        map<int, int> mpp; 
        
        q.push({root, 0});
        
        while(!q.empty()){
            auto it = q.front();
            q.pop();
            
            Node *node = it.first;
            int line = it.second; // Current vertical line index representation
            
            // Overwriting Rule: Unconditionally update the map with the current node's data.
            // As BFS naturally processes the tree from top to bottom, the last node processed 
            // on any given vertical line is guaranteed to be the bottom-most visible node.
            mpp[line] = node->data;
            
            // Moving left shifts the vertical axis column line to the left (-1)
            if(node->left != NULL) q.push({node->left, line - 1});
            // Moving right shifts the vertical axis column line to the right (+1)
            if(node->right != NULL) q.push({node->right, line + 1});
        }
        
        // Extract elements sequentially from left to right out of our sorted line mappings
        for(auto it : mpp){
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
    //         20
    //       /    \
    //      8      22
    //    /   \     \
    //   5     3     25
    //        / \      
    //       10  14    
    Node* root = new Node(20);
    root->left = new Node(8);
    root->right = new Node(22);
    root->left->left = new Node(5);
    root->left->right = new Node(3);
    root->right->right = new Node(25);
    root->left->right->left = new Node(10);
    root->left->right->right = new Node(14);

    Solution sol;
    vector<int> result = sol.bottomView(root);

    cout << "Bottom View output:\n[ ";
    for (int val : result) {
        cout << val << " ";
    }
    cout << "]\n";

    // Expected Output:
    // [ 5 10 3 14 25 ]

    deleteTree(root);
    return 0;
}