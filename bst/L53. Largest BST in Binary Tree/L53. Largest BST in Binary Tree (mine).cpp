#include <iostream>
#include <climits>
using namespace std;

class Node {
public:
    int data;
    Node *left, *right;

    Node(int x) {
        data = x;
        left = right = NULL;
    }
};

class Solution {
public:

    void check(Node* root, int& maxi) {
        if (root == NULL) return;

        int lar = 0;
        isbst(root, INT_MIN, INT_MAX, lar);

        maxi = max(maxi, lar);

        check(root->left, maxi);
        check(root->right, maxi);
    }

    bool isbst(Node* root, int low, int high, int& lar) {
        if (root == NULL)
            return true;

        if (root->data <= low || root->data >= high) {
            lar = 0;
            return false;
        }

        lar++;

        return isbst(root->left, low, root->data, lar) &&
               isbst(root->right, root->data, high, lar);
    }

    int largestBst(Node *root) {
        int maxi = 0;
        check(root, maxi);
        return maxi;
    }
};

int main() {

    /*
               50
              /  \
            30    60
           / \    / \
          5  20  45  70
                     / \
                    65 80
    */

    Node* root = new Node(50);

    root->left = new Node(30);
    root->right = new Node(60);

    root->left->left = new Node(5);
    root->left->right = new Node(20);

    root->right->left = new Node(45);
    root->right->right = new Node(70);

    root->right->right->left = new Node(65);
    root->right->right->right = new Node(80);

    Solution obj;

    cout << "Largest BST Size = " << obj.largestBst(root) << endl;

    return 0;
}