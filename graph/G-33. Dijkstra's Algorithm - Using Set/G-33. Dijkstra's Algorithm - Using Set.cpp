// GeeksforGeeks: Dijkstra Algorithm (Shortest Distance from Source using std::set)
// Time Complexity: O(E log V) -> Where E is the number of edges and V is the number of vertices. Set operations take logarithmic time.
// Space Complexity: O(V + E) -> Occupied by the sorted set and the distance array tracking shortest paths.
// Approach: Alternative implementation of Dijkstra's algorithm utilizing a balanced binary search tree (`std::set`).
// 1. Maintain a unique, sorted collection of pairs `{distance, node}`. `std::set` automatically orders items in ascending order.
// 2. Extract the minimum distance node from the front using `st.begin()`.
// 3. Instead of keeping stale path records (like priority_queue does), if a shorter path to a neighbor node is discovered, 
//    we explicitly search for and erase the old `{dist[adjNode], adjNode}` entry from the set before inserting the updated version.

#include <iostream>
#include <vector>
#include <set>

using namespace std;

class Solution {
public:
    // Function to find the shortest distance of all the vertices from the source vertex S.
    vector<int> dijkstra(int V, vector<vector<int>> adj[], int S) {
        // Set storage stores: pair<current_accumulated_distance, node_index>
        set<pair<int, int>> st;
        
        // Initialize distance array to infinity (1e9)
        vector<int> dist(V, 1e9);
        
        // Base setup for source node
        dist[S] = 0;
        st.insert({0, S});
        
        while (!st.empty()) {
            // Fetch the element with the lowest tentative path distance value from the front boundary
            auto it = *(st.begin());
            int node = it.second;
            int dis = it.first;
            
            // Remove the processed element from the set configuration
            st.erase(st.begin()); // Note: Screenshot passed the pair 'it' to erase. Both erase(it) and erase(iterator) work.
            
            // Traverse all neighbor channels linked adjacent to the current node position
            for (auto neighbor : adj[node]) {
                int adjNode = neighbor[0];
                int edgW = neighbor[1];
                
                // Edge Relaxation Check
                if (dis + edgW < dist[adjNode]) {
                    
                    // Optimization feature of Set: If the node was already reachable via a longer path,
                    // erase its old entry to save redundant iterations later.
                    if (dist[adjNode] != 1e9) {
                        st.erase({dist[adjNode], adjNode});
                    }
                    
                    // Update the shortest path record configurations
                    dist[adjNode] = dis + edgW;
                    st.insert({dist[adjNode], adjNode});
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
    
    cout << "Shortest distances from source node " << S << " using Set:\n";
    for (int i = 0; i < V; i++) {
        cout << "Node " << i << " : " << distances[i] << "\n";
    }
    
    // Expected Output:
    // Node 0 : 0
    // Node 1 : 1
    // Node 2 : 4
    
    return 0;
}