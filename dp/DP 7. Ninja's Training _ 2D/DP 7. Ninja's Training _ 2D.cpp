/*
 * Problem: Ninja's Training (Coding Ninjas) / Vacation (AtCoder DP Contest)
 * ------------------------------------------------------------------------
 * Approach: 2D Dynamic Programming (Day & Last Task Constraint)
 * 
 * Approach Explanation:
 * 1. A ninja must choose 1 of 3 activities (0, 1, 2) each day to maximize merit points,
 *    with the constraint that the same activity CANNOT be performed on two consecutive days.
 * 2. State Representation:
 *    - `day`: Current day index (from 0 to n - 1).
 *    - `last`: The task performed on the next day (0, 1, 2), or 3 if no task has been chosen yet.
 * 3. Recurrence Relation:
 *    - For any day and last task:
 *      f(day, last) = max_{task = 0..2, task != last} ( points[day][task] + f(day - 1, task) )
 * 4. Base Case (day == 0):
 *    - On day 0, greedily take the maximum of the allowed tasks (excluding `last`):
 *      f(0, last) = max_{task = 0..2, task != last} ( points[0][task] )
 * 5. Space Optimization:
 *    - In tabulation, `dp[day]` only relies on `dp[day - 1]`.
 *    - Instead of keeping an `n x 4` table, maintain a single 1D array of size 4 (`prev`)
 *      and compute the new day values into `temp`, optimizing auxiliary space to O(1).
 * 
 * Time & Space Complexity Summary:
 * - 1. Recursive:        TC: O(3^N)       | SC: O(N) recursion stack
 * - 2. Memoization:      TC: O(N * 4 * 3) | SC: O(N * 4) DP table + O(N) stack
 * - 3. Tabulation:       TC: O(N * 4 * 3) | SC: O(N * 4) DP table
 * - 4. Space-Optimized:  TC: O(N * 4 * 3) | SC: O(4) = O(1) constant space
 */

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    // -------------------------------------------------------------
    // 1. Recursive Approach (Brute Force)
    // Time Complexity:  O(3^N)
    // Space Complexity: O(N) recursion stack
    // -------------------------------------------------------------
    int solveRecursive(int day, int last, const vector<vector<int>>& points) {
        if (day == 0) {
            int maxi = 0;
            for (int task = 0; task < 3; task++) {
                if (task != last) {
                    maxi = max(maxi, points[0][task]);
                }
            }
            return maxi;
        }

        int maxi = 0;
        for (int task = 0; task < 3; task++) {
            if (task != last) {
                int point = points[day][task] + solveRecursive(day - 1, task, points);
                maxi = max(maxi, point);
            }
        }
        return maxi;
    }

    int ninjaTrainingRecursive(int n, const vector<vector<int>>& points) {
        return solveRecursive(n - 1, 3, points);
    }

    // -------------------------------------------------------------
    // 2. Memoization Approach (Top-Down DP)
    // Time Complexity:  O(N * 4 * 3)
    // Space Complexity: O(N * 4) dp table + O(N) recursion stack
    // -------------------------------------------------------------
    int solveMemo(int day, int last, const vector<vector<int>>& points, vector<vector<int>>& dp) {
        if (day == 0) {
            int maxi = 0;
            for (int task = 0; task < 3; task++) {
                if (task != last) {
                    maxi = max(maxi, points[0][task]);
                }
            }
            return maxi;
        }

        if (dp[day][last] != -1) return dp[day][last];

        int maxi = 0;
        for (int task = 0; task < 3; task++) {
            if (task != last) {
                int point = points[day][task] + solveMemo(day - 1, task, points, dp);
                maxi = max(maxi, point);
            }
        }
        return dp[day][last] = maxi;
    }

    int ninjaTrainingMemo(int n, const vector<vector<int>>& points) {
        vector<vector<int>> dp(n, vector<int>(4, -1));
        return solveMemo(n - 1, 3, points, dp);
    }

    // -------------------------------------------------------------
    // 3. Tabulation Approach (Bottom-Up DP)
    // Time Complexity:  O(N * 4 * 3)
    // Space Complexity: O(N * 4)
    // -------------------------------------------------------------
    int ninjaTrainingTabulation(int n, const vector<vector<int>>& points) {
        vector<vector<int>> dp(n, vector<int>(4, 0));

        // Base cases for day 0
        dp[0][0] = max(points[0][1], points[0][2]);
        dp[0][1] = max(points[0][0], points[0][2]);
        dp[0][2] = max(points[0][0], points[0][1]);
        dp[0][3] = max(points[0][0], max(points[0][1], points[0][2]));

        for (int day = 1; day < n; day++) {
            for (int last = 0; last < 4; last++) {
                dp[day][last] = 0;
                for (int task = 0; task < 3; task++) {
                    if (task != last) {
                        int point = points[day][task] + dp[day - 1][task];
                        dp[day][last] = max(dp[day][last], point);
                    }
                }
            }
        }

        return dp[n - 1][3];
    }

    // -------------------------------------------------------------
    // 4. Space-Optimized Approach (Most Optimal)
    // Time Complexity:  O(N * 4 * 3)
    // Space Complexity: O(4) = O(1)
    // -------------------------------------------------------------
    int ninjaTrainingSpaceOptimized(int n, const vector<vector<int>>& points) {
        vector<int> prev(4, 0);

        // Base cases for day 0
        prev[0] = max(points[0][1], points[0][2]);
        prev[1] = max(points[0][0], points[0][2]);
        prev[2] = max(points[0][0], points[0][1]);
        prev[3] = max(points[0][0], max(points[0][1], points[0][2]));

        for (int day = 1; day < n; day++) {
            vector<int> temp(4, 0);
            for (int last = 0; last < 4; last++) {
                temp[last] = 0;
                for (int task = 0; task < 3; task++) {
                    if (task != last) {
                        temp[last] = max(temp[last], points[day][task] + prev[task]);
                    }
                }
            }
            prev = temp;
        }

        return prev[3];
    }
};

// 🔹 Driver Code
int main() {
    /*
        Example:
        Day 0: [10, 50, 1]
        Day 1: [5,  100, 11]
        Day 2: [20, 30, 90]

        Optimal Path:
        Day 0 -> task 1 (50)
        Day 1 -> task 0 (5) or task 2 (11) -> pick 2 (11)
        Day 2 -> task 1 (30) or task 0 (20) ...
        Best route:
        Day 0: 50 (task 1)
        Day 1: 11 (task 2)
        Day 2: 20 (task 0) -> 81
        Alternatively:
        Day 0: 10 (task 0)
        Day 1: 100 (task 1)
        Day 2: 90 (task 2) -> 200 (Optimal)
    */

    vector<vector<int>> points = {
        {10, 50, 1},
        {5, 100, 11},
        {20, 30, 90}
    };
    int n = points.size();

    Solution solver;
    cout << "1. Recursive:        " << solver.ninjaTrainingRecursive(n, points) << "\n";
    cout << "2. Memoization:      " << solver.ninjaTrainingMemo(n, points) << "\n";
    cout << "3. Tabulation:       " << solver.ninjaTrainingTabulation(n, points) << "\n";
    cout << "4. Space-Optimized:  " << solver.ninjaTrainingSpaceOptimized(n, points) << "\n";

    return 0;
}