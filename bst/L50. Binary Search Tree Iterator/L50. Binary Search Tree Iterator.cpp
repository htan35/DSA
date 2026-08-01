/*
 * Problem: Binary Search Tree Iterator (LeetCode 173)
 * ----------------------------------------------------
 * Approach: Controlled Iterative Inorder Traversal using Stack
 * 
 * Approach Explanation:
 * 1. Constructor: Initialize stack with all nodes on the path from `root` to the leftmost leaf via `pushAll(root)`.
 * 2. next(): 
 *    - Pop the top node `temp` (guaranteed to be the next smallest value).
 *    - Process its right subtree by calling `pushAll(temp->right)`.
 *    - Return `temp->val`.
 * 3. hasNext(): Return `true` if the stack is not empty, `false` otherwise.
 * 
 * Time Complexity:
 *   - next():    Amortized O(1) - Each node is pushed and popped exactly once across all operations.
 *   - hasNext(): O(1)
 * 
 * Space Complexity:
 *   - O(H) Auxiliary Space - Stack holds at most H nodes (where H is tree height).
 */

#include <iostream>
#include <stack>

using namespace std;

// Definition for a binary tree node.
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

class BSTIterator {
private: 
    stack<TreeNode*> st;

    // Helper to push a node and all its left descendants
    void pushAll(TreeNode* node) {
        while (node != nullptr) {
            st.push(node);
            node = node->left;
        }
    }

public:
    BSTIterator(TreeNode* root) {
        pushAll(root);
    }
    
    int next() {
        TreeNode* temp = st.top();
        st.pop();
        pushAll(temp->right);
        return temp->val;
    }
    
    bool hasNext() {
        return !st.empty();
    }
};

// 🔹 Driver Code
int main() {
    /*
            7
           / \
          3   15
             /  \
            9    20
            
       Inorder Sequence: 3, 7, 9, 15, 20
    */

    TreeNode* root = new TreeNode(7);
    root->left = new TreeNode(3);
    root->right = new TreeNode(15);
    root->right->left = new TreeNode(9);
    root->right->right = new TreeNode(20);

    BSTIterator* iterator = new BSTIterator(root);

    cout << "BST Inorder Traversal via Iterator:\n";
    while (iterator->hasNext()) {
        cout << iterator->next() << " ";
    }
    cout << endl;

    delete iterator;
    return 0;
}