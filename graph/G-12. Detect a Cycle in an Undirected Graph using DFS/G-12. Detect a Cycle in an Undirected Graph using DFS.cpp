/*
 * Problem: Detect Cycle in an Undirected Graph using DFS
 * ------------------------------------------------------
 * Approach: Depth-First Search (DFS) with Parent Tracking
 * 
 * Approach Explanation:
 * 1. An undirected graph contains a cycle if, during a DFS traversal, we encounter 
 *    an adjacent node that is already visited and is NOT the parent of the current node.
 * 2. `dfs(node, parent, vis, adj)`:
 *    - Mark `vis[node] = 1`.
 *    - For every `adjacentNode` of `node`:
 *        a. If `!vis[adjacentNode]`: 
 *           Recursively call `dfs(adjacentNode, node, vis, adj)`. 
 *           If it returns true, propagate `true` up the call stack immediately.
 *        b. Else if `adjacentNode != parent`:
 *           The neighbor has been visited earlier from a different path -> a cycle exists, return true.
 *    - If all neighbors are explored without finding a back-edge, return false.
 * 3. `isCycle(V, adj)`:
 *    - Maintain a visited array `vis` of size V initialized to 0.
 *    - Iterate from `0` to `V - 1` to handle disconnected components:
 *        If `!vis[i]`, launch `dfs(i, -1, vis, adj)`.
 *        If any component reports a cycle, return true.
 *    - If all components finish without a cycle, return false.
 * 
 * Time Complexity:  O(V + 2E) - Every vertex is visited once and each undirected edge is checked twice.
 * Space Complexity: O(V) - For the visited array and the recursion call stack (worst-case skewed graph).
 */

#include <iostream>
#include <vector>

using namespace std;

class Solution {
private:
    bool dfs(int node, int parent, vector<int>& vis, vector<int> adj[]) {
        vis[node] = 1;

        for (auto adjacentNode : adj[node]) {
            if (!vis[adjacentNode]) {
                if (dfs(adjacentNode, node, vis, adj) == true) {
                    return true;
                }
            } 
            else if (adjacentNode != parent) {
                // Node is visited and is not the parent -> cycle found
                return true;
            }
        }

        return false;
    }

public:
    // Function to detect cycle in an undirected graph.
    bool isCycle(int V, vector<int> adj[]) {
        vector<int> vis(V, 0);

        // Check each connected component
        for (int i = 0; i < V; i++) {
            if (!vis[i]) {
                if (dfs(i, -1, vis, adj) == true) {
                    return true;
                }
            }
        }

        return false;
    }
};

// 🔹 Driver Code
int main() {
    /*
        Graph:
        0 --- 1
        |     |
        3 --- 2 --- 4

        Cycle present: 0-1-2-3-0
    */

    int V = 5;
    vector<int> adj[V];

    adj[0] = {1, 3};
    adj[1] = {0, 2};
    adj[2] = {1, 3, 4};
    adj[3] = {0, 2};
    adj[4] = {2};

    Solution obj;
    bool hasCycle = obj.isCycle(V, adj);

    if (hasCycle) {
        cout << "Cycle detected in the undirected graph." << endl;
    } else {
        cout << "No cycle detected in the undirected graph." << endl;
    }

    return 0;
}
