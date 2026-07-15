// GeeksforGeeks: BFS of Graph
// Time Complexity: O(V + E) -> Where V is the number of vertices and E is the number of edges. We visit each node once and traverse all its adjacent neighbors.
// Space Complexity: O(V) -> Due to the queue, visited array, and the result vector tracking the vertices.
// Approach: Standard Breadth-First Search (BFS) using a FIFO queue and a tracking array to prevent processing duplicate cycles.
// We start at the source node (0), mark it visited, and push it to the queue. 
// Pop the front node, add it to the final tracking vector, and push all its unvisited direct neighbors into the queue.

#include <iostream>
#include <vector>
#include <queue>

using namespace std;

class Solution {
  public:
    // Function to return Breadth First Traversal of given graph.
    vector<int> bfsOfGraph(int V, vector<int> adj[]) {
        // Fix for compilation error in screenshot (line 10 used undefined variable 'n')
        // We dynamically initialize a tracking array of size V using vector or dynamic sizing.
        vector<int> vis(V, 0); 
        vis[0] = 1; // Mark the starting node as visited
        
        queue<int> q;
        q.push(0); // Initialize queue exploration from node index 0
        
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
    int V = 5; // Number of vertices
    vector<int> adj[5];
    
    // Constructing a sample directed graph:
    //     0 ---> 1 ---> 2
    //     |      |
    //     v      v
    //     2      3
    //     |
    //     v
    //     4
    adj[0].push_back(1);
    adj[0].push_back(2);
    adj[1].push_back(2);
    adj[1].push_back(3);
    adj[2].push_back(4);
    
    Solution sol;
    vector<int> result = sol.bfsOfGraph(V, adj);
    
    cout << "BFS Traversal output:\n[ ";
    for(int node : result) {
        cout << node << " ";
    }
    cout << "]\n";
    
    // Expected Output:
    // [ 0 1 2 3 4 ]
    
    return 0;
}