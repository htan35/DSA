/*
 * Problem: N-Queens (LeetCode 51)
 * --------------------------------
 * Approach: Optimized Backtracking with Hash Arrays / Lookup Tables (Approach 2)
 * 
 * Approach Explanation:
 * 1. Replaces the O(N) directional while-loops of isSafe() with O(1) hash lookups:
 *    - `leftRow[row]`: Tracks horizontal row occupancy (size n).
 *    - `lowerDiagonal[row + col]`: Across any anti-diagonal (bottom-left to top-right), 
 *      the sum `(row + col)` remains invariant. Range: [0, 2n - 2], size: `2n - 1`.
 *    - `upperDiagonal[(n - 1) + (col - row)]`: Across any main diagonal (top-left to bottom-right), 
 *      the difference `(col - row)` is constant. Adding `(n - 1)` maps negative values into 
 *      valid indices in the range [0, 2n - 2], size: `2n - 1`.
 * 2. `solve(...)`:
 *    - Base Case: `col == n` means a full, valid board configuration is reached -> store into `ans`.
 *    - For each `row` in `col`, check if all 3 hash entries are `0`.
 *    - If valid, mark all three as `1`, place `'Q'`, and recurse for `col + 1`.
 *    - Backtrack: reset `'Q'` to `'.'` and all 3 hash entries back to `0`.
 * 
 * Time Complexity:  O(N!) - Checking validity at each step drops from O(N) down to O(1).
 * Space Complexity: O(N)  - Auxiliary space for recursion call stack and hash vectors.
 */

#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Solution {
public:
    void solve(int col, vector<string> &board, vector<vector<string>> &ans,
               vector<int> &leftRow,
               vector<int> &upperDiagonal, vector<int> &lowerDiagonal, int n) {
        if (col == n) {
            ans.push_back(board);
            return;
        }

        for (int row = 0; row < n; row++) {
            if (leftRow[row] == 0 && lowerDiagonal[row + col] == 0 
                && upperDiagonal[n - 1 + col - row] == 0) {
                
                board[row][col] = 'Q';
                leftRow[row] = 1;
                lowerDiagonal[row + col] = 1;
                upperDiagonal[n - 1 + col - row] = 1;

                solve(col + 1, board, ans, leftRow, upperDiagonal, lowerDiagonal, n);

                // Backtrack
                board[row][col] = '.';
                leftRow[row] = 0;
                lowerDiagonal[row + col] = 0;
                upperDiagonal[n - 1 + col - row] = 0;
            }
        }
    }

public:
    vector<vector<string>> solveNQueens(int n) {
        vector<vector<string>> ans;
        vector<string> board(n);
        string s(n, '.');
        for (int i = 0; i < n; i++) {
            board[i] = s;
        }

        vector<int> leftRow(n, 0);
        vector<int> upperDiagonal(2 * n - 1, 0);
        vector<int> lowerDiagonal(2 * n - 1, 0);

        solve(0, board, ans, leftRow, upperDiagonal, lowerDiagonal, n);
        return ans;
    }
};

// 🔹 Driver Code
int main() {
    int n = 4;
    Solution obj;
    vector<vector<string>> solutions = obj.solveNQueens(n);

    cout << "Total distinct solutions for " << n << "-Queens: " << solutions.size() << "\n\n";
    for (size_t k = 0; k < solutions.size(); k++) {
        cout << "Configuration " << k + 1 << ":\n";
        for (const string& row : solutions[k]) {
            cout << row << "\n";
        }
        cout << "\n";
    }

    return 0;
}
