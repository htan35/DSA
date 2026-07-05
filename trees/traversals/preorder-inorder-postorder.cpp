#include <iostream>
#include <vector>

using namespace std;

// Definition for a binary tree node structure
struct Node {
    int data;
    Node* left;
    Node* right;
    
    Node(int val) {
        data = val;
        left = nullptr;
        right = nullptr;
    }
};

class Solution {
public:
    // 1. Pre-order Traversal (Root -> Left -> Right)
    // Time Complexity: O(N), Space Complexity: O(N)
    void preorder(Node* node) {
        // Base Condition
        if (node == nullptr) {
            return;
        }

        // Step 1: Process current root data
        cout << node->data << " ";

        // Step 2: Recurse on left child
        preorder(node->left);

        // Step 3: Recurse on right child
        preorder(node->right);
    }

    // 2. In-order Traversal (Left -> Root -> Right)
    // Time Complexity: O(N), Space Complexity: O(N)
    void inorder(Node* node) {
        // Base Condition
        if (node == nullptr) {
            return;
        }

        // Step 1: Recurse on left child
        inorder(node->left);

        // Step 2: Process current root data
        cout << node->data << " ";

        // Step 3: Recurse on right child
        inorder(node->right);
    }

    // 3. Post-order Traversal (Left -> Right -> Root)
    // Time Complexity: O(N), Space Complexity: O(N)
    void postorder(Node* node) {
        // Base Condition
        if (node == nullptr) {
            return;
        }

        // Step 1: Recurse on left child
        postorder(node->left);

        // Step 2: Recurse on right child
        postorder(node->right);

        // Step 3: Process current root data
        cout << node->data << " ";
    }
};

int main() {
    // Constructing a sample binary tree matching standard structures:
    //        1
    //       / \
    //      4   8
    //         / \
    //        9  10
    Node* root = new Node(1);
    root->left = new Node(4);
    root->right = new Node(8);
    root->right->left = new Node(9);
    root->right->right = new Node(10);

    Solution sol;
    
    // Test Pre-order
    cout << "Pre-order Traversal output:  ";
    sol.preorder(root);  // Expected Outputs: 1 4 8 9 10
    cout << "\n";

    // Test In-order
    cout << "In-order Traversal output:   ";
    sol.inorder(root);   // Expected Outputs: 4 1 9 8 10
    cout << "\n";

    // Test Post-order
    cout << "Post-order Traversal output: ";
    sol.postorder(root);  // Expected Outputs: 4 9 10 8 1
    cout << "\n";

    return 0;
}