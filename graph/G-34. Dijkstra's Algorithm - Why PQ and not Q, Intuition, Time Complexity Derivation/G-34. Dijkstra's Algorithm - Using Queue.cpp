// Dijkstra Algorithm using a standard Queue (instead of Priority Queue or Set)
// Time Complexity: O(V * E) -> In the worst case, replacing the min-heap with a standard FIFO queue means 
// nodes can be pushed and re-processed multiple times upon structural relaxation updates.
// Space Complexity: O(V + E) -> Occupied by the FIFO queue and the distance array tracking shortest paths.
// Approach: A variation of shortest path relaxation (similar to the Shortest Path Faster Algorithm / SPFA).
// 1. Initialize all vertex distances to a large value (1e9) and set the source vertex distance to 0.
// 2. Use a standard FIFO `std::queue` to track nodes whose distances have updated.
// 3. Pop the front node, explore its neighbors, and if a shorter path is found, update the neighbor's 
//    distance and push it into the queue to propagate the changes.

#include <iostream>
#include <vector>
#include <queue>

using namespace std;

class Solution {
public:
    // Function to find the shortest distance of all the vertices from the source vertex S.
    vector<int> dijkstraUsingQueue(int V, vector<vector<int>> adj[], int S) {
        // Standard FIFO queue tracking node indices to process
        queue<int> q;
        
        // Initialize distance array to infinity (1e9)
        vector<int> dist(V, 1e9);
        
        // Base setup for the source node
        dist[S] = 0;
        q.push(S);
        
        while (!q.empty()) {
            int node = q.front();
            q.pop();
            
            // Traverse all neighbor channels linked adjacent to the current node position
            for (auto neighbor : adj[node]) {
                int adjNode = neighbor[0];
                int edgeWeight = neighbor[1];
                
                // Edge Relaxation Check
                if (dist[node] + edgeWeight < dist[adjNode]) {
                    dist[adjNode] = dist[node] + edgeWeight;
                    
                    // Push the neighbor into the queue so its updated distance 
                    // can be propagated down to its own subsequent neighbors
                    q.push(adjNode);
                }
            }
        }
        return dist;
    }
};

int main() {
    int V = 3;
    int S = 0; // Source vertex
    
    // Adjacency List where each element represents an edge: {neighbor_node, edge_weight}
    vector<vector<int>> adj[3];
    
    // Constructing a sample weighted undirected graph:
    //      (1) <-- 1 --> (0) <-- 6 --> (2)
    //       ^                           |
    //       +------------ 3 ------------+
    adj[0].push_back({1, 1});
    adj[0].push_back({2, 6});
    
    adj[1].push_back({0, 1});
    adj[1].push_back({2, 3});
    
    adj[2].push_back({0, 6});
    adj[2].push_back({1, 3});
    
    Solution sol;
    vector<int> distances = sol.dijkstraUsingQueue(V, adj, S);
    
    cout << "Shortest distances from source node " << S << " using standard Queue:\n";
    for (int i = 0; i < V; i++) {
        cout << "Node " << i << " : " << distances[i] << "\n";
    }
    
    // Expected Output:
    // Node 0 : 0
    // Node 1 : 1
    // Node 2 : 4
    
    return 0;
}