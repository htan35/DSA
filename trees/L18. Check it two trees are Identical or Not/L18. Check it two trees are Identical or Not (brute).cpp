// LeetCode 100: Same Tree (Level Order Serialization Approach)
// Time Complexity: O(N + M) -> Where N and M are the number of nodes in both trees respectively, visiting each node and its NULL pointers
// Space Complexity: O(N + M) -> Due to storing the structural serialization sequence in the `temp1` and `temp2` vectors, along with the BFS queues
// Approach: Serialize both trees independently using a level-order traversal (BFS) that explicitly tracks structural boundaries by pushing a placeholder character ('n') for NULL child references. 
// Finally, compare both serialization vectors; if their sizes match and every element aligns identically, the trees are structurally identical.

#include <iostream>
#include <vector>
#include <queue>

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
    // Helper helper function to capture structural alignment of tree1
    void tree1(TreeNode *node1, queue<TreeNode*> &q1, vector<char> &temp1){
        if(node1 == NULL) return;

        q1.push(node1);

        while(!q1.empty()){
            int size = q1.size();

            for(int i=0; i<size; i++){
                TreeNode *node = q1.front();
                q1.pop();

                // Explicitly record NULL pointers to distinguish structurally distinct paths that share matching node sequences
                if(node == NULL){
                    temp1.push_back('n');
                    continue;
                }

                temp1.push_back(node->val);

                // Push children unconditionally to retain exact structure in the serialization array
                q1.push(node->left);
                q1.push(node->right);
            }
        }
    }

    // Helper helper function to capture structural alignment of tree2
    void tree2(TreeNode *node2, queue<TreeNode*> &q2, vector<char> &temp2){
        if(node2 == NULL) return;

        q2.push(node2);

        while(!q2.empty()){
            int size = q2.size();

            for(int i=0; i<size; i++){
                TreeNode *node = q2.front();
                q2.pop();

                if(node == NULL){
                    temp2.push_back('n');
                    continue;
                }

                temp2.push_back(node->val);

                q2.push(node->left);
                q2.push(node->right);
            }
        }
    }

    bool isSameTree(TreeNode* p, TreeNode* q) {
        // Handle immediate fast-exit edge cases
        if(p == NULL && q == NULL) return true;
        if(p == NULL || q == NULL) return false;

        queue<TreeNode*> q1;
        queue<TreeNode*> q2;

        vector<char> temp1;
        vector<char> temp2;

        // Perform level-by-level flattening for both inputs
        tree1(p, q1, temp1);
        tree2(q, q2, temp2);

        if(temp1.size() != temp2.size()) return false;

        // Vector validation step to assert structural and value identity
        for(int i = 0; i < temp1.size(); i++){
            if(temp1[i] != temp2[i]){
                return false;
            }
        }

        return true;
    }
};

void deleteTree(TreeNode* root) {
    if (root == nullptr) return;
    deleteTree(root->left);
    deleteTree(root->right);
    delete root;
}

int main() {
    // Constructing Sample Tree P:
    //        1
    //       / \
    //      2   3
    TreeNode* p = new TreeNode(1);
    p->left = new TreeNode(2);
    p->right = new TreeNode(3);

    // Constructing Sample Tree Q (Identical to P):
    //        1
    //       / \
    //      2   3
    TreeNode* q = new TreeNode(1);
    q->left = new TreeNode(2);
    q->right = new TreeNode(3);

    Solution sol;
    bool result = sol.isSameTree(p, q);

    cout << "Are the trees identical: " << (result ? "True" : "False") << endl;

    // Expected Output:
    // Are the trees identical: True

    deleteTree(p);
    deleteTree(q);

    return 0;
}