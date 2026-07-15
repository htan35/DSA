// Bellman-Ford Algorithm
// Time: O(V * E)
// Space: O(V)
// Steps:
// 1) Initialize distances with INF and source as 0.
// 2) Relax all edges (V - 1) times.
// 3) One extra pass to detect a negative cycle.

#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    /* Function to implement Bellman Ford
    * edges: vector of vectors which represents the graph
    * S: source vertex to start traversing graph with
    * V: number of vertices
    */
    vector<int> bellman_ford(int V, vector<vector<int>>& edges, int S) {
        // Initialize distance array with INF
        vector<int> dist(V, 1e8);
        dist[S] = 0;

        // Relax all edges (V - 1) times
        for (int i = 0; i < V - 1; i++) {
            for (auto it : edges) {
                int u = it[0];
                int v = it[1];
                int wt = it[2];

                // Relax edge
                // We first check dist[u] != 1e8 to ensure the source vertex u
                // has a known (finite) distance; if u is still "infinity"
                // it means u is not reachable from the source S and we must
                // not use it to relax v. This also avoids adding wt to a
                // sentinel INF value which could overflow or produce
                // incorrect comparisons.
                if (dist[u] != 1e8 && dist[u] + wt < dist[v]) {
                    dist[v] = dist[u] + wt;
                }
            }
        }

        // Extra pass to check negative cycle
        for (auto it : edges) {
            int u = it[0];
            int v = it[1];
            int wt = it[2];

            // If still relaxable after (V-1) passes, a negative cycle exists
            // because shortest paths in a graph without negative cycles stabilize
            // within (V-1) edges; any further improvement means cycling with
            // total negative weight is reducing the path cost.
            if (dist[u] != 1e8 && dist[u] + wt < dist[v]) {
                return {-1}; 
            }
        }

        return dist;
    }
};

int main() {
    int V = 6;
    int S = 0; // Source node index

    // Graph definition: {source, destination, weight}
    vector<vector<int>> edges = {
        {3, 2, 6},
        {5, 3, 1},
        {0, 1, 5},
        {1, 5, -3},
        {1, 2, -2},
        {3, 4, -2},
        {2, 4, 3}
    };

    Solution sol;
    vector<int> distances = sol.bellman_ford(V, edges, S);

    if (distances.size() == 1 && distances[0] == -1) {
        cout << "Negative weight cycle detected in graph.\n";
    } else {
        cout << "Shortest distances from source node " << S << ":\n";
        for (int i = 0; i < V; i++) {
            cout << "Node " << i << " : " << distances[i] << "\n";
        }
    }

    // Expected Output:
    // Node 0 : 0
    // Node 1 : 5
    // Node 2 : 3
    // Node 3 : 3
    // Node 4 : 1
    // Node 5 : 2

    return 0;
}