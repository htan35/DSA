// GeeksforGeeks: DFS of Graph
// Time Complexity: O(V + E) -> Where V is the number of vertices and E is the number of edges. We visit each vertex exactly once and traverse its entire adjacency list.
// Space Complexity: O(V) -> Due to the visited array, the result vector `ls`, and the recursive call stack space in the worst case.
// Approach: Standard Depth-First Search (DFS) implementation using a recursive helper function and a tracking array to avoid cycles.
// We start at the source node (0), mark it visited, and store it. Then, we recursively dive deep into the first unvisited neighbor 
// before backtracking to check remaining neighbor branches.

#include <iostream>
#include <vector>

using namespace std;

class Solution {
  private:
    // Recursive DFS traversal engine
    void dfs(int node, vector<int> adj[], int vis[], vector<int> &ls) {
        vis[node] = 1;       // Mark current vertex as visited
        ls.push_back(node);  // Store it in the traversal result list
        
        // Traverse all direct neighbors of the current node position
        for(auto it : adj[node]) {
            // If the neighbor hasn't been discovered, dive deep into it recursively
            if(!vis[it]) {
                dfs(it, adj, vis, ls);
            }
        }
    }

  public:
    // Function to return a list containing the DFS traversal of the graph.
    vector<int> dfsOfGraph(int V, vector<int> adj[]) {
        // Fix for compilation error in screenshot (line 22 used undefined variable 'n')
        // We initialize a standard array of size V dynamically using a vector or a local dynamic allocation block.
        vector<int> vis(V, 0); 
        int start = 0; // DFS starting node index
        vector<int> ls;
        
        // Pass the pointer data of our visited vector into the recursive driver
        dfs(start, adj, vis.data(), ls);
        
        return ls;
    }
};

int main() {
    int V = 5; // Number of vertices
    vector<int> adj[5];
    
    // Constructing a sample directed graph:
    //     0 ---> 2 ---> 4
    //     |
    //     v
    //     1 ---> 3
    adj[0].push_back(2);
    adj[0].push_back(1);
    adj[2].push_back(4);
    adj[1].push_back(3);
    
    Solution sol;
    vector<int> result = sol.dfsOfGraph(V, adj);
    
    cout << "DFS Traversal output:\n[ ";
    for(int node : result) {
        cout << node << " ";
    }
    cout << "]\n";
    
    // Expected Output:
    // [ 0 2 4 1 3 ]
    
    return 0;
}