// LeetCode 547: Number of Provinces / Connected Components in a Graph
// Time Complexity: O(V^2) -> Where V is the number of vertices. Converting the adjacency matrix to an adjacency list takes O(V^2) time, and the DFS traversal visits all nodes and edges.
// Space Complexity: O(V) -> Due to the storage required for the converted adjacency list array, the visited tracking array, and the recursion stack.
// Approach: Identify the total number of disconnected islands (connected components) in the graph.
// 1. Convert the input adjacency matrix representation into a standard adjacency list representation.
// 2. Iterate through all vertices from 0 to V-1. If a vertex hasn't been visited yet, it marks the discovery of a new component (province).
// 3. Increment our count `cnt`, and trigger a DFS traversal to mark all other vertices reachable from this newly discovered node.

#include <iostream>
#include <vector>

using namespace std;

class Solution {
private:
    // Recursive DFS helper to explore and mark all nodes within the current connected component
    void dfs(int node, vector<int> adjLs[], vector<int> &vis) {
        vis[node] = 1; // Mark current vertex as visited
        
        // Traverse all neighbors linked to the current vertex
        for(auto it : adjLs[node]) {
            if(!vis[it]) {
                dfs(it, adjLs, vis);
            }
        }
    }

public:
    int numProvinces(vector<vector<int>> adj, int V) {
        // Fix for compilation issue in screenshot (line 21 used static array size for a variable-length V):
        // We initialize a dynamic array of vectors using vector container types
        vector<vector<int>> adjLs(V);
        
        // Step 1: Convert the Adjacency Matrix into an Adjacency List
        for(int i = 0; i < V; i++) {
            for(int j = 0; j < V; j++) {
                // If there is an edge between i and j, and it's not a self-loop
                // We skip self-loops (i == j) because they don't connect two different
                // vertices and therefore don't affect connectivity between nodes.
                // Example: for node 2, adj[2][2] == 1 is a self-loop. If we added
                // an edge 2->2 to the adjacency list it would only point back to
                // itself and DFS would mark node 2 visited once anyway. Self-loops
                // do not create new connections between distinct nodes, so they
                // should be ignored when counting connected components.
                if(adj[i][j] == 1 && i != j) {
                    adjLs[i].push_back(j);
                    // Notice: the matrix iteration will naturally check both directions, 
                    // so adding adjLs[j].push_back(i) is redundant here and has been cleaned up.
                }
            }
        }
        
        // Step 2: Traverse each component and keep track of the count
        vector<int> vis(V, 0);
        int cnt = 0;
        
        for(int i = 0; i < V; i++) {
            // If the node hasn't been visited, it must belong to a brand new component
            if(!vis[i]) {
                cnt++; // Increment the province counter
                dfs(i, adjLs.data(), vis); // Fire DFS to exhaustively discover all connected neighbors
            }
        }
        
        return cnt;
    }
};

int main() {
    // Constructing a sample graph with 3 vertices forming 2 provinces:
    // Province 1: Nodes [0, 1] (Connected)
    // Province 2: Node  [2]    (Isolated)
    vector<vector<int>> adj = {
        {1, 1, 0},
        {1, 1, 0},
        {0, 0, 1}
    };
    int V = 3;

    Solution sol;
    int provinces = sol.numProvinces(adj, V);

    cout << "Total number of provinces found: " << provinces << endl;

    // Expected Output:
    // Total number of provinces found: 2

    return 0;
}