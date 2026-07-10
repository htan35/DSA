// LeetCode 103: Binary Tree Zigzag Level Order Traversal (Post-Processing Reversal Approach)
// Time Complexity: O(N) -> Where N is the total number of nodes in the binary tree, as we visit each node once and swap odd level elements up to N/2 times total
// Space Complexity: O(N) -> Due to the queue used for standard Breadth-First Search (BFS) layer tracking
// Approach: Extract standard level-order vectors using a tracking queue. After gathering all layers into a 2D matrix,
// loop through the final matrix and manually reverse elements in-place for every odd index row (i % 2 == 1) using a two-pointer structural swap bounded by size/2.

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
    vector<vector<int>> zigzagLevelOrder(TreeNode* root) {
        vector<vector<int>> ans;
        if(root == NULL) return ans;
        
        queue<TreeNode*> q;
        q.push(root);

        // Phase 1: Collect standard sequential level-order layers
        while(!q.empty()){
            vector<int> level;
            int size = q.size();

            for(int i = 0; i < size; i++){
                TreeNode *node = q.front();
                q.pop();

                if(node->left != NULL) q.push(node->left);
                if(node->right != NULL) q.push(node->right);

                level.push_back(node->val);
            }
            ans.push_back(level);
        }

        // Phase 2: Manually invert tracking orientation on odd row matrices
        for(int i = 0; i < ans.size(); i++){
            if(i % 2 == 1){
                // Loop only up to half the row size (size/2); swapping beyond half reverts elements back to normal
                for(int j = 0; j < ans[i].size() / 2; j++){   
                    int n = ans[i].size();
                    int temp = ans[i][j];
                    ans[i][j] = ans[i][n - j - 1];
                    ans[i][n - j - 1] = temp;
                }
            }
        }
        
        return ans;
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
    vector<vector<int>> result = sol.zigzagLevelOrder(root);

    cout << "Zigzag Level Order Traversal output:\n";
    for (const auto& level : result) {
        cout << "[ ";
        for (int val : level) {
            cout << val << " ";
        }
        cout << "]\n";
    }

    // Expected Output:
    // [ 3 ]
    // [ 20 9 ]
    // [ 15 7 ]

    deleteTree(root);

    return 0;
}