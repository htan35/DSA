// GeeksforGeeks: Dijkstra Algorithm (Shortest Distance from Source)
// Time Complexity: O(E log V) -> Where E is the number of edges and V is the number of vertices. The min-heap operations take logarithmic time.
// Space Complexity: O(V + E) -> Occupied by the min-heap priority queue and the distance tracking array.
// Approach: Classic greedy Dijkstra's algorithm using a min-heap (`std::priority_queue` with a `greater` comparator). 
// 1. Initialize all vertex distances to a large value (`1e9`) and set the source vertex distance to `0`.
// 2. Continually extract the node with the minimum tentative distance from the priority queue.
// 3. Relax all outgoing edge structures: if traveling through the current node yields a shorter path to a neighbor, 
//    update its distance and push the updated configurations into the priority queue.

#include <iostream>
#include <vector>
#include <queue>

using namespace std;

class Solution {
public:
    // Function to find the shortest distance of all the vertices from the source vertex S.
    vector<int> dijkstra(int V, vector<vector<int>> adj[], int S) {
        // Min-heap tracking: pair<current_accumulated_distance, node_index>
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
        
        // Initialize distance array to infinity (1e9)
        vector<int> dist(V, 1e9);
        
        // Base setup for source node
        dist[S] = 0;
        pq.push({0, S}); 
        
        while (!pq.empty()) {
            int dis = pq.top().first;
            int node = pq.top().second;
            pq.pop();
            
            // Optimization: If we found a shorter path to this node already, skip old stale entries
            if (dis > dist[node]) continue;
            
            // Traverse all neighbor channels linked adjacent to the current node position
            for (auto it : adj[node]) {
                int adjNode = it[0];
                int edgeWeight = it[1];
                
                // Edge Relaxation check
                if (dis + edgeWeight < dist[adjNode]) {
                    dist[adjNode] = dis + edgeWeight;
                    pq.push({dist[adjNode], adjNode});
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
    vector<int> distances = sol.dijkstra(V, adj, S);
    
    cout << "Shortest distances from source node " << S << ":\n";
    for (int i = 0; i < V; i++) {
        cout << "Node " << i << " : " << distances[i] << "\n";
    }
    
    // Expected Output:
    // Node 0 : 0
    // Node 1 : 1
    // Node 2 : 4
    
    return 0;
}