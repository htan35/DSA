/*
 * Approach: Backtracking DFS Traversal
 * -----------------------------------
 * 1. Maintain a running path vector (`temp`) and a master answer vector (`ans`).
 * 2. At each node:
 *    - Push `node->data` into `temp`.
 *    - If the current node is a leaf (`left == NULL && right == NULL`), push `temp` to `ans`,
 *      pop `temp.pop_back()`, and return to avoid redundant recursion.
 *    - Recursively visit `left` child (if non-null).
 *    - Recursively visit `right` child (if non-null).
 *    - Backtrack by popping the current node (`temp.pop_back()`) before returning to the parent call.
 * 
 * Time Complexity:  O(N) - Every node in the binary tree is visited exactly once.
 * Space Complexity: O(H) - Recursion stack and path storage take O(H) space, where H is the height of the tree (O(N) worst case, O(log N) for balanced trees).
 */

#include <iostream>
#include <vector>

using namespace std;

// Definition for Node
class Node {
public:
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
    bool isleaf(Node *node) {
        if (node->left == NULL && node->right == NULL) return true;
        return false;
    }

    void path(Node* node, vector<int> &temp, vector<vector<int>> &ans) {
        if (node == NULL) {
            return;
        }

        temp.push_back(node->data);

        if (isleaf(node)) {
            ans.push_back(temp);
            temp.pop_back();
            return;
        }

        if (node->left != NULL) {
            path(node->left, temp, ans);
        }

        if (node->right != NULL) {
            path(node->right, temp, ans);
        }

        temp.pop_back();
        return;
    }

    vector<vector<int>> paths(Node* root) {
        vector<vector<int>> ans;
        vector<int> temp;

        if (root == NULL) {
            return ans;
        }

        path(root, temp, ans);
        return ans;
    }
};

int main() {
    /*
             10
           /    \
          20    30
         /  \
        40  60

       Paths:
       [10, 20, 40]
       [10, 20, 60]
       [10, 30]
    */

    Node* root = new Node(10);
    root->left = new Node(20);
    root->right = new Node(30);
    root->left->left = new Node(40);
    root->left->right = new Node(60);

    Solution obj;
    vector<vector<int>> result = obj.paths(root);

    cout << "All Root-to-Leaf Paths:" << endl;
    for (const auto& p : result) {
        cout << "[ ";
        for (int val : p) {
            cout << val << " ";
        }
        cout << "]" << endl;
    }

    return 0;
}