#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

// Tree Node
struct Node {
    int data;
    Node* left;
    Node* right;

    Node(int val) {
        data = val;
        left = right = NULL;
    }
};

// Solution Class
class Solution {
  public:
  
    void floor(Node* root , int key, int& maxi){
        if(root == NULL) return;

        if(key < root->data){
            floor(root->left, key, maxi);
        }
        else {
            // possible floor
            maxi = max(root->data, maxi);
            floor(root->right, key, maxi);
        }
    }
    
    int floorinBST(Node* root, int key) {
        int maxi = -1;
        floor(root, key, maxi);
        return maxi;
    }
};

// Helper: Insert into BST
Node* insert(Node* root, int val) {
    if(root == NULL) return new Node(val);

    if(val < root->data)
        root->left = insert(root->left, val);
    else
        root->right = insert(root->right, val);

    return root;
}

// Driver Code
int main() {
    /*
            40
           /  \
         20    60
        / \    / \
      10  30  50  70
    */

    Node* root = NULL;
    vector<int> values = {40, 20, 60, 10, 30, 50, 70};

    for(int x : values)
        root = insert(root, x);

    Solution obj;

    int key;
    cout << "Enter key: ";
    cin >> key;

    int ans = obj.floorinBST(root, key);

    cout << "Floor of " << key << " is: " << ans << endl;

    return 0;
}