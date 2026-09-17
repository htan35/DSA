/*
 * Problem: Strongly Connected Components (Kosaraju's Algorithm)
 * ------------------------------------------------------------
 * Approach: 3-Step DFS with Graph Transposition & SCC Extraction
 * 
 * Approach Explanation:
 * 1. A Strongly Connected Component (SCC) is a maximal subgraph where every vertex
 *    is reachable from every other vertex in that subgraph.
 * 2. Step 1 - Topological Sorting by Finish Time:
 *    - Run standard DFS on the original graph.
 *    - Push nodes to a stack `st` as their DFS finishes. The node with the latest 
 *      finishing time stays on top of the stack.
 * 3. Step 2 - Graph Transposition / Edge Reversal:
 *    - Construct a reversed graph `adjT`, reversing every directed edge `u -> v` to `v -> u`.
 *    - Reversing edges isolates each SCC: paths within an SCC remain connected, 
 *      but paths between different SCCs are severed.
 * 4. Step 3 - Traversal on Reversed Graph:
 *    - Reset the visited array to 0.
 *    - Pop nodes from `st` one by one. If an unvisited node is found:
 *        a. Increment `scc` counter.
 *        b. Run `dfs3` on `adjT` from this node. Every vertex reached during this specific
 *           `dfs3` run belongs exclusively to the current SCC.
 *        c. To print/store: collect all nodes encountered during this `dfs3` call into a list.
 * 
 * Time Complexity:  O(V + E) - Three linear passes: DFS1 + Graph Reversal + DFS2.
 * Space Complexity: O(V + E) - Stack O(V), visited array O(V), and transposed graph O(V + E).
 */

#include <iostream>
#include <vector>
#include <stack>

using namespace std;

class Solution {
private:
    // Step 1: DFS to sort vertices by finishing time
    void dfs(int node, vector<int>& vis, vector<int> adj[], stack<int>& st) {
        vis[node] = 1;
        for (auto it : adj[node]) {
            if (!vis[it]) {
                dfs(it, vis, adj, st);
            }
        }
        st.push(node);
    }

    // Step 3: DFS on transposed graph to collect nodes belonging to the current SCC
    void dfs3(int node, vector<int>& vis, vector<int> adjT[], vector<int>& currentSCC) {
        vis[node] = 1;
        currentSCC.push_back(node); // Store node for printing
        for (auto it : adjT[node]) {
            if (!vis[it]) {
                dfs3(it, vis, adjT, currentSCC);
            }
        }
    }

public:
    // Function to find the number of SCCs and retrieve all component groups
    pair<int, vector<vector<int>>> kosaraju(int V, vector<int> adj[]) {
        vector<int> vis(V, 0);
        stack<int> st;

        // Step 1: Order vertices by finishing times
        for (int i = 0; i < V; i++) {
            if (!vis[i]) {
                dfs(i, vis, adj, st);
            }
        }

        // Step 2: Transpose the graph (reverse all directed edges)
        vector<int> adjT[V];
        for (int i = 0; i < V; i++) {
            vis[i] = 0; // Re-use vis array for Step 3
            for (auto it : adj[i]) {
                adjT[it].push_back(i); // Reverse edge: i -> it becomes it -> i
            }
        }

        // Step 3: DFS on transposed graph in order of finishing times
        int sccCount = 0;
        vector<vector<int>> allSCCs;

        while (!st.empty()) {
            int node = st.top();
            st.pop();

            if (!vis[node]) {
                sccCount++;
                vector<int> currentSCC;
                dfs3(node, vis, adjT, currentSCC);
                allSCCs.push_back(currentSCC);
            }
        }

        return {sccCount, allSCCs};
    }
};

// 🔹 Driver Code
int main() {
    /*
        Directed Graph:
        0 -> 2, 0 -> 3
        1 -> 0
        2 -> 1
        3 -> 4
        
        Components:
        SCC 1: {0, 1, 2} (forms a cycle)
        SCC 2: {3}
        SCC 3: {4}
    */

    int V = 5;
    vector<int> adj[5];
    adj[0].push_back(2);
    adj[0].push_back(3);
    adj[1].push_back(0);
    adj[2].push_back(1);
    adj[3].push_back(4);

    Solution obj;
    pair<int, vector<vector<int>>> result = obj.kosaraju(V, adj);

    cout << "Total Strongly Connected Components: " << result.first << "\n\n";
    cout << "The SCC groups are:\n";
    for (size_t i = 0; i < result.second.size(); i++) {
        cout << "Component " << i + 1 << ": [ ";
        for (int node : result.second[i]) {
            cout << node << " ";
        }
        cout << "]\n";
    }

    return 0;
}