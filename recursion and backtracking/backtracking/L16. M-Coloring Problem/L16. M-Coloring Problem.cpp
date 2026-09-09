/*
 * Problem: M-Coloring Problem (Backtracking)
 * -------------------------------------------
 * Approach: Backtracking vertex-by-vertex trying colors from 1 to M
 * 
 * Approach Explanation:
 * 1. The goal is to determine if the graph can be colored using at most M colors 
 *    such that no two adjacent vertices share the same color.
 * 2. Helper `isSafe(node, color, graph, n, col)`:
 *    - Checks if any adjacent neighbor `k` of `node` already has color `col`.
 *    - Iterates `k` from `0` to `n - 1`: if an edge exists (`graph[k][node] == 1` or `graph[node][k] == 1`)
 *      and `color[k] == col`, return false. Otherwise, return true.
 * 3. Recursive Solver `solve(node, color, m, N, graph)`:
 *    - Base Case: When `node == N`, all vertices have been assigned a valid color -> return true.
 *    - Loop through colors `i` from `1` to `m`:
 *        a. If `isSafe(node, color, graph, N, i)` is true:
 *           - Assign `color[node] = i`.
 *           - Recurse for the next node: `solve(node + 1, color, m, N, graph)`.
 *           - If it returns true, propagate `true` immediately.
 *           - Backtrack: reset `color[node] = 0`.
 *    - If no color from `1` to `m` works for this node, return false.
 * 
 * Time Complexity:  O(M^N) - In the worst case, we try M colors for each of the N vertices.
 * Space Complexity: O(N)   - For the color array and the recursion call stack.
 */

#include <iostream>
#include <vector>

using namespace std;

class Solution {
private:
    bool isSafe(int node, int color[], bool graph[101][101], int n, int col) {
        for (int k = 0; k < n; k++) {
            if (k != node && graph[k][node] == 1 && color[k] == col) {
                return false;
            }
        }
        return true;
    }

    bool solve(int node, int color[], int m, int N, bool graph[101][101]) {
        // Base Case: All vertices colored successfully
        if (node == N) {
            return true;
        }

        // Try assigning colors 1 through m
        for (int i = 1; i <= m; i++) {
            if (isSafe(node, color, graph, N, i)) {
                color[node] = i;

                if (solve(node + 1, color, m, N, graph)) 
                    return true;

                // Backtrack
                color[node] = 0;
            }
        }

        return false;
    }

public:
    // Function to determine if graph can be coloured with at most M colours
    // such that no two adjacent vertices of graph are coloured with same colour.
    bool graphColoring(bool graph[101][101], int m, int N) {
        int color[N] = {0};

        if (solve(0, color, m, N, graph)) 
            return true;

        return false;
    }
};

// 🔹 Driver Code
int main() {
    /*
        Triangle graph (K3) + 1 extra connected node:
        0 --- 1
         \   /
           2 --- 3

        Can it be colored with M = 3 colors? Yes.
        Can it be colored with M = 2 colors? No (contains odd cycle of length 3).
    */

    int N = 4;
    int m = 3;
    bool graph[101][101] = {false};

    // Edges: (0-1), (1-2), (2-0), (2-3)
    graph[0][1] = graph[1][0] = true;
    graph[1][2] = graph[2][1] = true;
    graph[2][0] = graph[0][2] = true;
    graph[2][3] = graph[3][2] = true;

    Solution obj;
    if (obj.graphColoring(graph, m, N)) {
        cout << "Graph can be colored with at most " << m << " colors." << endl;
    } else {
        cout << "Graph cannot be colored with at most " << m << " colors." << endl;
    }

    return 0;
}
