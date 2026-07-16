// GeeksforGeeks: Minimum Spanning Tree (Prim's Algorithm - Printing Edges)
// Time Complexity: O(E log E) -> Where E is the number of edges. Min-heap operations drive the execution time.
// Space Complexity: O(V + E) -> Used by the priority queue, structural vectors, and adjacency structures.
// Approach: Extend the greedy min-heap Prim's implementation to track graph structure linkages.
// 1. Alter the priority queue structure to store tracking triplets: `{edge_weight, {current_node, parent_node}}`.
// 2. Start by pushing an initial node (0) linked to a dummy parent (-1) with a baseline weight of 0.
// 3. When parsing items out of the min-heap, if the current node hasn't been visited and its parent is valid (not -1), 
//    append the pair `{parent, node}` directly into our tracking MST vector list before updating adjacent paths.

#include <iostream>
#include <vector>
#include <queue>

using namespace std;

class Solution {
public:
    // Function to find sum of weights of edges of the Minimum Spanning Tree and return its edges.
    int spanningTree(int V, vector<vector<int>> adj[], vector<pair<int, int>> &mstEdges) {
        // Min-heap tracking triplets: pair<edge_weight, pair<current_node, parent_node>>
        priority_queue<pair<int, pair<int, int>>, 
                       vector<pair<int, pair<int, int>>>, 
                       greater<pair<int, pair<int, int>>>> pq;
        
        // Visited tracking array
        vector<int> vis(V, 0);
        
        // Push the starting configuration: {weight, {node, parent}}
        // Node 0 starts with a dummy parent of -1
        pq.push({0, {0, -1}});
        int sum = 0;
        
        while (!pq.empty()) {
            auto it = pq.top();
            pq.pop();
            
            int wt = it.first;
            int node = it.second.first;
            int parent = it.second.second;
            
            // If the node is already processed inside the MST boundary, skip it
            if (vis[node] == 1) continue;
            
            // Mark node as part of MST and accumulate its edge weight
            vis[node] = 1;
            sum += wt;
            
            // If it's not the initial starting root node, record this valid structural edge transition
            if (parent != -1) {
                mstEdges.push_back({parent, node});
            }
            
            // Traverse all neighbor channels linked adjacent to the current node position
            for (auto neighbor : adj[node]) {
                int adjNode = neighbor[0];
                int edW = neighbor[1];
                
                // If the neighboring vertex hasn't been added to the MST, push it to the heap with the current node as its parent
                if (!vis[adjNode]) {
                    pq.push({edW, {adjNode, node}});
                }
            }
        }
        return sum;
    }
};

int main() {
    // Constructing the exact sample graph structure from your screenshot:
    // Vertices: 5 (0, 1, 2, 3, 4)
    int V = 5;
    vector<vector<int>> adj[5];
    
    // Adding undirected edges: {neighbor, weight}
    adj[0].push_back({1, 2}); adj[1].push_back({0, 2});
    adj[0].push_back({2, 1}); adj[2].push_back({0, 1});
    adj[1].push_back({2, 1}); adj[2].push_back({1, 1});
    adj[2].push_back({3, 2}); adj[3].push_back({2, 2});
    adj[2].push_back({4, 2}); adj[4].push_back({2, 2});
    adj[3].push_back({4, 1}); adj[4].push_back({3, 1});
    
    Solution sol;
    vector<pair<int, int>> mstEdges;
    int totalWeight = sol.spanningTree(V, adj, mstEdges);
    
    cout << "Total weight of the Minimum Spanning Tree (MST): " << totalWeight << endl;
    cout << "Edges included in the MST structure:\n";
    for (auto edge : mstEdges) {
        cout << "(" << edge.first << ", " << edge.second << ")\n";
    }
    
    // Expected Output:
    // Total weight of the Minimum Spanning Tree (MST): 5
    // Edges included in the MST structure match the image: (0, 2), (2, 1), (2, 3), (3, 4)
    
    return 0;
}