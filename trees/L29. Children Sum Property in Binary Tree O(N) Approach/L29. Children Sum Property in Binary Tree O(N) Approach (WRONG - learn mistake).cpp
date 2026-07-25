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
/* Structure of a Tree Node
class Node {
public:
    int data;
    Node* left, *right;
    Node(int data) {
        data = data;
        left = right = nullptr;
    }
}; */


class Solution {
  public:
    
    bool isleaf(Node* node){
        if(node->left == NULL && node->right == NULL) return true;
        return false;
    }
    
    bool check(Node* node, int sum){
        if(sum != node->data) return false;
        return true;
    }
    
    int height(Node* node){
        if(!node) return 0;

        if(isleaf(node)) return node->data;
        
        int l = height(node->left);
        int r = height(node->right);

        // Propagate failure
        if(l == -1 || r == -1) return -1;
        
        if(check(node, l + r) == false) return -1;
        
        return l + r + node->data;
    }
  
  
    bool isSumProperty(Node *root) {
        if(!root || isleaf(root)) return true;

        return height(root) != -1;
    }
};

// Wrong Answer. !!!
// Ask Yogi Bot
// Possibly your code does not work correctly for multiple test-cases (TCs).

// The first test case where your code failed:

// Test Cases Passed: 
// 3 /1111
// For Input : 
// 4 4 N 4 N N N
// Your Code's output is: 
// False
// It's Correct output is: 
// True
// Output Difference: 
// FalseTrue



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