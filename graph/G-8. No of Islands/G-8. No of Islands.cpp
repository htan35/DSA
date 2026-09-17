/*
 * Problem: Number of Islands (8-Directional Connected Components) - GFG
 * -------------------------------------------------------------------
 * Approach: Breadth-First Search (BFS) with 8-Directional Traversal
 * * Approach Explanation:
 * 1. An island consists of a group of connected land cells ('1') surrounded by water ('0').
 * In this variant (GeeksforGeeks), cells connect in all 8 directions (horizontal, vertical, diagonal).
 * 2. Maintain a 2D `vis` array initialized to 0 to keep track of visited cells.
 * 3. Outer Nested Loops:
 * - Scan every cell `(row, col)` in the `n x m` grid.
 * - If a cell contains `'1'` and is not visited (`!vis[row][col]`), a new island is found:
 * - Increment island counter `cnt++`.
 * - Trigger `bfs(row, col, vis, grid)` to visit and mark all 8-directionally connected land cells.
 * 4. BFS Traversal:
 * - Push the starting cell into a queue `q` of pairs `{row, col}` and mark `vis[row][col] = 1`.
 * - While the queue is not empty:
 * - Pop `{row, col}`.
 * - Loop `delrow` from -1 to 1 and `delcol` from -1 to 1 to cover all 8 surrounding neighbors:
 * - Compute `nrow = row + delrow` and `ncol = col + delcol`.
 * - Check boundary conditions: `nrow >= 0 && nrow < n && ncol >= 0 && ncol < m`.
 * - If valid, unvisited, and is land (`grid[nrow][ncol] == '1' && !vis[nrow][ncol]`):
 * - Mark `vis[nrow][ncol] = 1`.
 * - Push `{nrow, ncol}` into the queue.
 * * Note:
 * - On LeetCode 200, islands are strictly 4-directional (up, down, left, right).
 * On GeeksforGeeks, islands are defined by 8-directional connectivity (as implemented here).
 * * Time Complexity:  O(N * M) - Every cell is visited at most a constant number of times (evaluated in 8 directions).
 * Space Complexity: O(N * M) - For the 2D `vis` vector and the BFS queue storing at most O(N * M) elements.
 */

#include <iostream>
#include <vector>
#include <queue>

using namespace std;

class Solution {
private:
    void bfs(int row, int col, vector<vector<int>> &vis, vector<vector<char>> &grid) {
        vis[row][col] = 1;
        queue<pair<int, int>> q;
        q.push({row, col});
        int n = grid.size();
        int m = grid[0].size();

        while (!q.empty()) {
            int r = q.front().first;
            int c = q.front().second;
            q.pop();

            // Traverse in the 8 neighbors and mark them if it's land
            for (int delrow = -1; delrow <= 1; delrow++) {
                for (int delcol = -1; delcol <= 1; delcol++) {
                    int nrow = r + delrow;
                    int ncol = c + delcol;

                    if (nrow >= 0 && nrow < n && ncol >= 0 && ncol < m
                        && grid[nrow][ncol] == '1' && !vis[nrow][ncol]) {
                        vis[nrow][ncol] = 1;
                        q.push({nrow, ncol});
                    }
                }
            }
        }
    }

public:
    // Function to find the number of islands.
    int numIslands(vector<vector<char>>& grid) {
        int n = grid.size();
        int m = grid[0].size();
        vector<vector<int>> vis(n, vector<int>(m, 0));
        int cnt = 0;

        for (int row = 0; row < n; row++) {
            for (int col = 0; col < m; col++) {
                if (!vis[row][col] && grid[row][col] == '1') {
                    cnt++;
                    bfs(row, col, vis, grid);
                }
            }
        }

        return cnt;
    }
};

// 🔹 Driver Code
int main() {
    /*
        Grid (8-directional connectivity):
        0 1 1 1 0 0 0
        0 0 1 1 0 1 0

        Because (0, 2) and (1, 5) connect via diagonal paths:
        (0,3) -> (1,5) [diagonal/connected via intermediate cells]
    */

    vector<vector<char>> grid = {
        {'0', '1', '1', '1', '0', '0', '0'},
        {'0', '0', '1', '1', '0', '1', '0'}
    };

    Solution obj;
    cout << "Total number of islands: " << obj.numIslands(grid) << endl;

    return 0;
}