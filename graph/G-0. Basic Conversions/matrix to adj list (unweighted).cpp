// Unweighted Matrix to Adjacency List
#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    // LeetCode-style function interface
    vector<vector<int>> matrixToAdjacencyList(vector<vector<int>>& adjMatrix) {
        int V = adjMatrix.size(); // Number of vertices is determined by row count
        vector<vector<int>> adjList(V);

        for (int i = 0; i < V; i++) {
            for (int j = 0; j < V; j++) {
                // If an edge exists and it's not a self-loop (optional check depending on problem constraints)
                if (adjMatrix[i][j] == 1 && i != j) {
                    adjList[i].push_back(j);
                }
            }
        }
        return adjList;
    }
};

int main() {
    // Example LeetCode Input format: A 3x3 unweighted graph matrix
    vector<vector<int>> adjMatrix = {
        {0, 1, 1},
        {1, 0, 0},
        {1, 0, 0}
    };

    Solution sol;
    vector<vector<int>> adjList = sol.matrixToAdjacencyList(adjMatrix);

    // Print the Adjacency List to verify output
    cout << "--- Unweighted Adjacency List ---" << endl;
    for (int i = 0; i < adjList.size(); i++) {
        cout << i << " -> ";
        for (int neighbor : adjList[i]) {
            cout << neighbor << " ";
        }
        cout << endl;
    }
    return 0;
}