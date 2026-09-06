/*
 * Problem: Detect Cycle in an Undirected Graph using BFS
 * ------------------------------------------------------
 * Approach: Breadth-First Search (BFS) with Parent Tracking
 * 
 * Approach Explanation:
 * 1. For an undirected graph, a cycle exists if during BFS we reach an adjacent node 
 *    that is already visited AND is NOT the parent of the current node.
 * 2. `detect(src, adj, vis)`:
 *    - Use a queue of pairs: `queue<pair<int, int>> q` storing `{current_node, parent_node}`.
 *    - Push the starting node with parent = -1 and mark it visited: `vis[src] = 1`.
 *    - While the queue is not empty:
 *        a. Pop `{node, parent}`.
 *        b. Traverse all adjacent neighbors of `node`.
 *        c. If neighbor is unvisited: mark `vis[adjacentNode] = 1` and push `{adjacentNode, node}`.
 *        d. Else if neighbor is visited AND `parent != adjacentNode`: a cycle is detected -> return true.
 * 3. `isCycle(V, adj)`:
 *    - Maintain a visited array `vis` initialized to 0.
 *    - Iterate from `0` to `V - 1` to handle disconnected components:
 *        If `!vis[i]`, call `detect(i, adj, vis)`. If any component returns true, return true.
 *    - If all components finish without finding a cycle, return false.
 * 
 * Time Complexity:  O(V + 2E) - Standard BFS visits every vertex and explores every edge twice.
 * Space Complexity: O(V) - For the visited array and the BFS queue.
 */

#include <iostream>
#include <vector>
#include <queue>

using namespace std;

class Solution {
private:
    bool detect(int src, vector<int> adj[], int vis[]) {
        vis[src] = 1;
        queue<pair<int, int>> q;
        q.push({src, -1});

        while (!q.empty()) {
            int node = q.front().first;
            int parent = q.front().second;
            q.pop();

            for (auto adjacentNode : adj[node]) {
                if (!vis[adjacentNode]) {
                    vis[adjacentNode] = 1;
                    q.push({adjacentNode, node});
                } 
                else if (parent != adjacentNode) {
                    // Visited node that is NOT parent means someone else reached it -> Cycle
                    return true;
                }
            }
        }

        return false;
    }

public:
    // Function to detect cycle in an undirected graph.
    bool isCycle(int V, vector<int> adj[]) {
        int vis[V] = {0};

        // Check for cycle across all connected components
        for (int i = 0; i < V; i++) {
            if (!vis[i]) {
                if (detect(i, adj, vis)) return true;
            }
        }

        return false;
    }
};

// 🔹 Driver Code
int main() {
    /*
        Graph:
        0 --- 1
        |     |
        3 --- 2 --- 4

        Cycle present: 0-1-2-3-0
    */

    int V = 5;
    vector<int> adj[V];

    adj[0] = {1, 3};
    adj[1] = {0, 2};
    adj[2] = {1, 3, 4};
    adj[3] = {0, 2};
    adj[4] = {2};

    Solution obj;
    bool hasCycle = obj.isCycle(V, adj);

    if (hasCycle) {
        cout << "Cycle detected in the undirected graph." << endl;
    } else {
        cout << "No cycle detected in the undirected graph." << endl;
    }

    return 0;
}
