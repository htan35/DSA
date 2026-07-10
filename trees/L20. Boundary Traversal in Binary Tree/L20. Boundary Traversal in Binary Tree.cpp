// LeetCode 545: Boundary of Binary Tree
// Time Complexity: O(N) -> Where N is the total number of nodes in the binary tree. Left/Right boundaries take O(H), and leaf collection visits every node once O(N).
// Space Complexity: O(N) -> Due to the temporary storage vector `tmp` for the right boundary and recursion stack frames for leaf collection.
// Approach: The boundary traversal is broken down into three distinct steps executed in clockwise order:
// 1. Add the root node if it is not a leaf node.
// 2. Traverse the left boundary (excluding leaf nodes) by favoring the left child, dropping to the right child only if the left is missing.
// 3. Perform a standard preorder/inorder DFS to gather all the leaf nodes from left to right.
// 4. Traverse the right boundary (excluding leaf nodes) similarly to the left boundary, collect elements into a temporary container, and append them in reverse order.

#include <iostream>
#include <vector>

using namespace std;

struct Node {
    int data;
    Node *left;
    Node *right;

    Node(int x) : data(x), left(nullptr), right(nullptr) {}
};

class Solution {
private:
    bool isLeaf(Node* node) {
        return node->left == nullptr && node->right == nullptr;
    }

    // Recursively add left boundary (top-down)
    void addLeftBoundary(Node* node, vector<int>& res) {
        // Stop at null or leaf nodes to avoid duplicates in the boundary.
        if (!node || isLeaf(node))
            return;

        res.push_back(node->data);

        if (node->left)
            addLeftBoundary(node->left, res);
        else
            addLeftBoundary(node->right, res);
    }

    // Recursively add all leaf nodes
    void addLeaves(Node* node, vector<int>& res) {
        if (!node)
            return;

        if (isLeaf(node)) {
            res.push_back(node->data);
            return;
        }

        addLeaves(node->left, res);
        addLeaves(node->right, res);
    }

    // Recursively add right boundary (bottom-up)
    void addRightBoundary(Node* node, vector<int>& res) {
        // Stop at null or leaf nodes to avoid duplicates in the boundary.
        if (!node || isLeaf(node))
            return;

        if (node->right)
            addRightBoundary(node->right, res);
        else
            addRightBoundary(node->left, res);

        // Push while returning from recursion
        res.push_back(node->data);
    }

public:
    vector<int> printBoundary(Node* root) {
        vector<int> res;

        if (!root)
            return res;

        // Add the root only if it is not a leaf.
        // Example:
        //      1
        // Here, the root is also a leaf (single-node tree).
        // If we add the root here and later call addLeaves(),
        // the root gets added again, resulting in {1, 1}.
        // This check prevents that duplicate.
        if (!isLeaf(root))
            res.push_back(root->data);

        // Left Boundary
        addLeftBoundary(root->left, res);

        // Leaf Nodes
        addLeaves(root, res);

        // Right Boundary
        addRightBoundary(root->right, res);

        return res;
    }
};

// Utility function to delete tree
void deleteTree(Node* root) {
    if (!root)
        return;

    deleteTree(root->left);
    deleteTree(root->right);
    delete root;
}

int main() {

    //            1
    //          /   \
    //         2     7
    //        /       \
    //       3         8
    //        \       /
    //         4     9
    //        / \   / \
    //       5   6 10 11

    Node* root = new Node(1);

    root->left = new Node(2);
    root->right = new Node(7);

    root->left->left = new Node(3);
    root->left->left->right = new Node(4);

    root->left->left->right->left = new Node(5);
    root->left->left->right->right = new Node(6);

    root->right->right = new Node(8);
    root->right->right->left = new Node(9);

    root->right->right->left->left = new Node(10);
    root->right->right->left->right = new Node(11);

    Solution sol;

    vector<int> ans = sol.printBoundary(root);

    cout << "Boundary Traversal: ";

    for (int x : ans)
        cout << x << " ";

    cout << endl;

    // Expected:
    // 1 2 3 5 6 10 11 8 7

    deleteTree(root);

    return 0;
}