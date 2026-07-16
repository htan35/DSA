// Disjoint Set Union (DSU) Data Structure using Union by Size and Path Compression
// Time Complexity: O(4 * alpha) per operation -> amortized O(1), where alpha is the Inverse Ackermann function
// Space Complexity: O(N) -> Used by the size and parent vectors tracking the sets
// Approach: Maintain sets of elements where each element points to a parent.
// 1. `findUPar`: Finds the ultimate parent of a node and uses Path Compression to flatten the tree.
// 2. `unionBySize`: Connects two sets by attaching the tree with the smaller number of nodes (smaller size) 
//    under the root of the tree with the larger number of nodes (larger size), updating the size of the combined root.

#include <bits/stdc++.h>
using namespace std;

class DisjointSet {
    vector<int> size, parent;
public:
    // Constructor to initialize n elements (1-based indexing supported)
    DisjointSet(int n) {
        size.resize(n + 1, 1);   // STEP 1: Every node initially forms a set of size 1
        parent.resize(n + 1);
        for (int i = 0; i <= n; i++) {
            parent[i] = i;       // STEP 2: Every node is initially its own parent
        }
    }

    // Function to find the ultimate parent of a component (with Path Compression)
    int findUPar(int node) {
        if (node == parent[node])
            return node;
            
        // STEP 3: PATH COMPRESSION (Flattens the tree structure for O(1) lookups)
        return parent[node] = findUPar(parent[node]);
    }

    // Function to combine two independent sets based on their total size (node count)
    // Updated as per the logic shown in your screenshot
    void unionBySize(int u, int v) {
        // STEP 4: Find ultimate parents of both components
        int ulp_u = findUPar(u);
        int ulp_v = findUPar(v);
        
        // If they share the same ultimate parent, they are already in the same set
        if (ulp_u == ulp_v) return;
        
        // STEP 5: Attach the smaller component under the larger component
        if (size[ulp_u] < size[ulp_v]) {
            parent[ulp_u] = ulp_v;            // Make root of V the parent of root of U
            size[ulp_v] += size[ulp_u];       // Add the size of U to the size of V
        }
        else {
            parent[ulp_v] = ulp_u;            // Make root of U the parent of root of V
            size[ulp_u] += size[ulp_v];       // Add the size of V to the size of U
        }
    }
};

int main() {
    // Creating a disjoint set with elements up to index 7
    DisjointSet ds(7);
    
    // Simulating component links using Union by Size (matching the screenshot calls)
    ds.unionBySize(1, 2);
    ds.unionBySize(2, 3);
    ds.unionBySize(4, 5);
    ds.unionBySize(6, 7);
    
    // Additional links to merge the groups (similar to the logic used in Union by Rank)
    ds.unionBySize(5, 6);
    
    // Check if 3 and 7 belong to the same component set
    if (ds.findUPar(3) == ds.findUPar(7)) {
        cout << "Same\n";
    } else {
        cout << "Not same\n"; // Expected Output
    }
    
    // Connect the two remaining components together
    ds.unionBySize(3, 7);
    
    // Check connectivity validation again after linking
    if (ds.findUPar(3) == ds.findUPar(7)) {
        cout << "Same\n"; // Expected Output
    } else {
        cout << "Not same\n";
    }
    
    return 0;
}