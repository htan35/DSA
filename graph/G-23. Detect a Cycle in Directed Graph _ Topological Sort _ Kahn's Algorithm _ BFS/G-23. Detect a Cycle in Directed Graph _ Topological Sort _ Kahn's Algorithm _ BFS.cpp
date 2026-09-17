/*
 * Problem: Detect Cycle in a Directed Graph (BFS / Kahn's Algorithm)
 * ------------------------------------------------------------------
 * Approach: In-degree Array + Queue Count Verification
 * * Approach Explanation:
 * 1. Kahn's Algorithm (Topological Sort via BFS) can only produce an ordering of size V 
 * if and only if the graph is a Directed Acyclic Graph (DAG).
 * 2. If a directed graph contains a cycle:
 * - Vertices involved in the cycle (and those reachable only through them) will never reach 
 * an in-degree of 0.
 * - Consequently, they will never enter the queue.
 * 3. Algorithm:
 * - Calculate in-degrees for all V vertices.
 * - Push all nodes with `indegree == 0` into the queue.
 * - Maintain a counter `cnt = 0`.
 * - While the queue is not empty:
 * - Pop `node`, increment `cnt++`.
 * - For each outgoing neighbor `it`:
 * - Decrement `indegree[it]--`.
 * - If `indegree[it] == 0`, push `it` into the queue.
 * 4. Cycle Condition:
 * - If `cnt == V`: all nodes were processed -> graph is a DAG (No Cycle, return false).
 * - If `cnt < V`: some nodes were skipped due to cyclic dependencies -> Cycle exists (return true).
 * * Time Complexity:  O(V + E) - Visits every vertex once and decrements along every directed edge once.
 * Space Complexity: O(V)     - For `indegree` array and the BFS queue.
 */

#include <iostream>
#include <vector>
#include <queue>

using namespace std;

class Solution {
public:
    // Function to detect cycle in a directed graph.
    bool isCyclic(int V, vector<int> adj[]) {
        int indegree[V] = {0};

        // Step 1: Calculate in-degrees of all vertices
        for (int i = 0; i < V; i++) {
            for (auto it : adj[i]) {
                indegree[it]++;
            }
        }

        // Step 2: Push vertices with 0 in-degree into the queue
        queue<int> q;
        for (int i = 0; i < V; i++) {
            if (indegree[i] == 0) {
                q.push(i);
            }
        }

        int cnt = 0; // Tracks number of visited nodes in topological order

        // Step 3: BFS processing
        while (!q.empty()) {
            int node = q.front();
            q.pop();
            cnt++;

            // Node is processed; reduce in-degree of adjacent nodes
            for (auto it : adj[node]) {
                indegree[it]--;
                if (indegree[it] == 0) {
                    q.push(it);
                }
            }
        }

        // If topological sort includes all V vertices, it's a DAG (no cycle)
        if (cnt == V) return false;

        // Otherwise, a cycle exists
        return true;
    }
};

// 🔹 Driver Code
int main() {
    /*
        Test Graph 1 (Contains Cycle):
        0 -> 1 -> 2 -> 0
    */
    int V1 = 3;
    vector<int> adj1[3];
    adj1[0].push_back(1);
    adj1[1].push_back(2);
    adj1[2].push_back(0);

    Solution obj;
    cout << "Graph 1 has cycle: " << (obj.isCyclic(V1, adj1) ? "Yes" : "No") << "\n";

    /*
        Test Graph 2 (Acyclic - DAG):
        0 -> 1 -> 2
    */
    int V2 = 3;
    vector<int> adj2[3];
    adj2[0].push_back(1);
    adj2[1].push_back(2);

    cout << "Graph 2 has cycle: " << (obj.isCyclic(V2, adj2) ? "Yes" : "No") << "\n";

    return 0;
}