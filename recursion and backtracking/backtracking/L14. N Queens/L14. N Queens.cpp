/*
 * Problem: N-Queens (LeetCode 51)
 * --------------------------------
 * Approach: Backtracking column by column with direction checks (Approach 1)
 * 
 * Approach Explanation:
 * 1. Place queens column-by-column from left to right (col: 0 -> n - 1).
 * 2. Because queens are placed from left to right, any threat to `(row, col)` 
 *    can ONLY come from the left side:
 *    - Upper-left diagonal: `(row - 1, col - 1)` up to `(0, 0)`
 *    - Direct left row: `(row, col - 1)` down to `(row, 0)`
 *    - Lower-left diagonal: `(row + 1, col - 1)` down to `(n - 1, 0)`
 *    - No need to check right directions or same-column threats.
 * 3. Base Case:
 *    - If `col == n`, all n queens have been placed safely -> add current board to `ans`.
 * 4. Backtracking:
 *    - Try placing 'Q' at `board[row][col]`.
 *    - Recurse for `col + 1`.
 *    - Reset `board[row][col] = '.'` before testing the next row.
 * 
 * Time Complexity:  O(N! * N) - At each step we test up to N rows and check safety in O(N).
 * Space Complexity: O(N^2)    - For storing the board states and recursion stack depth O(N).
 */

#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Solution {
public:
    // Helper function to check if placing a queen at board[row][col] is valid
    bool isSafe1(int row, int col, vector<string>& board, int n) {
        int duprow = row;
        int dupcol = col;

        // 1. Check upper-left diagonal
        while (row >= 0 && col >= 0) {
            if (board[row][col] == 'Q') return false;
            row--;
            col--;
        }

        // 2. Check straight left horizontal row
        col = dupcol;
        row = duprow;
        while (col >= 0) {
            if (board[row][col] == 'Q') return false;
            col--;
        }

        // 3. Check lower-left diagonal
        row = duprow;
        col = dupcol;
        while (row < n && col >= 0) {
            if (board[row][col] == 'Q') return false;
            row++;
            col--;
        }

        return true;
    }

    void solve(int col, vector<string>& board, vector<vector<string>>& ans, int n) {
        // Base Case: successfully placed queens in all n columns
        if (col == n) {
            ans.push_back(board);
            return;
        }

        // Try placing a queen in each row of the current column
        for (int row = 0; row < n; row++) {
            if (isSafe1(row, col, board, n)) {
                board[row][col] = 'Q';
                solve(col + 1, board, ans, n);
                board[row][col] = '.'; // Backtrack
            }
        }
    }

    vector<vector<string>> solveNQueens(int n) {
        vector<vector<string>> ans;
        vector<string> board(n);
        string s(n, '.');

        for (int i = 0; i < n; i++) {
            board[i] = s;
        }

        solve(0, board, ans, n);
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
