/*
 * Problem: Rat in a Maze Problem - I (GFG)
 * ----------------------------------------
 * Approach: Backtracking with Direction Vectors in Lexicographical Order ("DLRU")
 * 
 * Approach Explanation:
 * 1. The rat starts at cell (0, 0) and wants to reach destination (n - 1, n - 1).
 *    A cell with value 1 is passable, while 0 is blocked.
 * 2. Lexicographical Order Requirement:
 *    - To generate paths naturally in sorted order without needing post-sort:
 *      Order moves strictly as: Down ('D'), Left ('L'), Right ('R'), Up ('U').
 *    - Direction vectors:
 *        `di[] = {+1,  0,  0, -1}`
 *        `dj[] = { 0, -1, +1,  0}`
 * 3. Base Case:
 *    - When `i == n - 1 && j == n - 1`, target is reached -> push `move` string to `ans`.
 * 4. Movement & Backtracking:
 *    - Check for boundary limits: `nexti >= 0 && nextj >= 0 && nexti < n && nextj < n`.
 *    - Check valid path: `!vis[nexti][nextj] && a[nexti][nextj] == 1`.
 *    - Mark `vis[i][j] = 1`, make recursive call with `move + dir[ind]`, and backtrack `vis[i][j] = 0`.
 * 5. Edge Case Check:
 *    - If start cell `m[0][0] == 0` or target cell `m[n-1][n-1] == 0`, no valid path exists.
 * 
 * Time Complexity:  O(4^(N^2)) - Worst-case exploring 4 directions at each cell.
 * Space Complexity: O(N^2)     - Visited matrix and auxiliary recursion stack depth.
 */

#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Solution {
    void solve(int i, int j, vector<vector<int>> &a, int n, vector<string> &ans, string move,
               vector<vector<int>> &vis, int di[], int dj[]) {
        // Base Case: Reached bottom-right cell
        if (i == n - 1 && j == n - 1) {
            ans.push_back(move);
            return;
        }

        // Ordered strictly lexicographically: Down, Left, Right, Up
        string dir = "DLRU";
        for (int ind = 0; ind < 4; ind++) {
            int nexti = i + di[ind];
            int nextj = j + dj[ind];

            // Boundary checks and validity check
            if (nexti >= 0 && nextj >= 0 && nexti < n && nextj < n && !vis[nexti][nextj] && a[nexti][nextj] == 1) {
                vis[i][j] = 1;
                solve(nexti, nextj, a, n, ans, move + dir[ind], vis, di, dj);
                vis[i][j] = 0; // Backtrack
            }
        }
    }

public:
    vector<string> findPath(vector<vector<int>> &m, int n) {
        vector<string> ans;
        vector<vector<int>> vis(n, vector<int>(n, 0));
        
        // Direction offsets corresponding to 'D', 'L', 'R', 'U'
        int di[] = {+1, 0, 0, -1};
        int dj[] = {0, -1, 1, 0};

        // If starting cell is blocked, no path can exist
        if (m[0][0] == 1) {
            solve(0, 0, m, n, ans, "", vis, di, dj);
        }

        return ans;
    }
};

// 🔹 Driver Code
int main() {
    /*
        Maze:
        1 0 0 0
        1 1 0 1
        1 1 0 0
        0 1 1 1

        Expected paths:
        "DDRDRR", "DRDDRR"
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
