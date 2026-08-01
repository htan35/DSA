/*
 * Problem: Populating Next Right Pointers in Each Node
 * --------------------------------------------------
 * Approach: Standard BFS / Level-Order Traversal (On-the-fly connection)
 * 
 * Approach Explanation:
 * 1. Perform a standard level-order BFS using a queue.
 * 2. Track the number of nodes at the current level using `size = q.size()`.
 * 3. Keep a `prev` pointer initialized to `nullptr` at the start of each level.
 * 4. For every popped node:
 *    a. If `prev` is not null, point `prev->next = curr`.
 *    b. Update `prev = curr`.
 *    c. Push non-null left and right children into the queue.
 * 5. At the end of the loop, the last node of each level naturally points to `nullptr`.
 * 
 * Time Complexity:  O(N) - Visits each node once.
 * Space Complexity: O(W) = O(N) - Where W is the maximum width of the tree (for the queue).
 */

#include <iostream>
#include <queue>

using namespace std;

class Node {
public:
    int val;
    Node* left;
    Node* right;
    Node* next;

    Node() : val(0), left(NULL), right(NULL), next(NULL) {}
    Node(int _val) : val(_val), left(NULL), right(NULL), next(NULL) {}
};

class Solution {
public:
    Node* connect(Node* root) {
        if (!root) return nullptr;

        queue<Node*> q;
        q.push(root);

        while (!q.empty()) {
            int size = q.size();
            Node* prev = nullptr;

            for (int i = 0; i < size; i++) {
                Node* curr = q.front();
                q.pop();

                // Wire previous node's next pointer to the current node
                if (prev != nullptr) {
                    prev->next = curr;
                }
                prev = curr;

                // Standard BFS child pushes
                if (curr->left) q.push(curr->left);
                if (curr->right) q.push(curr->right);
            }
            // The last node in the level automatically points to nullptr (default)
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
    // /*
    //          1
    //        /   \
    //       2     3
    //      / \   / \
    //     4   5 6   7
    // */

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