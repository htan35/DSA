/*
 * Problem: Bipartite Graph Verification (DFS Approach)
 * ---------------------------------------------------
 * Approach: Graph 2-Coloring via Depth-First Search (DFS)
 * * Approach Explanation:
 * 1. Definition: A graph is bipartite if its vertices can be partitioned into 
 * two independent sets such that every edge connects a vertex in set 1 to 
 * a vertex in set 2 (i.e., no two adjacent vertices share the same color).
 * - Core Property: A graph with ANY odd-length cycle is NOT bipartite.
 * 2. Color Tracking:
 * - `color[i] = -1`: Vertex `i` is unvisited.
 * - `color[i] = 0` or `1`: Vertex `i` is assigned one of two colors.
 * 3. `dfs(node, col, color, adj)`:
 * - Assign color `col` to `node`.
 * - Traverse all adjacent neighbors `it` of `node`:
 * a. If `color[it] == -1` (uncolored):
 * - Recurse with inverted color `!col`.
 * - If that branch returns `false`, immediately return `false`.
 * b. If `color[it] == col` (already colored with the same color):
 * - An odd-length cycle is detected; return `false`.
 * 4. Multi-Component Handling:
 * - Loop `i` from `0` to `V - 1`. If `color[i] == -1`, trigger `dfs(i, 0, ...)`.
 * * Time Complexity:  O(V + 2E) - Visits every vertex and traverses all undirected edges.
 * Space Complexity: O(V)      - For the color tracking array and recursion call stack.
 */

#include <iostream>
#include <vector>

using namespace std;

class Solution {
private:
    bool dfs(int node, int col, int color[], vector<int> adj[]) {
        color[node] = col;

        for (auto it : adj[node]) {
            // If neighbor has not been colored yet
            if (color[it] == -1) {
                if (dfs(it, !col, color, adj) == false) 
                    return false;
            }
            // If adjacent neighbor already has the same color
            else if (color[it] == col) {
                return false;
            }
        }

        return true;
    }

public:
    bool isBipartite(int V, vector<int> adj[]) {
        int color[V];
        for (int i = 0; i < V; i++) color[i] = -1;

        // Ensure disconnected components are all checked
        for (int i = 0; i < V; i++) {
            if (color[i] == -1) {
                if (dfs(i, 0, color, adj) == false) 
                    return false;
            }
        }

        return true;
    }
};

// 🔹 Driver Code
int main() {
    /*
        Example Graph (Bipartite):
        0 --- 1
        |     |
        3 --- 2
    */
    int V = 4;
    vector<int> adj[4];
    adj[0] = {1, 3};
    adj[1] = {0, 2};
    adj[2] = {1, 3};
    adj[3] = {0, 2};

    Solution obj;
    if (obj.isBipartite(V, adj)) {
        cout << "Graph is Bipartite (contains no odd cycle)." << endl;
    } else {
        cout << "Graph is NOT Bipartite (contains an odd cycle)." << endl;
    }

    return 0;
}