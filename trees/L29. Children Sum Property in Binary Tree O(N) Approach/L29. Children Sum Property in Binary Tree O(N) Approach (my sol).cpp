/*
 * Approach: Bottom-Up Recursive Checking (Children Sum Property)
 * -------------------------------------------------------------
 * 1. A binary tree satisfies the Children Sum Property if for every non-leaf node, 
 *    `node->data` equals the sum of the values of its immediate left and right children.
 * 2. Base Cases:
 *    - Empty tree (`NULL`) or leaf nodes (`left == NULL && right == NULL`) trivially satisfy the property.
 * 3. Helper Function `check(node)`:
 *    - Safely computes the values of existing immediate children (`l` and `r`).
 *    - Returns `true` if `node->data == l + r`, otherwise `false`.
 * 4. Helper Function `height(node)`:
 *    - Validates the current node using `check(node)`.
 *    - Recursively ensures both left and right subtrees satisfy the property.
 * 
 * Time Complexity:  O(N) - Every node in the tree is processed once.
 * Space Complexity: O(H) - O(N) in worst-case (skewed tree) or O(log N) in a balanced tree due to recursion call stack.
 */

#include <iostream>
using namespace std;

// Definition for Binary Tree Node
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
    
    bool isleaf(Node* node) {
        return (node->left == NULL && node->right == NULL);
    }
    
    bool check(Node* node) {
        int l = 0, r = 0;
        
        if (node->left != NULL)
            l = node->left->data;
            
        if (node->right != NULL)
            r = node->right->data;
            
        return (node->data == l + r);
    }
    
    bool height(Node* node) {
        if (node == NULL || isleaf(node))
            return true;
            
        if (check(node) == false)
            return false;
            
        return height(node->left) && height(node->right);
    }
  
    bool isSumProperty(Node *root) {
        return height(root);
    }
};

int main() {
    /*
            10
           /  \
          4    6
         / \    \
        1   3    6

    Expected Output: 1 (True - Children Sum Property holds for all non-leaf nodes)
    */

    Node* root = new Node(10);
    root->left = new Node(4);
    root->right = new Node(6);

    root->left->left = new Node(1);
    root->left->right = new Node(3);

    root->right->right = new Node(6);

    Solution obj;
    bool ans = obj.isSumProperty(root);

    if (ans) {
        cout << "The tree satisfies the Children Sum Property (1)" << endl;
    } else {
        cout << "The tree DOES NOT satisfy the Children Sum Property (0)" << endl;
    }

    return 0;
}