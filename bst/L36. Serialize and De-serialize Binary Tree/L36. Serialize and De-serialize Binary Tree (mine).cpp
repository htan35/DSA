#include <iostream>
#include <queue>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>

using namespace std;

/**
 * Definition for a binary tree node.
 */
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Codec {
public:

    // Encodes a tree to a single string.
    string serialize(TreeNode* root) {
        queue<pair<TreeNode* , int>> q;
        // map<TreeNode*, int> mpp;
        vector<pair<TreeNode*, int>> v;
        string ans;
        if(root == NULL) return ans;

        q.push({root, 0});

        // doing it in level is unnecessary
        // while(!q.empty()){
        //     int size = q.size();
        //     TreeNode* node = q.front().first;
        //     int idx = q.front().second;
        //     v.push_back({node,idx});
        //     q.pop();

        //     for(int i=0; i<size;i++){
        //         if(node->left != NULL) q.push({node->left, 2*(idx)+1});
        //         if(node->right != NULL) q.push({node->right, 2*(idx)+2});
        //     }

        // }

        while (!q.empty()) {
            TreeNode* node = q.front().first;
            int idx = q.front().second;
            q.pop();

            v.push_back({node, idx});

            if (node->left)
                q.push({node->left, 2 * idx + 1});

            if (node->right)
                q.push({node->right, 2 * idx + 2});
        }

        sort(v.begin(), v.end(),
            [](const pair<TreeNode*, int>& a, const pair<TreeNode*, int>& b) {
                return a.second < b.second; 
            });
        
        int j = 0;

        for (int i = 0; i <= v.back().second; i++) {
            if (j < v.size() && v[j].second == i) {
                ans += to_string(v[j].first->val);
                j++;
            } else {
                ans += "NULL";
            }
            ans += ",";
        }

        return ans;

    }

    // Decodes your encoded data to tree.
    TreeNode* deserialize(string data) {

        if (data.empty())
            return NULL;

        // Split the string
        stringstream ss(data);
        vector<string> arr;
        string temp;

        while (getline(ss, temp, ',')) {
            if (!temp.empty())
                arr.push_back(temp);
        }

        if (arr.empty() || arr[0] == "NULL")
            return NULL;

        // Create a TreeNode* array
        vector<TreeNode*> nodes(arr.size(), NULL);

        // Create all nodes
        for (int i = 0; i < arr.size(); i++) {
            if (arr[i] != "NULL") {
                nodes[i] = new TreeNode(stoi(arr[i]));
            }
        }

        // Connect children
        for (int i = 0; i < arr.size(); i++) {

            if (nodes[i] == NULL)
                continue;

            int left = 2 * i + 1;
            int right = 2 * i + 2;

            if (left < arr.size())
                nodes[i]->left = nodes[left];

            if (right < arr.size())
                nodes[i]->right = nodes[right];
        }

        return nodes[0];
    }
};

// ---------- DRIVER CODE ----------

// Helper: Print inorder (to verify)
void inorder(TreeNode* root) {
    if (!root) return;
    inorder(root->left);
    cout << root->val << " ";
    inorder(root->right);
}

// Helper: Build sample tree
TreeNode* buildSampleTree() {
    /*
            1
           / \
          2   3
             / \
            4   5
    */
    TreeNode* root = new TreeNode(1);
    root->left = new TreeNode(2);
    root->right = new TreeNode(3);
    root->right->left = new TreeNode(4);
    root->right->right = new TreeNode(5);

    return root;
}

int main() {

    Codec ser, deser;

    TreeNode* root = buildSampleTree();

    cout << "Original Tree Inorder: ";
    inorder(root);
    cout << endl;

    // Serialize
    string data = ser.serialize(root);
    cout << "Serialized: " << data << endl;

    // Deserialize
    TreeNode* newRoot = deser.deserialize(data);

    cout << "Deserialized Tree Inorder: ";
    inorder(newRoot);
    cout << endl;

    return 0;
}