// Weighted Matrix to Adjacency List
#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    // Returns list where adjList[i] = list of pairs {neighbor, weight}
    vector<vector<pair<int, int>>> weightedMatrixToAdjacencyList(vector<vector<int>>& adjMatrix) {
        int V = adjMatrix.size();
        vector<vector<pair<int, int>>> adjList(V);

        for (int i = 0; i < V; i++) {
            for (int j = 0; j < V; j++) {
                // Assuming 0 means no connection, and non-zero values represent weights
                if (adjMatrix[i][j] != 0 && i != j) {
                    adjList[i].push_back({j, adjMatrix[i][j]});
                }
            }
        }
        return adjList;
    }
};

int main() {
    // Example LeetCode Input format: A 3x3 weighted graph matrix
    vector<vector<int>> adjMatrix = {
        {0, 5, 2},
        {5, 0, 0},
        {2, 0, 0}
    };

    Solution sol;
    vector<vector<pair<int, int>>> adjList = sol.weightedMatrixToAdjacencyList(adjMatrix);

    cout << "--- Weighted Adjacency List ---" << endl;
    for (int i = 0; i < adjList.size(); i++) {
        cout << i << " -> ";
        for (auto edge : adjList[i]) {
            cout << "(" << edge.first << ", wt: " << edge.second << ") ";
        }
        cout << endl;
    }
    return 0;
}