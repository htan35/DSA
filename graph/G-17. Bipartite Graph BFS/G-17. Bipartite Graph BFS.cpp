/*
 * Problem: Bipartite Graph using BFS
 * -----------------------------------
 * Approach: Breadth-First Search (BFS) 2-Coloring
 * 
 * Approach Explanation:
 * 1. A graph is bipartite if we can color every node using 2 colors (0 and 1) such that 
 *    no two adjacent nodes share the same color (i.e., the graph contains NO odd-length cycle).
 * 2. Helper `check(start, V, adj, color)`:
 *    - Initialize queue `queue<int> q` and push `start`.
 *    - Assign `color[start] = 0`.
 *    - While the queue is not empty:
 *        a. Pop `node = q.front()`.
 *        b. Traverse every neighbor `it` of `node`.
 *        c. If `color[it] == -1` (uncolored):
 *           - Assign opposite color: `color[it] = !color[node]` (or `1 - color[node]`).
 *           - Push `it` into queue.
 *        d. Else if `color[it] == color[node]`:
 *           - Adjacent node has the exact same color -> Graph cannot be bipartite, return false.
 *    - If all reachable nodes are colored without conflict, return true.
 * 3. `isBipartite(V, adj)`:
 *    - Initialize an array `color` of size V with `-1` (uncolored).
 *    - Loop through all vertices `0` to `V - 1` to handle disconnected components.
 *    - If `color[i] == -1`, run `check()`. If any component returns false, return false.
 *    - If all components pass, return true.
 * 
 * Time Complexity:  O(V + 2E) - Standard BFS visits every vertex and inspects every undirected edge.
 * Space Complexity: O(V) - For the color array and the BFS queue.
 */

#include <iostream>
#include <vector>
#include <queue>

using namespace std;

class Solution {
private:
    // Colors a single connected component using BFS
    bool check(int start, int V, vector<int> adj[], int color[]) {
        queue<int> q;
        q.push(start);
        color[start] = 0;

        while (!q.empty()) {
            int node = q.front();
            q.pop();

            for (auto neighbour : adj[node]) {
                // If the adjacent node is not yet colored
                if (color[neighbour] == -1) {
                    // eg 0 becomes 1 or vice versa
                    color[neighbour] = !color[node];
                    q.push(neighbour);
                }
                // If the adjacent node has the same color
                else if (color[neighbour] == color[node]) {
                    return false;
                }
            }
        }

        return true;
    }

public:
    // Function to check if graph is bipartite
    bool isBipartite(int V, vector<int> adj[]) {
        int color[V];
        for (int i = 0; i < V; i++) color[i] = -1;

        // Check for every component
        for (int i = 0; i < V; i++) {
            if (color[i] == -1) {
                if (check(i, V, adj, color) == false) {
                    return false;
                }
            }
        }

        return true;
    }
};

// 🔹 Driver Code
int main() {
    /*
        Graph 1 (Even cycle -> Bipartite):
        0 --- 1
        |     |
        3 --- 2
    */

    int V1 = 4;
    vector<int> adj1[V1];
    adj1[0] = {1, 3};
    adj1[1] = {0, 2};
    adj1[2] = {1, 3};
    adj1[3] = {0, 2};

    Solution obj;
    cout << "Graph 1 is Bipartite: " << (obj.isBipartite(V1, adj1) ? "Yes" : "No") << endl;

    /*
        Graph 2 (Odd cycle -> Not Bipartite):
        0 --- 1
         \   /
           2
    */

    int V2 = 3;
    vector<int> adj2[V2];
    adj2[0] = {1, 2};
    adj2[1] = {0, 2};
    adj2[2] = {0, 1};

    cout << "Graph 2 is Bipartite: " << (obj.isBipartite(V2, adj2) ? "Yes" : "No") << endl;

    return 0;
}
