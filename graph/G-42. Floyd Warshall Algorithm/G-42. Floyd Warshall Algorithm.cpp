/*
 * Problem: Floyd-Warshall Algorithm (All-Pairs Shortest Path)
 * -----------------------------------------------------------
 * Approach: Dynamic Programming / Multi-Source Shortest Path via Intermediate Nodes
 * 
 * Approach Explanation:
 * 1. The Floyd-Warshall algorithm finds the shortest distance between every pair of vertices 
 *    in an edge-weighted directed graph and can detect negative weight cycles.
 * 2. Preprocessing:
 *    - In the input adjacency matrix, an edge weight of `-1` denotes unreachable nodes.
 *    - Convert `-1` to infinity (`1e9`) so standard addition/min logic doesn't treat -1 as negative cost.
 *    - Set self-loop distances `matrix[i][i] = 0`.
 * 3. 3-Nested Loops (Dynamic Transition):
 *    - Loop intermediate vertex `k` from `0` to `n - 1`:
 *        - Try routing through node `k`:
 *          `matrix[i][j] = min(matrix[i][j], matrix[i][k] + matrix[k][j])`
 * 4. Negative Cycle Detection:
 *    - If after relaxation any `matrix[i][i] < 0`, a negative-weight cycle exists.
 * 5. Postprocessing:
 *    - Convert unreachable nodes marked as `1e9` back to `-1` to meet problem output format.
 * 
 * Time Complexity:  O(N^3) - Three nested loops of size N.
 * Space Complexity: O(1)   - Done in-place modifying the given distance matrix.
 */

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    void shortest_distance(vector<vector<int>>& matrix) {
        int n = matrix.size();

        // Step 1: Pre-process unreachable cells and self-distances
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (matrix[i][j] == -1) {
                    matrix[i][j] = 1e9;
                }
                if (i == j) {
                    matrix[i][j] = 0;
                }
            }
        }

        // Step 2: Floyd-Warshall core relaxation loop via intermediate node k
        for (int k = 0; k < n; k++) {
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < n; j++) {
                    matrix[i][j] = min(matrix[i][j], matrix[i][k] + matrix[k][j]);
                }
            }
        }

        // Step 3 (Optional Check): Detect negative weight cycles
        /*
        for (int i = 0; i < n; i++) {
            if (matrix[i][i] < 0) {
                // Negative weight cycle exists reachable from node i
            }
        }
        */

        // Step 4: Revert 1e9 values back to -1 representing unreachable pairs
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (matrix[i][j] >= 1e9) {
                    matrix[i][j] = -1;
                }
            }
        }
    }
};

// 🔹 Driver Code
int main() {
    /*
        Example:
        Matrix representing directed graph:
        Node 0 to 1 has cost 2
        Node 1 to 0 has cost 1
        Node 0 to 2 has cost 43
        Node 1 to 2 has cost 6
        
        Expected shortest path 0 -> 2 is 0 -> 1 -> 2 with cost 2 + 6 = 8 (or 1 + 6 = 7 depending on input)
    */

    vector<vector<int>> matrix = {
        {0, 1, 43},
        {1, 0, 6},
        {-1, -1, 0}
    };

    Solution obj;
    obj.shortest_distance(matrix);

    cout << "All-Pairs Shortest Path Matrix:\n";
    for (const auto& row : matrix) {
        for (int val : row) {
            cout << val << "\t";
        }
        cout << "\n";
    }

    return 0;
}