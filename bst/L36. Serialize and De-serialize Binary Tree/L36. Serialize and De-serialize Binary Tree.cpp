/*
 * Problem: Serialize and Deserialize Binary Tree (LeetCode 297)
 * -----------------------------------------------------------
 * Approach: Level Order Traversal (BFS) using stringstream
 * 
 * Approach Explanation:
 * 1. Serialization (Tree -> String):
 *    - Perform a standard BFS using a queue.
 *    - For every non-null node, append `val` + `,` to the string and push children to queue.
 *    - For every null pointer, append `#` + `,` (marker for null).
 * 
 * 2. Deserialization (String -> Tree):
 *    - Use `stringstream` and `getline(s, str, ',')` to read comma-separated tokens.
 *    - Create the root node from the first token and push to a queue.
 *    - Iterate through the queue. For each popped parent node:
 *        a. Read next token for Left child -> if not "#", create node & link as `left`.
 *        b. Read next token for Right child -> if not "#", create node & link as `right`.
 * 
 * Time Complexity:  O(N) for both operations.
 * Space Complexity: O(N) for both operations (Queue + String buffer).
 */

#include <iostream>
#include <string>
#include <queue>
#include <sstream>

using namespace std;

// Definition for a binary tree node.
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;

    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

class Codec {
public:
    // Approach: BFS Level-Order Traversal to record nodes and null markers ('#')
    string serialize(TreeNode* root) {
        if (!root) return "";

        string s = "";
        queue<TreeNode*> q;
        q.push(root);

        while (!q.empty()) {
            TreeNode* curNode = q.front();
            q.pop();

            if (curNode == nullptr) {
                s.append("#,");
            } else {
                s.append(to_string(curNode->val) + ",");
                q.push(curNode->left);
                q.push(curNode->right);
            }
        }

        return s;
    }

    // Approach: BFS Token Parsing using stringstream to reconstruct tree level by level
    TreeNode* deserialize(string data) {
        if (data.size() == 0) return nullptr;

        stringstream s(data);
        string str;

        // Fetch root value
        getline(s, str, ',');
        TreeNode* root = new TreeNode(stoi(str));

        queue<TreeNode*> q;
        q.push(root);

        while (!q.empty()) {
            TreeNode* node = q.front();
            q.pop();

            // Process Left Child
            getline(s, str, ',');
            if (str == "#") {
                node->left = nullptr;
            } else {
                TreeNode* leftNode = new TreeNode(stoi(str));
                node->left = leftNode;
                q.push(leftNode);
            }

            // Process Right Child
            getline(s, str, ',');
            if (str == "#") {
                node->right = nullptr;
            } else {
                TreeNode* rightNode = new TreeNode(stoi(str));
                node->right = rightNode;
                q.push(rightNode);
            }
        }

        return root;
    }
};

// 🔹 Driver Code
int main() {
    /*
            1
           / \
          2   3
             / \
            4   5
            
       Serialized string: "1,2,3,#,#,4,5,#,#,#,#,"
    */

    TreeNode* root = new TreeNode(1);
    root->left = new TreeNode(2);
    root->right = new TreeNode(3);
    root->right->left = new TreeNode(4);
    root->right->right = new TreeNode(5);

    Codec ser, deser;

    // 1. Serialize
    string serializedData = ser.serialize(root);
    cout << "Serialized Tree: " << serializedData << endl;

    // 2. Deserialize
    TreeNode* deserializedRoot = deser.deserialize(serializedData);

    // 3. Re-serialize to verify correctness
    string reSerializedData = ser.serialize(deserializedRoot);
    cout << "Re-serialized Tree: " << reSerializedData << endl;

    if (serializedData == reSerializedData) {
        cout << "\n✅ Serialization and Deserialization successful!" << endl;
    }

    return 0;
}