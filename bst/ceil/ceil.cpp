/*
 * Problem: Ceil in a Binary Search Tree (BST)
 * -------------------------------------------
 * Ceil of X is the smallest node value in the BST that is >= X.
 * 
 * Time Complexity:  O(H) - where H is the height of the BST.
 * Space Complexity:
 *   - Recursive: O(H) call stack depth.
 *   - Iterative: O(1) auxiliary space.
 */

#include <iostream>
using namespace std;

struct Node {
    int data;
    Node *left, *right;

    Node(int val) {
        data = val;
        left = right = nullptr;
    }
};

class Solution {
public:
    // Approach 1: Recursive - O(H) Space
    int findCeilRecursive(Node* root, int x) {
        if (root == nullptr) return -1;

        // Exact match found
        if (root->data == x) return root->data;

        // Root is smaller than x, so search in the right subtree
        if (root->data < x) {
            return findCeilRecursive(root->right, x);
        }

        // Root is greater than x, current node is a potential candidate
        int leftAns = findCeilRecursive(root->left, x);

        // If left subtree provided a valid ceil, return it; otherwise, current root is the ceil
        if (leftAns >= x && leftAns != -1) {
            return leftAns;
        }

        return root->data;
    }

    // Approach 2: Iterative - O(1) Auxiliary Space (Optimal)
    int findCeilIterative(Node* root, int x) {
        int ceil = -1;

        while (root != nullptr) {
            if (root->data == x) {
                return x; // Exact match found
            }

            if (root->data < x) {
                root = root->right; // Node too small, look right
            } else {
                ceil = root->data;  // Potential ceil candidate
                root = root->left;  // Look left for a smaller valid value
            }
        }

        return ceil;
    }
};

// 🔹 Driver Code
int main() {
    /*
               10
              /  \
             5    15
            / \
           2   8
              /
             6
    */

    Node* root = new Node(10);
    root->left = new Node(5);
    root->right = new Node(15);
    root->left->left = new Node(2);
    root->left->right = new Node(8);
    root->left->right->left = new Node(6);

    Solution obj;
    int key = 7;

    cout << "Ceil of " << key << " (Recursive): " << obj.findCeilRecursive(root, key) << endl;
    cout << "Ceil of " << key << " (Iterative): " << obj.findCeilIterative(root, key) << endl;

    return 0;
}