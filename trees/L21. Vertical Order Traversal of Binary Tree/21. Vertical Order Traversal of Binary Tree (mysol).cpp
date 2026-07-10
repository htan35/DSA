// LeetCode 987: Vertical Order Traversal of a Binary Tree
// Time Complexity: O(N log N) -> Where N is the total number of nodes, dictated by sorting the flattened 'temp' vector
// Space Complexity: O(N) -> To store the node configurations in the 'temp' vector and manage the BFS queue
// Approach: Traverse the tree using a Level Order Traversal (BFS) while tracking coordinates (row, col) for each node.
// Store every node configuration as {row, col, value} inside a list. Sort all collected elements: prioritising column order first, 
// then row level, and finally node values if both row and column overlap. Group elements with matching columns together for the final return matrix.
#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;

    TreeNode(int x) {
        val = x;
        left = right = nullptr;
    }
};

class Solution {
public:
    vector<vector<int>> verticalTraversal(TreeNode* root) {

        // make pair<int,int> first one to row second to column and then sort
        // if col same then row condition

        vector<vector<int>> temp;
        vector<vector<int>> ans;

        if(root == NULL) return {};

        queue<pair<TreeNode*, pair<int,int>>> q;

        q.push({root, {0, 0}});

        while(!q.empty()){

            TreeNode *node = q.front().first;
            int x = q.front().second.first;
            int y = q.front().second.second;

            q.pop();

            // Store every node as {row, col, value}
            temp.push_back({x, y, node->val});

            if(node->left != NULL)
                q.push({node->left, {x+1, y-1}});

            if(node->right != NULL)
                q.push({node->right, {x+1, y+1}});
        }

        // vector contains row,col,node->val
        // so first sort via col then via row then via value

        sort(temp.begin(), temp.end(), [](vector<int>& a, vector<int>& b){

            if(a[1] != b[1]) return a[1] < b[1]; // Compare column first

            if(a[0] != b[0]) return a[0] < b[0]; // Then compare row

            return a[2] < b[2];                  // Finally compare value
        });

        // After sorting, temp is arranged according to:
        // column -> row -> value
        //
        // But return type is vector<vector<int>>.
        // So now we need to club all nodes having the same column.
        //
        // Example:
        // temp = { {1,-1,9}, {0,0,3}, {2,0,15}, {1,1,20}, {2,2,7} }
        //
        // Answer should become:
        // [[9], [3,15], [20], [7]]

        int i = 0;

        while(i < temp.size()){

            // Stand on one column and remember it
            int current_column = temp[i][1];

            // Store all values belonging to this column
            vector<int> col_group;

            // Keep collecting values until column changes
            while(i < temp.size() && temp[i][1] == current_column){

                col_group.push_back(temp[i][2]);
                i++;
            }

            // Finished one column, push it into answer
            ans.push_back(col_group);
        }

        return ans;
    }
};

// Utility to delete tree
void deleteTree(TreeNode* root){
    if(root==nullptr) return;

    deleteTree(root->left);
    deleteTree(root->right);

    delete root;
}

int main(){

    // Example Tree
    //
    //          3
    //        /   \
    //       9     20
    //            /  \
    //           15   7

    TreeNode* root = new TreeNode(3);

    root->left = new TreeNode(9);

    root->right = new TreeNode(20);

    root->right->left = new TreeNode(15);
    root->right->right = new TreeNode(7);

    Solution obj;

    vector<vector<int>> ans = obj.verticalTraversal(root);

    cout << "Vertical Traversal:\n";

    for(auto &col : ans){

        cout << "[ ";

        for(int x : col)
            cout << x << " ";

        cout << "]\n";
    }

    deleteTree(root);

    return 0;
}