// LeetCode 104: Maximum Depth of Binary Tree (Iterative Level Order Traversal)
// Time Complexity: O(N) -> Where N is the total number of nodes in the binary tree, visiting each node exactly once
// Space Complexity: O(N) -> In the worst case (perfect binary tree), the queue holds up to N/2 leaf nodes at the last level
// Approach: Perform a Breadth-First Search (BFS) level by level using a queue. 
// For each level processed, increment a depth counter until the entire tree has been traversed.
// HEIGHT OF A TREE = NUMBER OF LEVELS = NUMBER OF ROWS IN LEVEL ORDER TRAVERSAL
// IF ONLY ROOT IS PRESENT, HEIGHT = 1

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
    int maxDepth(TreeNode* root) {

        if(root == NULL) return 0;
        
        vector<vector<int>> ans;
        queue<TreeNode*> q;

        if(root == NULL) return 0;

        q.push(root);

        while(!q.empty()){
            vector<int>level;
            int size = q.size();
            for(int i=0;i<size;i++){
                TreeNode *node = q.front();
                q.pop();

                if(node->left!=NULL) q.push(node->left);
                if(node->right!=NULL) q.push(node->right);

                level.push_back(node->val);

            }
            ans.push_back(level);
        }

        return ans.size(); // ans has levels and total levels is no of rows of ans, which is the depth of the tree
        
    }
};

void deleteTree(TreeNode* root) {
    if (root == nullptr) return;
    deleteTree(root->left);
    deleteTree(root->right);
    delete root;
}

int main() {
    // Constructing a sample binary tree:
    //        3
    //       / \
    //      9  20
    //        /  \
    //       15   7
    TreeNode* root = new TreeNode(3);
    root->left = new TreeNode(9);
    root->right = new TreeNode(20);
    root->right->left = new TreeNode(15);
    root->right->right = new TreeNode(7);

    Solution sol;
    int depth = sol.maxDepth(root);

    cout << "Maximum Depth of Binary Tree: " << depth << endl;

    // Expected Output:
    // Maximum Depth of Binary Tree: 3

    deleteTree(root);

    return 0;
}