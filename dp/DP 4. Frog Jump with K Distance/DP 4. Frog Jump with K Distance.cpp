/*
 * Problem: Frog Jump with K Distances (DP 4 - At most K jumps)
 * -----------------------------------------------------------
 * Approach: Dynamic Programming (Memoization, Tabulation, & Space Optimization)
 * 
 * Problem Statement:
 * A frog is at index 0 and wants to reach index (n - 1). In this follow-up, 
 * the frog is allowed to jump anywhere from 1 up to K steps forward 
 * (i.e., from index `i` to `i + 1`, `i + 2`, ..., `i + k`).
 * Energy consumed for jump from index `j` to `i` is: `abs(heights[i] - heights[j])`.
 * 
 * Recurrence Relation:
 *   dp[i] = min_{j=1..k} ( dp[i - j] + abs(heights[i] - heights[i - j]) )  for (i - j >= 0)
 * Base Case:
 *   dp[0] = 0
 * 
 * Complexity Note:
 * - Time Complexity:  O(N * K) - For each of the N stairs, we test up to K previous stairs.
 * - Space Complexity: 
 *     - Tabulation:       O(N)
 *     - Space-Optimized:  O(K) (maintaining a rolling window or list of the last K states)
 */

#include <iostream>
#include <vector>
#include <cmath>
#include <climits>
#include <algorithm>

using namespace std;

// -------------------------------------------------------------
// 1. Tabulation Approach (Bottom-Up DP - As shown on board)
// Time Complexity:  O(N * K)
// Space Complexity: O(N)
// -------------------------------------------------------------
int frogJumpKTabulation(int n, int k, vector<int>& heights) {
    vector<int> dp(n, 0);
    dp[0] = 0;

    for (int i = 1; i < n; i++) {
        int minSteps = INT_MAX;

        for (int j = 1; j <= k; j++) {
            if (i - j >= 0) {
                int jump = dp[i - j] + abs(heights[i] - heights[i - j]);
                minSteps = min(minSteps, jump);
            }
        }
        dp[i] = minSteps;
    }

    return dp[n - 1];
}

// -------------------------------------------------------------
// 2. Memoization Approach (Top-Down DP)
// Time Complexity:  O(N * K)
// Space Complexity: O(N) dp array + O(N) recursion stack
// -------------------------------------------------------------
int solveMemo(int ind, int k, vector<int>& heights, vector<int>& dp) {
    if (ind == 0) return 0;
    if (dp[ind] != -1) return dp[ind];

    int minSteps = INT_MAX;
    for (int j = 1; j <= k; j++) {
        if (ind - j >= 0) {
            int jump = solveMemo(ind - j, k, heights, dp) + abs(heights[ind] - heights[ind - j]);
            minSteps = min(minSteps, jump);
        }
    }

    return dp[ind] = minSteps;
}

int frogJumpKMemo(int n, int k, vector<int>& heights) {
    vector<int> dp(n, -1);
    return solveMemo(n - 1, k, heights, dp);
}

// -------------------------------------------------------------
// 3. Space-Optimized Approach (Rolling Window of Size K)
// Time Complexity:  O(N * K)
// Space Complexity: O(K)
// -------------------------------------------------------------
int frogJumpKSpaceOptimized(int n, int k, vector<int>& heights) {
    // Only need to keep track of the last k answers
    vector<int> lastK;
    lastK.push_back(0); // Base case: dp[0] = 0

    for (int i = 1; i < n; i++) {
        int minSteps = INT_MAX;
        int sz = lastK.size();

        for (int j = 1; j <= k && j <= sz; j++) {
            int jump = lastK[sz - j] + abs(heights[i] - heights[i - j]);
            minSteps = min(minSteps, jump);
        }

        lastK.push_back(minSteps);
        // Evict oldest state once size exceeds k
        if (lastK.size() > (size_t)k) {
            lastK.erase(lastK.begin());
        }
    }

    return lastK.back();
}

// 🔹 Driver Code
int main() {
    /*
        Example:
        heights = [10, 30, 40, 50, 20], k = 3
        
        Indices:   0   1   2   3   4
        Heights:  10  30  40  50  20
        
        Jump from 0 -> 4 directly: |10 - 20| = 10 (not possible since 4 - 0 = 4 > k = 3)
        Jump 0 -> 2 -> 4: |10 - 40| + |40 - 20| = 30 + 20 = 50
        Jump 0 -> 1 -> 4: |10 - 30| + |30 - 20| = 20 + 10 = 30 (Optimal)
    */

    vector<int> heights = {10, 30, 40, 50, 20};
    int n = heights.size();
    int k = 3;

    cout << "Tabulation Result:       " << frogJumpKTabulation(n, k, heights) << "\n";
    cout << "Memoization Result:      " << frogJumpKMemo(n, k, heights) << "\n";
    cout << "Space-Optimized Result:  " << frogJumpKSpaceOptimized(n, k, heights) << "\n";

    return 0;
}