// Disjoint Set Union (DSU) Data Structure using Union by Rank and Path Compression
// Time Complexity: O(4 * alpha) per operation -> amortized O(1), where alpha is the Inverse Ackermann function (grows extremely slowly)
// Space Complexity: O(N) -> Used by the rank and parent vectors tracking the sets
// Approach: Maintain sets of elements where each element points to a parent. 
// 1. `findUPar`: Finds the ultimate parent of a node and uses Path Compression to flatten the tree structure.
// 2. `unionByRank`: Connects two elements by attaching the tree with the smaller rank under the root of the tree with the larger rank.

#include <bits/stdc++.h>
using namespace std;

class DisjointSet {
    vector<int> rank, parent;
public:
    // Constructor to initialize n elements (1-based indexing supported by resizing to n+1)
    DisjointSet(int n) {
        rank.resize(n + 1, 0); // STEP 1: All nodes initially have a rank of 0
        parent.resize(n + 1);
        for (int i = 0; i <= n; i++) {
            parent[i] = i;     // STEP 2: Every node is initially its own parent (independent sets)
        }
    }

    // Function to find the ultimate parent of a component
    int findUPar(int node) {
        // Base case: If the node is its own parent, it is the ultimate parent of its set
        if (node == parent[node])
            return node;
            
        // STEP 3: PATH COMPRESSION
        // The result of the recursive call is assigned directly back to parent[node].
        // This attaches all visited nodes directly to the ultimate parent, flattening the tree structure 
        // and reducing future lookup times to near-constant O(1).
        return parent[node] = findUPar(parent[node]);
    }

    // Function to combine two independent sets based on their tree ranks
    void unionByRank(int u, int v) {
        // STEP 4: Find ultimate parents of both components
        int ulp_u = findUPar(u);
        int ulp_v = findUPar(v);
        
        // If they already share the same ultimate parent, they belong to the same set
        if (ulp_u == ulp_v) return;
        
        // STEP 5: Attach smaller rank tree under the larger rank tree
        if (rank[ulp_u] < rank[ulp_v]) {
            parent[ulp_u] = ulp_v; // Tree U becomes a subtree of Tree V; no rank increase for V
        }
        else if (rank[ulp_v] < rank[ulp_u]) {
            parent[ulp_v] = ulp_u; // Tree V becomes a subtree of Tree U; no rank increase for U
        }
        else {
            // STEP 6: If ranks are equal, attach one to the other arbitrarily and increment the new root's rank
            parent[ulp_v] = ulp_u;
            rank[ulp_u]++;
        }
    }
};

int main() {
    // Creating a disjoint set with elements up to index 7
    DisjointSet ds(7);
    
    // Simulating component links
    ds.unionByRank(1, 2);
    ds.unionByRank(2, 3);
    ds.unionByRank(4, 5);
    ds.unionByRank(6, 7);
    ds.unionByRank(5, 6);
    
    // Check if 3 and 7 belong to the same component set
    if (ds.findUPar(3) == ds.findUPar(7)) {
        cout << "Same\n";
    } else {
        cout << "Not same\n"; // Expected Output
    }
    
    // Connect the two larger remaining components together
    ds.unionByRank(3, 7);
    
    // Check connectivity validation again after linking
    if (ds.findUPar(3) == ds.findUPar(7)) {
        cout << "Same\n"; // Expected Output
    } else {
        cout << "Not same\n";
    }
    
    return 0;
}