/*
 * Problem: Topological Sort using BFS (Kahn's Algorithm)
 * ------------------------------------------------------
 * Approach: In-degree Array + Queue-based Breadth-First Search
 * * Approach Explanation:
 * 1. Kahn's algorithm resolves dependencies by repeatedly removing nodes that 
 * have no incoming prerequisites (in-degree == 0).
 * 2. Calculate In-degrees:
 * - For every directed edge u -> v, increment `indegree[v]++`.
 * 3. Initialize Queue:
 * - Push all vertices with `indegree == 0` into a queue (these have no dependencies).
 * 4. BFS Traversal:
 * - Pop `node` from queue, append it to `topo` result list.
 * - For every adjacent vertex `it` reachable from `node`:
 * - Decrement its in-degree: `indegree[it]--`.
 * - If `indegree[it] == 0`, all its prerequisites have been processed; push `it` into queue.
 * 5. Cycle Detection Note:
 * - If `topo.size() < V`, the graph contains a directed cycle (Kahn's algorithm fails to process cyclic nodes).
 * * Time Complexity:  O(V + E) - Visits each vertex once and decrements in-degree across every directed edge once.
 * Space Complexity: O(V)     - For indegree array, queue, and topological output container.
 */

#include <iostream>
#include <vector>
#include <queue>

using namespace std;

class Solution {
public:
    // Function to return list containing vertices in Topological order.
    vector<int> topoSort(int V, vector<int> adj[]) {
        int indegree[V] = {0};

        // Step 1: Calculate in-degree for each node
        for (int i = 0; i < V; i++) {
            for (auto it : adj[i]) {
                indegree[it]++;
            }
        }

        // Step 2: Push all nodes with in-degree 0 into the queue
        queue<int> q;
        for (int i = 0; i < V; i++) {
            if (indegree[i] == 0) {
                q.push(i);
            }
        }

        // Step 3: Standard BFS processing
        vector<int> topo;
        while (!q.empty()) {
            int node = q.front();
            q.pop();
            topo.push_back(node);

            // Node is in topo sort, remove it from outgoing dependencies
            for (auto it : adj[node]) {
                indegree[it]--;
                if (indegree[it] == 0) {
                    q.push(it);
                }
            }
        }

        return topo;
    }
};

// 🔹 Driver Code
int main() {
    /*
        Directed Graph (DAG):
        5 -> 0, 5 -> 2
        4 -> 0, 4 -> 1
        2 -> 3
        3 -> 1
        
        Valid Topological Sort: 4 5 2 3 1 0 (or 5 4 2 3 1 0)
    */

    int V = 6;
    vector<int> adj[6];
    adj[5].push_back(0);
    adj[5].push_back(2);
    adj[4].push_back(0);
    adj[4].push_back(1);
    adj[2].push_back(3);
    adj[3].push_back(1);

    Solution obj;
    vector<int> result = obj.topoSort(V, adj);

    cout << "Topological Sort (Kahn's Algorithm):\n";
    for (int node : result) {
        cout << node << " ";
    }
    cout << endl;

    return 0;
}