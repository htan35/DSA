#include <bits/stdc++.h>
using namespace std;

template <typename T>
class TreeNode
{
public:
    T data;
    TreeNode<T>* left;
    TreeNode<T>* right;

    TreeNode(T data)
    {
        this->data = data;
        left = NULL;
        right = NULL;
    }
};

void check(TreeNode<int>* node,
           vector<int>& ino,
           vector<int>& pre,
           vector<int>& post,
           stack<pair<TreeNode<int>*, int>>& st)
{
    if(node == NULL)
        return;

    st.push({node, 1});

    // Preorder
    if(st.top().second == 1)
    {
        pre.push_back(st.top().first->data);
        st.top().second++;
    }

    check(node->left, ino, pre, post, st);

    // Inorder
    if(st.top().second == 2)
    {
        ino.push_back(st.top().first->data);
        st.top().second++;
    }

    check(node->right, ino, pre, post, st);

    // Postorder
    if(st.top().second == 3)
    {
        post.push_back(st.top().first->data);
        st.pop();
    }
}

vector<vector<int>> getTreeTraversal(TreeNode<int>* root)
{
    vector<vector<int>> ans;
    vector<int> pre, ino, post;

    stack<pair<TreeNode<int>*, int>> st;

    check(root, ino, pre, post, st);

    ans.push_back(ino);
    ans.push_back(pre);
    ans.push_back(post);

    return ans;
}

int main()
{
    /*
            1
          /   \
         2     3
        / \   / \
       4   5 6   7
    */

    TreeNode<int>* root = new TreeNode<int>(1);

    root->left = new TreeNode<int>(2);
    root->right = new TreeNode<int>(3);

    root->left->left = new TreeNode<int>(4);
    root->left->right = new TreeNode<int>(5);

    root->right->left = new TreeNode<int>(6);
    root->right->right = new TreeNode<int>(7);

    vector<vector<int>> ans = getTreeTraversal(root);

    cout << "Inorder: ";
    for (int x : ans[0])
        cout << x << " ";
    cout << endl;

    cout << "Preorder: ";
    for (int x : ans[1])
        cout << x << " ";
    cout << endl;

    cout << "Postorder: ";
    for (int x : ans[2])
        cout << x << " ";
    cout << endl;

    return 0;
}