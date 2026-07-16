// Unweighted Adjacency List to Matrix
#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    // LeetCode-style function interface
    vector<vector<int>> adjacencyListToMatrix(int V, vector<vector<int>>& adjList) {
        // Initialize a V x V matrix filled with 0s
        vector<vector<int>> adjMatrix(V, vector<int>(V, 0));

        for (int i = 0; i < V; i++) {
            for (int neighbor : adjList[i]) {
                adjMatrix[i][neighbor] = 1; // Set edge link to 1
            }
        }
        return adjMatrix;
    }
};

int main() {
    int V = 3;
    // Example Input: Adjacency list representation
    // 0 -> 1, 2
    // 1 -> 0
    // 2 -> 0
    vector<vector<int>> adjList = {
        {1, 2},
        {0},
        {0}
    };

    Solution sol;
    vector<vector<int>> adjMatrix = sol.adjacencyListToMatrix(V, adjList);

    cout << "--- Unweighted Adjacency Matrix ---" << endl;
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            cout << adjMatrix[i][j] << " ";
        }
        cout << endl;
    }
    return 0;
}