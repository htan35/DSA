// LeetCode 701: Insert into a Binary Search Tree (Recursive Approach)
// Time Complexity: O(H) -> Where H is the height of the BST. In a balanced tree, this takes O(log N) time; in a worst-case skewed tree, it takes O(N) time.
// Space Complexity: O(H) -> Representing the recursion call stack depth.
// Approach: Utilize the fundamental structural sorting property of a Binary Search Tree (BST). 
// If the insertion value is smaller than the current node's value, we branch recursively down the left child.
// If it is larger, we branch down the right child. When we hit a empty leaf spot (`NULL`), we create and hook up the new node.

#include <iostream>

using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

class Solution {
public:
    TreeNode* insertIntoBST(TreeNode* root, int val) {
        // Base case: Once an empty insertion spot is found, instantiate the new TreeNode
        if (root == NULL) {
            return new TreeNode(val);
        }
        
        // BST Sorting Rule: If insertion value is smaller, branch down left
        if (root->val > val) {
            root->left = insertIntoBST(root->left, val);
        }
        // BST Sorting Rule: If insertion value is larger, branch down right
        else {
            root->right = insertIntoBST(root->right, val);
        }

        // Return the unchanged node pointer back to preserve structural connectivity links
        return root;
    }
};

void printInOrder(TreeNode* root) {
    if (root == nullptr) return;
    printInOrder(root->left);
    cout << root->val << " ";
    printInOrder(root->right);
}

void deleteTree(TreeNode* root) {
    if (root == nullptr) return;
    deleteTree(root->left);
    deleteTree(root->right);
    delete root;
}

int main() {
    // Constructing a standard Binary Search Tree (BST):
    //        4
    //       / \
    //      2   7
    //     / \
    //    1   3
    TreeNode* root = new TreeNode(4);
    root->left = new TreeNode(2);
    root->right = new TreeNode(7);
    root->left->left = new TreeNode(1);
    root->left->right = new TreeNode(3);

    Solution sol;
    int newValue = 5;
    root = sol.insertIntoBST(root, newValue);

    cout << "In-order traversal after inserting " << newValue << ":\n";
    printInOrder(root);
    cout << endl;

    // Expected Output (In-order traversal of a valid BST is always sorted):
    // 1 2 3 4 5 7 

    deleteTree(root);
    return 0;
}