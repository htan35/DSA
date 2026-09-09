/*
 * Problem: Sudoku Solver (LeetCode 37)
 * -------------------------------------
 * Approach: Recursive Backtracking with Single-Loop Subgrid Validation
 * 
 * Approach Explanation:
 * 1. `solve(board)`:
 *    - Scans the 9x9 board cell by cell looking for an empty spot (`'.'`).
 *    - For an empty cell `(i, j)`, attempts to place characters `'1'` through `'9'`.
 *    - Uses `isValid(board, i, j, c)` to check if character `c` can legally be placed:
 *        a. Row check: `board[row][i] == c`
 *        b. Column check: `board[i][col] == c`
 *        c. 3x3 Sub-box check: `board[3 * (row / 3) + i / 3][3 * (col / 3) + i % 3] == c`
 *           All 3 checks are performed simultaneously inside a single loop from `0` to `8`.
 *    - If valid, places `c` at `board[i][j]` and makes the recursive call `solve(board)`.
 *    - If that choice leads to a full solution, immediately returns `true` (stops early).
 *    - If that branch fails, backtracks by resetting `board[i][j] = '.'`.
 *    - If no digit from `'1'` to `'9'` fits, returns `false` to trigger backtracking.
 *    - If every cell is filled without conflict, returns `true`.
 * 
 * Time Complexity:  O(9^(empty cells)) - In the worst case, evaluates up to 9 options per empty cell.
 * Space Complexity: O(1) auxiliary space (or O(81) max recursion stack depth).
 */

#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    void solveSudoku(vector<vector<char>>& board) {
        solve(board);
    }

    bool solve(vector<vector<char>>& board) {
        for (int i = 0; i < board.size(); i++) {
            for (int j = 0; j < board[0].size(); j++) {
                if (board[i][j] == '.') {
                    for (char c = '1'; c <= '9'; c++) {
                        if (isValid(board, i, j, c)) {
                            board[i][j] = c;

                            if (solve(board) == true)
                                return true;
                            else
                                board[i][j] = '.'; // Backtrack
                        }
                    }
                    return false;
                }
            }
        }
        return true;
    }

    bool isValid(vector<vector<char>>& board, int row, int col, char c) {
        for (int i = 0; i < 9; i++) {
            // Check column
            if (board[i][col] == c)
                return false;

            // Check row
            if (board[row][i] == c)
                return false;

            // Check 3x3 sub-box
            if (board[3 * (row / 3) + i / 3][3 * (col / 3) + i % 3] == c)
                return false;
        }
        return true;
    }
};

// 🔹 Driver Code
int main() {
    vector<vector<char>> board = {
        {'5', '3', '.', '.', '7', '.', '.', '.', '.'},
        {'6', '.', '.', '1', '9', '5', '.', '.', '.'},
        {'.', '9', '8', '.', '.', '.', '.', '6', '.'},
        {'8', '.', '.', '.', '6', '.', '.', '.', '3'},
        {'4', '.', '.', '8', '.', '3', '.', '.', '1'},
        {'7', '.', '.', '.', '2', '.', '.', '.', '6'},
        {'.', '6', '.', '.', '.', '.', '2', '8', '.'},
        {'.', '.', '.', '4', '1', '9', '.', '.', '5'},
        {'.', '.', '.', '.', '8', '.', '.', '7', '9'}
    };

    Solution solver;
    solver.solveSudoku(board);

    cout << "Solved Sudoku Board:\n";
    for (int r = 0; r < 9; r++) {
        for (int c = 0; c < 9; c++) {
            cout << board[r][c] << " ";
        }
        cout << "\n";
    }

    return 0;
}
