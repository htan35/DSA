// Weighted Adjacency List to Matrix
#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    // Returns a V x V matrix filled with weights
    vector<vector<int>> weightedAdjacencyListToMatrix(int V, vector<vector<pair<int, int>>>& adjList) {
        // Initialize a V x V matrix filled with 0 (denoting no edge)
        vector<vector<int>> adjMatrix(V, vector<int>(V, 0));

        for (int i = 0; i < V; i++) {
            for (auto edge : adjList[i]) {
                int neighbor = edge.first;
                int weight = edge.second;
                adjMatrix[i][neighbor] = weight; 
            }
        }
        return adjMatrix;
    }
};

int main() {
    int V = 3;
    // Example Input: Weighted adjacency list
    // 0 -> {1, wt: 5}, {2, wt: 2}
    // 1 -> {0, wt: 5}
    // 2 -> {0, wt: 2}
    vector<vector<pair<int, int>>> adjList = {
        {{1, 5}, {2, 2}},
        {{0, 5}},
        {{0, 2}}
    };

    Solution sol;
    vector<vector<int>> adjMatrix = sol.weightedAdjacencyListToMatrix(V, adjList);

    cout << "--- Weighted Adjacency Matrix ---" << endl;
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            cout << adjMatrix[i][j] << " ";
        }
        cout << endl;
    }
    return 0;
}