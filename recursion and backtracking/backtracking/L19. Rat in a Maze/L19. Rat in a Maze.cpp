/*
 * Problem: Rat in a Maze Problem - I (Explicit 4-Directional Branches)
 * ------------------------------------------------------------------
 * Approach: Backtracking with Separate Conditionals for D, L, R, U
 * 
 * Approach Explanation:
 * 1. The goal is to reach destination cell (n - 1, n - 1) starting from (0, 0).
 * 2. To ensure alphabetical (lexicographical) ordering of generated paths:
 *    - Down:  (i + 1, j) with character 'D'
 *    - Left:  (i, j - 1) with character 'L'
 *    - Right: (i, j + 1) with character 'R'
 *    - Up:    (i - 1, j) with character 'U'
 * 3. Before each recursive branch:
 *    - Check bounds (row, col within [0, n - 1]).
 *    - Check visited state (`!vis[next_row][next_col]`).
 *    - Check path validity (`a[next_row][next_col] == 1`).
 * 4. Backtracking:
 *    - Set `vis[i][j] = 1` before branching into valid directions.
 *    - Reset `vis[i][j] = 0` immediately after returning from each branch.
 * 
 * Note on Comparison:
 * - This approach explicitly handles each direction using separate `if` blocks.
 * - The delta-array approach (`di[]`, `dj[]`, string `"DLRU"`) refactors these 
 *   4 blocks into a single clean loop, avoiding repeated boilerplate.
 * 
 * Time Complexity:  O(4^(N^2)) - Worst case exploring all 4 paths across the grid.
 * Space Complexity: O(N^2)     - Matrix for visited states and auxiliary recursion stack.
 */

#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Solution {
    void solve(int i, int j, vector<vector<int>> &a, int n, vector<string> &ans, 
               string move, vector<vector<int>> &vis) {
        // Base Case: Target reached
        if (i == n - 1 && j == n - 1) {
            ans.push_back(move);
            return;
        }

        // 1. Downward ('D')
        if (i + 1 < n && !vis[i + 1][j] && a[i + 1][j] == 1) {
            vis[i][j] = 1;
            solve(i + 1, j, a, n, ans, move + 'D', vis);
            vis[i][j] = 0; // Backtrack
        }

        // 2. Left ('L')
        if (j - 1 >= 0 && !vis[i][j - 1] && a[i][j - 1] == 1) {
            vis[i][j] = 1;
            solve(i, j - 1, a, n, ans, move + 'L', vis);
            vis[i][j] = 0; // Backtrack
        }

        // 3. Right ('R')
        if (j + 1 < n && !vis[i][j + 1] && a[i][j + 1] == 1) {
            vis[i][j] = 1;
            solve(i, j + 1, a, n, ans, move + 'R', vis);
            vis[i][j] = 0; // Backtrack
        }

        // 4. Upward ('U')
        if (i - 1 >= 0 && !vis[i - 1][j] && a[i - 1][j] == 1) {
            vis[i][j] = 1;
            solve(i - 1, j, a, n, ans, move + 'U', vis);
            vis[i][j] = 0; // Backtrack
        }
    }

public:
    vector<string> findPath(vector<vector<int>> &m, int n) {
        vector<string> ans;
        vector<vector<int>> vis(n, vector<int>(n, 0));

        // Start only if source cell is passable
        if (m[0][0] == 1) {
            solve(0, 0, m, n, ans, "", vis);
        }

        return ans;
    }
};

// 🔹 Driver Code
int main() {
    /*
        Grid:
        1 0 0 0
        1 1 0 1
        1 1 0 0
        0 1 1 1

        Paths found: "DDRDRR", "DRDDRR"
    */

    int n = 4;
    vector<vector<int>> m = {
        {1, 0, 0, 0},
        {1, 1, 0, 1},
        {1, 1, 0, 0},
        {0, 1, 1, 1}
    };

    Solution obj;
    vector<string> paths = obj.findPath(m, n);

    if (paths.empty()) {
        cout << "No path found." << endl;
    } else {
        cout << "Valid paths in lexicographical order:\n";
        for (const string &p : paths) {
            cout << p << "\n";
        }
    }

    return 0;
}
