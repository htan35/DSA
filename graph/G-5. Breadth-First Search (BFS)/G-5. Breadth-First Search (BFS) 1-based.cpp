// GeeksforGeeks: BFS of Graph (1-Based Indexing Modification)
// Time Complexity: O(V + E) -> Where V is the number of vertices and E is the number of edges.
// Space Complexity: O(V) -> Due to the tracking structures (queue, visited array, and result vector).
// Approach: Standard Breadth-First Search (BFS) adapted for 1-based indexed graphs.
// The visited tracking array is initialized with size (V + 1) to safely accommodate indices up to V.
// Traversal begins by pushing the first vertex (1) into the queue.

#include <iostream>
#include <vector>
#include <queue>

using namespace std;

class Solution {
  public:
    // Function to return Breadth First Traversal of given 1-indexed graph.
    vector<int> bfsOfGraph(int V, vector<int> adj[]) {
        // Size is set to V + 1 so that we can directly use indices from 1 to V without out-of-bounds errors
        vector<int> vis(V + 1, 0); 
        vis[1] = 1; // Mark the starting node (1) as visited
        
        queue<int> q;
        q.push(1); // Initialize exploration from node index 1
        
        vector<int> bfs;
        
        while(!q.empty()) {
            int node = q.front();
            q.pop();
            bfs.push_back(node);
            
            // Traverse all neighbor channels adjacent to the current node position
            for(auto it : adj[node]) {
                // If the neighboring vertex hasn't been discovered yet, register it
                if(!vis[it]) {
                    vis[it] = 1;
                    q.push(it);
                }
            }
        }
        return bfs;
    }
};

int main() {
    int V = 5; // Number of vertices (numbered 1 to 5)
    
    // Array size must be V + 1 to support 1-based index access for adjacency list heads
    vector<int> adj[6]; 
    
    // Constructing a sample directed graph with 1-based nodes:
    //     1 ---> 2 ---> 3
    //     |      |
    //     v      v
    //     3      4
    //     |
    //     v
    //     5
    adj[1].push_back(2);
    adj[1].push_back(3);
    adj[2].push_back(3);
    adj[2].push_back(4);
    adj[3].push_back(5);
    
    Solution sol;
    vector<int> result = sol.bfsOfGraph(V, adj);
    
    cout << "BFS Traversal output (1-Based Indexing):\n[ ";
    for(int node : result) {
        cout << node << " ";
    }
    cout << "]\n";
    
    // Expected Output:
    // [ 1 2 3 4 5 ]
    
    return 0;
}