/*
 * Problem: Populating Next Right Pointers in Each Node (LeetCode 116)
 * ------------------------------------------------------------------
 * Approach: Iterative Pointer Wire-Up using Existing `next` Pointers
 * 
 * Approach Explanation:
 * 1. Start at the root (`curr`).
 * 2. Outer loop runs while `curr->left` exists (since it's a perfect binary tree, 
 *    having a left child means the current level can establish links for the next level).
 * 3. Inner loop uses a temporary pointer `temp` to traverse horizontally along the current level:
 *    a. Wire `temp->left->next` to `temp->right`.
 *    b. If `temp->next` exists, wire `temp->right->next` to `temp->next->left` (crosses parent boundaries).
 *    c. Advance `temp` using `temp = temp->next`.
 * 4. Once the current level is fully connected, move `curr = curr->left` to drop to the next level.
 * 
 * Time Complexity:  O(N) - Every node/edge is processed exactly once.
 * Space Complexity: O(1) Auxiliary Space - Pointers are modified in-place without queue or stack.
 */

#include <iostream>
#include <queue>

using namespace std;

// Definition for a Node.
class Node {
public:
    int val;
    Node* left;
    Node* right;
    Node* next;

    Node() : val(0), left(NULL), right(NULL), next(NULL) {}

    Node(int _val) : val(_val), left(NULL), right(NULL), next(NULL) {}

    Node(int _val, Node* _left, Node* _right, Node* _next)
        : val(_val), left(_left), right(_right), next(_next) {}
};

class Solution {
public:
    Node* connect(Node* root) {
        if (!root) return nullptr;

        Node* curr = root;

        // Traverse down level by level (stop at leaf level)
        while (curr->left) {
            Node* temp = curr;

            // Traverse horizontally across the current level using `next`
            while (temp) {
                // 1. Connect left child -> right child
                temp->left->next = temp->right;

                // 2. Connect right child -> adjacent left child (across subtrees)
                if (temp->next) {
                    temp->right->next = temp->next->left;
                }

                // Move horizontally across current level
                temp = temp->next;
            }

            // Move to the leftmost node of the next level
            curr = curr->left;
        }

        return root;
    }
};

// Helper function to print level order traversal using `next` pointers
void printLevelOrderNext(Node* root) {
    Node* levelStart = root;

    while (levelStart) {
        Node* curr = levelStart;
        while (curr) {
            cout << curr->val << " -> ";
            if (!curr->next) cout << "NULL  ";
            curr = curr->next;
        }
        cout << endl;
        levelStart = levelStart->left;
    }
}

// 🔹 Driver Code
int main() {
    /*
             1
           /   \
          2     3
         / \   / \
        4   5 6   7
    */

    Node* root = new Node(1);
    root->left = new Node(2);
    root->right = new Node(3);
    root->left->left = new Node(4);
    root->left->right = new Node(5);
    root->right->left = new Node(6);
    root->right->right = new Node(7);

    Solution sol;
    sol.connect(root);

    cout << "Level-by-level traversal using 'next' pointers:\n" << endl;
    printLevelOrderNext(root);

    return 0;
}