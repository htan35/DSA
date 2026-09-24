/*
 * Problem: Grid Unique Paths (LeetCode 62 / DP 8)
 * -----------------------------------------------
 * Approach: Dynamic Programming on Grids & Combinatorics
 * 
 * Approach Explanation:
 * 1. A robot is at the top-left corner (0, 0) of an m x n grid and wants to reach
 *    the bottom-right cell (m - 1, n - 1). The robot can only move right or down.
 * 2. Recurrence:
 *    - To reach cell (i, j), the robot comes from either the top (i - 1, j) or the left (i, j - 1).
 *    - f(i, j) = f(i - 1, j) + f(i, j - 1)
 * 3. Base Cases:
 *    - f(0, 0) = 1 (1 unique way to start at the origin)
 *    - Out of bounds (i < 0 || j < 0) = 0
 * 4. Space Optimization:
 *    - Each cell (i, j) only depends on the previous row (`prev[j]`) and the current row's left cell (`cur[j - 1]`).
 *    - Reduces auxiliary space from O(M * N) down to O(N).
 * 5. Combinatorics Alternative (Optimal O(min(M, N))):
 *    - Total steps = (m - 1) downs + (n - 1) rights = (m + n - 2).
 *    - Number of ways = (m + n - 2) C (m - 1) = (m + n - 2) C (n - 1).
 * 
 * Time & Space Complexity Summary:
 * - 1. Recursive:        TC: O(2^(M + N)) | SC: O(M + N) recursion stack
 * - 2. Memoization:      TC: O(M * N)     | SC: O(M * N) DP table + O(M + N) stack
 * - 3. Tabulation:       TC: O(M * N)     | SC: O(M * N) DP table
 * - 4. Space-Optimized:  TC: O(M * N)     | SC: O(N) rolling array
 * - 5. Combinatorics:    TC: O(min(M, N)) | SC: O(1)
 */

#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    // -------------------------------------------------------------
    // 1. Recursive Approach (Brute Force)
    // Time Complexity:  O(2^(M + N))
    // Space Complexity: O(M + N) recursion stack
    // -------------------------------------------------------------
    int solveRecursive(int i, int j) {
        if (i == 0 && j == 0) return 1;
        if (i < 0 || j < 0) return 0;

        int up = solveRecursive(i - 1, j);
        int left = solveRecursive(i, j - 1);

        return up + left;
    }

    int uniquePathsRecursive(int m, int n) {
        return solveRecursive(m - 1, n - 1);
    }

    // -------------------------------------------------------------
    // 2. Memoization Approach (Top-Down DP)
    // Time Complexity:  O(M * N)
    // Space Complexity: O(M * N) dp table + O(M + N) recursion stack
    // -------------------------------------------------------------
    int solveMemo(int i, int j, vector<vector<int>>& dp) {
        if (i == 0 && j == 0) return 1;
        if (i < 0 || j < 0) return 0;

        if (dp[i][j] != -1) return dp[i][j];

        int up = solveMemo(i - 1, j, dp);
        int left = solveMemo(i, j - 1, dp);

        return dp[i][j] = up + left;
    }

    int uniquePathsMemo(int m, int n) {
        vector<vector<int>> dp(m, vector<int>(n, -1));
        return solveMemo(m - 1, n - 1, dp);
    }

    // -------------------------------------------------------------
    // 3. Tabulation Approach (Bottom-Up DP)
    // Time Complexity:  O(M * N)
    // Space Complexity: O(M * N)
    // -------------------------------------------------------------
    int uniquePathsTabulation(int m, int n) {
        vector<vector<int>> dp(m, vector<int>(n, 0));

        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (i == 0 && j == 0) {
                    dp[i][j] = 1;
                } else {
                    int up = 0;
                    int left = 0;

                    if (i > 0) up = dp[i - 1][j];
                    if (j > 0) left = dp[i][j - 1];

                    dp[i][j] = up + left;
                }
            }
        }

        return dp[m - 1][n - 1];
    }

    // -------------------------------------------------------------
    // 4. Space-Optimized Approach (Optimal DP)
    // Time Complexity:  O(M * N)
    // Space Complexity: O(N)
    // -------------------------------------------------------------
    int uniquePathsSpaceOptimized(int m, int n) {
        vector<int> prev(n, 0);

        for (int i = 0; i < m; i++) {
            vector<int> cur(n, 0);
            for (int j = 0; j < n; j++) {
                if (i == 0 && j == 0) {
                    cur[j] = 1;
                } else {
                    int up = 0;
                    int left = 0;

                    if (i > 0) up = prev[j];
                    if (j > 0) left = cur[j - 1];

                    cur[j] = up + left;
                }
            }
            prev = cur;
        }

        return prev[n - 1];
    }

    // -------------------------------------------------------------
    // 5. Combinatorics Approach (Most Optimal)
    // Time Complexity:  O(min(M, N))
    // Space Complexity: O(1)
    // Formula: (m + n - 2) C (m - 1)
    // -------------------------------------------------------------
    int uniquePathsCombinatorics(int m, int n) {
        int N = n + m - 2;
        int r = m - 1;
        double res = 1;

        for (int i = 1; i <= r; i++) {
            res = res * (N - r + i) / i;
        }

        return (int)res;
    }
};

// 🔹 Driver Code
int main() {
    int m = 3, n = 7;

    Solution solver;
    cout << "1. Recursive:        " << solver.uniquePathsRecursive(m, n) << "\n";
    cout << "2. Memoization:      " << solver.uniquePathsMemo(m, n) << "\n";
    cout << "3. Tabulation:       " << solver.uniquePathsTabulation(m, n) << "\n";
    cout << "4. Space-Optimized:  " << solver.uniquePathsSpaceOptimized(m, n) << "\n";
    cout << "5. Combinatorics:    " << solver.uniquePathsCombinatorics(m, n) << "\n";

    return 0;
}