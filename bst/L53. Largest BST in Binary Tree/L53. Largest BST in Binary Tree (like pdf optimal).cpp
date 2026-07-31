/*
 * Approach: Bottom-Up Post-Order Traversal (Striver's Node Metadata Format)
 * ------------------------------------------------------------------------
 * Metadata Order in Image: { size, maxNode, minNode }
 * 
 * 1. Base Case (Empty Tree):
 *    - Returns {0, INT_MIN, INT_MAX}.
 *    - Passing INT_MIN as maxNode and INT_MAX as minNode ensures any parent node 
 *      can easily satisfy: left.maxNode < root->val < right.minNode.
 * 
 * 2. Valid BST Check:
 *    - If left.maxNode < root->val && root->val < right.minNode:
 *      Size    = 1 + left.size + right.size
 *      maxNode = max(root->val, right.maxNode)
 *      minNode = min(root->val, left.minNode)
 * 
 * 3. Invalid BST Fallback:
 *    - Returns { max(left.size, right.size), INT_MAX, INT_MIN }
 *    - Setting maxNode to INT_MAX and minNode to INT_MIN invalidates any future parent.
 * 
 * Time Complexity:  O(N) - Every node is visited once.
 * Space Complexity: O(H) - Call stack depth equals tree height H.
 */

#include <iostream>
#include <climits>
#include <algorithm>

using namespace std;

struct Node {
    int data;
    Node *left, *right;

    Node(int x) {
        data = x;
        left = right = NULL;
    }
};

// Custom structure matching {size, maxNode, minNode}
struct NodeInfo {
    int size;
    int maxNode;
    int minNode;
};

class Solution {
private:
    NodeInfo solve(Node* root) {
        // Base case: null node returns {0, INT_MIN, INT_MAX}
        if (root == NULL) {
            return {0, INT_MIN, INT_MAX};
        }

        // Post-order traversal: process left and right subtrees first
        NodeInfo left = solve(root->left);
        NodeInfo right = solve(root->right);

        // Check if current node satisfies BST condition
        if (left.maxNode < root->data && root->data < right.minNode) {
            int currentSize = 1 + left.size + right.size;
            int currentMax = max(root->data, right.maxNode);
            int currentMin = min(root->data, left.minNode);

            return {currentSize, currentMax, currentMin};
        }

        // Invalid BST branch: propagate the largest size found so far and set invalid bounds
        return {max(left.size, right.size), INT_MAX, INT_MIN};
    }

public:
    int largestBst(Node *root) {
        return solve(root).size;
    }
};

int main() {
    /*
       Tree matching the screenshot layout:
                   20
                 /    \
               15      40
              /  \    /  \
            14   18  30   60
            /   /  \     /
          17   16  19   50
    */

    Node* root = new Node(20);

    root->left = new Node(15);
    root->right = new Node(40);

    root->left->left = new Node(14);
    root->left->right = new Node(18);
    root->left->left->left = new Node(17);
    root->left->right->left = new Node(16);
    root->left->right->right = new Node(19);

    root->right->left = new Node(30);
    root->right->right = new Node(60);
    root->right->right->left = new Node(50);

    Solution obj;
    cout << "Largest BST Size = " << obj.largestBst(root) << endl;

    return 0;
}