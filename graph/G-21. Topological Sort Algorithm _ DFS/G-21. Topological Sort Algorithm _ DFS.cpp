/*
 * Problem: Topological Sort (DFS Approach)
 * ----------------------------------------
 * Approach: Depth-First Search with Stack Post-Processing
 * * Approach Explanation:
 * 1. Topological Sorting is a linear ordering of vertices for a Directed Acyclic Graph (DAG) 
 * such that for every directed edge u -> v, vertex u comes before v in the ordering.
 * 2. Why a Stack?
 * - In DFS, a node completes its execution (finishes visiting all reachable descendants) 
 * before returning.
 * - Pushing a node onto the stack AFTER its DFS call finishes guarantees that all its 
 * dependencies (children) are already deeper in the stack.
 * - Popping from the stack later naturally reverses this post-order, placing prerequisites first.
 * 3. Algorithm:
 * - Maintain a `vis` array initialized to 0.
 * - For each unvisited node `i` from 0 to V - 1, call `dfs(i, vis, st, adj)`.
 * - In `dfs`:
 * - Mark `node` as visited (`vis[node] = 1`).
 * - For each neighbor `it` of `node`, if not visited, recurse `dfs(it)`.
 * - Once all outgoing paths are exhausted, push `node` to `st`.
 * - Pop elements one-by-one from `st` into `ans` vector and return.
 * * Time Complexity:  O(V + E) - Visits every vertex once and checks each directed edge once.
 * Space Complexity: O(V)     - For `vis` array, recursion call stack, and explicitly maintained `st`.
 */

#include <iostream>
#include <vector>
#include <stack>

using namespace std;

class Solution {
private:
    void dfs(int node, int vis[], stack<int>& st, vector<int> adj[]) {
        vis[node] = 1;

        for (auto it : adj[node]) {
            if (!vis[it]) {
                dfs(it, vis, st, adj);
            }
        }

        // Push to stack after visiting all adjacent nodes
        st.push(node);
    }

public:
    // Function to return list containing vertices in Topological order.
    vector<int> topoSort(int V, vector<int> adj[]) {
        int vis[V] = {0};
        stack<int> st;

        // Traverse all components
        for (int i = 0; i < V; i++) {
            if (!vis[i]) {
                dfs(i, vis, st, adj);
            }
        }

        // Extract topological order from the stack
        vector<int> ans;
        while (!st.empty()) {
            ans.push_back(st.top());
            st.pop();
        }

        return ans;
    }
};

// 🔹 Driver Code
int main() {
    /*
        Directed Graph (DAG):
        1 -> 0
        2 -> 0
        3 -> 0
        
        A valid topological ordering must place 1, 2, and 3 before 0.
        Possible valid output: 3, 2, 1, 0
    */

    int V = 4;
    vector<int> adj[4];
    adj[1].push_back(0);
    adj[2].push_back(0);
    adj[3].push_back(0);

    Solution obj;
    vector<int> result = obj.topoSort(V, adj);

    cout << "Topological Sort Order:\n";
    for (int node : result) {
        cout << node << " ";
    }
    cout << endl;

    return 0;
}