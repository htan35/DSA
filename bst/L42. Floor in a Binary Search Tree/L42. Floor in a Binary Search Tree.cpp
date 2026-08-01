/*
 * Problem: Floor in a Binary Search Tree (BST)
 * --------------------------------------------
 * Approach 1: Recursive BST Traversal
 * Approach 2: Iterative Traversal (Optimal - O(1) Auxiliary Space)
 * 
 * Logic:
 * - Initialize `floorVal = -1`.
 * - While traversing:
 *   - If node->data == key, floor is found (exact match). Return immediately.
 *   - If key > node->data, node->data is a candidate for floor. 
 *     Store it and move to node->right to search for a larger valid candidate.
 *   - If key < node->data, node->data is too big. Move to node->left.
 * 
 * Time Complexity:  O(H) - where H is the height of the BST (O(log N) for balanced, O(N) for skewed).
 * Space Complexity: 
 *   - Recursive: O(H) call stack depth.
 *   - Iterative: O(1) auxiliary space.
 */

#include <iostream>
#include <algorithm>

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
private:
    // Helper function for recursive approach
    void findFloorRecursive(Node* root, int key, int& floorVal) {
        if (!root) return;

        if (root->data == key) {
            floorVal = root->data;
            return;
        }

        if (key > root->data) {
            floorVal = root->data; // Candidate floor found
            findFloorRecursive(root->right, key, floorVal); // Look for a closer/larger valid candidate
        } else {
            findFloorRecursive(root->left, key, floorVal);  // Current value too large, search left
        }
    }

public:
    // Approach 1: Recursive
    int floorRecursive(Node* root, int key) {
        int floorVal = -1;
        findFloorRecursive(root, key, floorVal);
        return floorVal;
    }

    // Approach 2: Iterative (Preferred for O(1) space)
    int floorIterative(Node* root, int key) {
        int floorVal = -1;

        while (root != nullptr) {
            if (root->data == key) {
                return root->data;
            }

            if (key > root->data) {
                floorVal = root->data; // Store potential floor candidate
                root = root->right;    // Move right to see if a larger <= key value exists
            } else {
                root = root->left;     // Move left as current node is > key
            }
        }

        return floorVal;
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

    cout << "Floor of " << key << " (Recursive): " << obj.floorRecursive(root, key) << endl;
    cout << "Floor of " << key << " (Iterative): " << obj.floorIterative(root, key) << endl;

    return 0;
}