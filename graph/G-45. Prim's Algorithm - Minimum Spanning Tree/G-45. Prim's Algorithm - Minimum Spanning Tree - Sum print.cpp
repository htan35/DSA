// GeeksforGeeks: Minimum Spanning Tree (Prim's Algorithm)
// Time Complexity: O(E log E) -> Where E is the number of edges. Inserting and extracting from the min-heap priority queue takes logarithmic time.
// Space Complexity: O(V + E) -> Used by the priority queue, the visited array vector, and the adjacency list tracking structures.
// Approach: A greedy Post-Order structural sweep variation known as Prim's Algorithm to construct a Minimum Spanning Tree (MST).
// 1. Maintain a min-heap tracking elements sorted by edge weight: pair<edge_weight, node_index>.
// 2. Start from an arbitrary node (0) with a weight of 0.
// 3. Pop the lowest weight node from the priority queue. If it has already been visited (marked as part of the MST), skip it using `continue`.
// 4. Otherwise, permanently lock the node into the MST by setting `vis[node] = 1`, add its edge weight to `sum`, and push all its unvisited neighbor configurations into the min-heap.

#include <iostream>
#include <vector>
#include <queue>

using namespace std;

class Solution {
public:
    // Function to find sum of weights of edges of the Minimum Spanning Tree.
    int spanningTree(int V, vector<vector<int>> adj[]) {
        // Min-heap tracking: pair<edge_weight, node_index>
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
        
        // Visited array tracking: vis[i] = 1 if node i is included in the MST structure
        vector<int> vis(V, 0);
        
        // Push the starting source node {weight, node}
        pq.push({0, 0});
        int sum = 0;
        
        while (!pq.empty()) {
            auto it = pq.top();
            pq.pop();
            
            int node = it.second;
            int wt = it.first;
            
            // If the node is already a confirmed part of the MST structure, bypass it
            if (vis[node] == 1) continue;
            
            // Add node value edge weight configuration permanently into the expanding MST sum
            vis[node] = 1;
            sum += wt;
            
            // Traverse all neighbor channels linked adjacent to the current node position
            for (auto it : adj[node]) {
                int adjNode = it[0];
                int edW = it[1];
                
                // If the adjacent neighbor node is not yet locked inside the MST path, push it to the queue
                if (!vis[adjNode]) {
                    pq.push({edW, adjNode});
                }
            }
        }
        return sum;
    }
};

int main() {
    int V = 3;
    
    // Adjacency List where each element represents an edge: {neighbor_node, edge_weight}
    vector<vector<int>> adj[3];
    
    // Constructing a sample weighted undirected graph:
    //       (0)
    //      /   \
    //     5     1
    //    /       \
    //  (1)---3---(2)
    adj[0].push_back({1, 5});
    adj[0].push_back({2, 1});
    
    adj[1].push_back({0, 5});
    adj[1].push_back({2, 3});
    
    adj[2].push_back({0, 1});
    adj[2].push_back({1, 3});
    
    Solution sol;
    int mstWeightSum = sol.spanningTree(V, adj);
    
    cout << "Total weight of the Minimum Spanning Tree (MST): " << mstWeightSum << endl;
    
    // Expected Output:
    // Total weight of the Minimum Spanning Tree (MST): 4 (Edges chosen: 0-2 with weight 1, and 2-1 with weight 3)
    
    return 0;
}