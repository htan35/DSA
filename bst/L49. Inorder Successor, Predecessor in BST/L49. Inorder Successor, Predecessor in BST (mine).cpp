/*
 * Approach: Inorder Traversal Vector Storage
 * -----------------------------------------
 * 1. Perform an inorder traversal to store BST nodes in a sorted `vector<Node*>`.
 * 2. Find Predecessor:
 *    - Advance index `pre` until `ino[pre]->data >= key`.
 *    - If `pre == 0`, no element is strictly smaller than key, so predecessor is NULL.
 *    - Otherwise, predecessor is `ino[pre - 1]`.
 * 3. Find Successor:
 *    - Decrement index `suc` until `ino[suc]->data <= key`.
 *    - If `suc == n - 1`, no element is strictly larger than key, so successor is NULL.
 *    - Otherwise, successor is `ino[suc + 1]`.
 * 
 * Time Complexity:  O(N) - O(N) for inorder traversal + O(N) linear search in vector.
 * Space Complexity: O(N) - Extra vector storing all N node pointers + recursion stack.
 */

#include <iostream>
#include <vector>
#include <string>

using namespace std;

// Definition for a Binary Search Tree Node
class Node {
public:
    int data;
    Node *left;
    Node *right;

    Node(int x) {
        data = x;
        left = NULL;
        right = NULL;
    }
};

class Solution {
public:
    void inorder(Node* node, vector<Node*> &ino) {
        if (node == NULL) return;
        
        inorder(node->left, ino);
        ino.push_back(node);
        inorder(node->right, ino);
    }

    vector<Node*> findPreSuc(Node* root, int key) {
        vector<Node*> presuc;
        if (root == NULL) return presuc;

        vector<Node*> ino;
        inorder(root, ino);

        // Predecessor: largest value strictly less than key
        int pre = 0;
        while (pre < ino.size() && key > ino[pre]->data)
            pre++;

        // Test case inorder sequence: 1, 3, 4, 8, 9, 10 (key = 1)
        // if condition : `pre` stops at index of 1, so predecessor is element just before it => NULL.
        // else condition : key = 8, `pre` stops at index of 8, so predecessor is element just after it => 4.
        if (pre == 0)
            presuc.push_back(NULL);
        else
            presuc.push_back(ino[pre - 1]);

        // Successor: smallest value strictly greater than key
        int suc = ino.size() - 1;
        while (suc >= 0 && key < ino[suc]->data)
            suc--;

        // Test case inorder sequence: 1, 3, 4, 8, 9, 10 (key = 10)
        // if condition : `suc` stops at index of 10, so successor is element just after it => NULL.
        //  else condition: key = 8, `suc` stops at index of 8, so successor is element just after it => 9.
        if (suc == ino.size() - 1)
            presuc.push_back(NULL);
        else
            presuc.push_back(ino[suc + 1]);

        return presuc;
    }
};

int main() {
    /*
             8
           /   \
          1     9
           \     \
            4    10
           /
          3
    */

    Node* root = new Node(8);
    root->left = new Node(1);
    root->right = new Node(9);
    root->left->right = new Node(4);
    root->left->right->left = new Node(3);
    root->right->right = new Node(10);

    int key = 8;

    Solution obj;
    vector<Node*> result = obj.findPreSuc(root, key);

    cout << "Key: " << key << endl;
    cout << "Predecessor: " << (result[0] ? to_string(result[0]->data) : "NULL") << endl;
    cout << "Successor:   " << (result[1] ? to_string(result[1]->data) : "NULL") << endl;

    return 0;
}