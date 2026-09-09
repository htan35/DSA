/*
 * Problem: Detect Cycle in a Directed Graph using DFS
 * ----------------------------------------------------
 * Approach: DFS with Path Visited Tracking (Two Arrays)
 * 
 * Approach Explanation:
 * 1. Unlike undirected graphs, encountering an already visited node in a directed graph 
 *    does NOT necessarily mean a cycle exists (it could just be a cross-edge from a different branch).
 * 2. A cycle exists only if a node points back to an ancestor on the CURRENT recursion path (a back-edge).
 * 3. Two tracking arrays are used:
 *    - `vis[]`: Tracks whether a node has been visited across all DFS calls.
 *    - `dfsVis[]` (pathVis): Tracks whether a node is currently in the active DFS call stack path.
 * 4. Algorithm (`checkCycle`):
 *    - Mark `vis[node] = 1` and `dfsVis[node] = 1`.
 *    - For every outgoing neighbor `it` of `node`:
 *        a. If `!vis[it]`: Recursively explore `checkCycle(it)`. If true, return true.
 *        b. Else if `dfsVis[it] == 1`: The neighbor is already on the current path -> Cycle detected! Return true.
 *    - Backtracking Step: Before returning false, reset `dfsVis[node] = 0` since this node is no longer 
 *      in the active recursion path.
 * 5. `isCyclic(N, adj)`:
 *    - Loop through all nodes `0` to `N - 1` to handle disconnected components.
 * 
 * Time Complexity:  O(V + E) - Visits every vertex and directed edge at most once.
 * Space Complexity: O(2V) + O(V) stack space = O(V).
 */

#include <iostream>
#include <vector>
#include <cstring>

using namespace std;

class Solution {
private:
    bool checkCycle(int node, vector<int> adj[], int vis[], int dfsVis[]) {
        vis[node] = 1;
        dfsVis[node] = 1;

        for (auto it : adj[node]) {
            // When node is not visited
            if (vis[it] == 0) {
                if (checkCycle(it, adj, vis, dfsVis)) 
                    return true;
            } 
            // If node has been visited previously on the same path
            else if (dfsVis[it] == 1) {
                return true;
            }
        }

        // Backtrack: remove node from current recursion path
        dfsVis[node] = 0;
        return false;
    }

public:
    // Function to detect cycle in a directed graph.
    bool isCyclic(int N, vector<int> adj[]) {
        int vis[N];
        int dfsVis[N];
        memset(vis, 0, sizeof(vis));
        memset(dfsVis, 0, sizeof(dfsVis));

        for (int i = 0; i < N; i++) {
            if (!vis[i]) {
                if (checkCycle(i, adj, vis, dfsVis)) {
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
        Directed Graph:
        1 ---> 2 ---> 3
               ^      |
               |      v
               5 <--- 4

        Cycle present: 2 -> 3 -> 4 -> 5 -> 2
    */

    int N = 6; // Nodes 0 to 5
    vector<int> adj[N];

    adj[1].push_back(2);
    adj[2].push_back(3);
    adj[3].push_back(4);
    adj[4].push_back(5);
    adj[5].push_back(2);

    Solution obj;
    if (obj.isCyclic(N, adj)) {
        cout << "Cycle detected in the directed graph." << endl;
    } else {
        cout << "No cycle detected in the directed graph." << endl;
    }

    return 0;
}
