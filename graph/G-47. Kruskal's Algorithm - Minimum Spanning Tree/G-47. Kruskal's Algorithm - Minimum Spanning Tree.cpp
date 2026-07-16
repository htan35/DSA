// GeeksforGeeks: Minimum Spanning Tree (Kruskal's Algorithm using DSU Union by Rank)
// Time Complexity: O(E log E + E * 4 * alpha) -> Where E is the number of edges. Sorting the edges dominates the runtime: O(E log E). Disjoint Set operations take near-constant amortized time.
// Space Complexity: O(V + E) -> Required for storing the flattened edge list and the internal tracking vectors inside the DisjointSet class.
// Approach: Kruskal's Algorithm built on a greedy edge-selection mechanism.
// 1. Flatten the input adjacency list into a linear array tracking edge objects: `{weight, {source, destination}}`.
// 2. Sort all collected edges in ascending order by weight.
// 3. Iterate through the sorted edges. For each edge, check if its endpoints belong to the same component set via `findUPar`.
// 4. If they belong to different components, including this edge will not form a cycle. Add its weight to `mstWt` and merge the components using `unionByRank`.

#include <bits/stdc++.h>
using namespace std;

// DSU Implementation using Union by Rank and Path Compression
class DisjointSet {
    vector<int> rank, parent;
public:
    DisjointSet(int n) {
        rank.resize(n + 1, 0);
        parent.resize(n + 1);
        for (int i = 0; i <= n; i++) {
            parent[i] = i;
        }
    }

    int findUPar(int node) {
        if (node == parent[node])
            return node;
        return parent[node] = findUPar(parent[node]); // Path Compression
    }

    void unionByRank(int u, int v) {
        int ulp_u = findUPar(u);
        int ulp_v = findUPar(v);
        
        if (ulp_u == ulp_v) return;
        
        if (rank[ulp_u] < rank[ulp_v]) {
            parent[ulp_u] = ulp_v;
        }
        else if (rank[ulp_v] < rank[ulp_u]) {
            parent[ulp_v] = ulp_u;
        }
        else {
            parent[ulp_v] = ulp_u;
            rank[ulp_u]++;
        }
    }
};

class Solution {
public:
    // Function to find sum of weights of edges of the Minimum Spanning Tree using Kruskal's Algorithm.
    int spanningTree(int V, vector<vector<int>> adj[]) {
        // Linear list to record edge configurations: {weight, {node_u, node_v}}
        vector<pair<int, pair<int, int>>> edges;
        
        // Step 1: Flatten the adjacency list structure into a linear edge sequence list
        for (int i = 0; i < V; i++) {
            for (auto it : adj[i]) {
                int adjNode = it[0];
                int wt = it[1];
                int node = i;
                
                edges.push_back({wt, {node, adjNode}});
            }
        }
        
        // Instantiate the DSU structure supporting nodes up to V
        DisjointSet ds(V);
        
        // Step 2: Sort all gathered edges in ascending order by weight
        sort(edges.begin(), edges.end());
        
        int mstWt = 0;
        
        // Step 3: Iterate through sorted edges and select valid structural links greedily
        for (auto it : edges) {
            int wt = it.first;
            int u = it.second.first;
            int v = it.second.second;
            
            // Cycle prevention check: If their ultimate parents differ, they belong to separate sets
            if (ds.findUPar(u) != ds.findUPar(v)) {
                mstWt += wt;
                
                // Modification: Linked using Union by Rank as requested instead of Union by Size
                ds.unionByRank(u, v); 
            }
        }
        
        return mstWt;
    }
};

int main() {
    int V = 5;
    vector<vector<int>> adj[5];
    
    // Constructing an undirected weighted graph matching standard validation patterns
    adj[0].push_back({1, 2}); adj[1].push_back({0, 2});
    adj[0].push_back({2, 1}); adj[2].push_back({0, 1});
    adj[1].push_back({2, 1}); adj[2].push_back({1, 1});
    adj[2].push_back({3, 2}); adj[3].push_back({2, 2});
    adj[2].push_back({4, 2}); adj[4].push_back({2, 2});
    adj[3].push_back({4, 1}); adj[4].push_back({3, 1});
    
    Solution sol;
    int totalMstWeight = sol.spanningTree(V, adj);
    
    cout << "Total weight of Minimum Spanning Tree via Kruskal's (Union by Rank): " << totalMstWeight << endl;
    
    // Expected Output:
    // Total weight of Minimum Spanning Tree via Kruskal's (Union by Rank): 5
    
    return 0;
}