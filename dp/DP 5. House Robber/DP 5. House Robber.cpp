/*
 * Problem: Maximum Sum of Non-Adjacent Elements / House Robber (DP 5)
 * -------------------------------------------------------------------
 * Approach: Dynamic Programming (Pick / Not-Pick Pattern)
 * 
 * Approach Explanation:
 * 1. At every element at index `i`, we have two decisions:
 *    - Pick: Add `nums[i]` to our sum. Because adjacent elements cannot be selected, 
 *      the next allowable element must come from index `i - 2` or earlier.
 *    - Not Pick: Skip `nums[i]` (gain 0), allowing us to consider the element at index `i - 1`.
 * 2. Recurrence Relation:
 *    - f(i) = max(nums[i] + f(i - 2), 0 + f(i - 1))
 * 3. Base Cases:
 *    - if (ind == 0) return nums[0]; (picking the first element if reached)
 *    - if (ind < 0) return 0;        (out of bounds returns no value)
 * 4. Space Optimization:
 *    - Notice that computing the current index answer `curi` only requires:
 *        - `prev`: answer for index `i - 1`
 *        - `prev2`: answer for index `i - 2`
 *    - We can reduce auxiliary space from O(N) to O(1) using two variables.
 * 
 * Time & Space Complexity Summary:
 * - 1. Recursive:        TC: O(2^N) | SC: O(N) auxiliary stack
 * - 2. Memoization:      TC: O(N)   | SC: O(N) DP table + O(N) stack
 * - 3. Tabulation:       TC: O(N)   | SC: O(N) DP table
 * - 4. Space-Optimized:  TC: O(N)   | SC: O(1) constant auxiliary space
 */

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    // -------------------------------------------------------------
    // 1. Recursive Approach (Brute Force)
    // Time Complexity:  O(2^N)
    // Space Complexity: O(N) recursion stack
    // -------------------------------------------------------------
    int solveRecursive(int ind, const vector<int>& nums) {
        if (ind == 0) return nums[0];
        if (ind < 0) return 0;

        int pick = nums[ind] + solveRecursive(ind - 2, nums);
        int notPick = 0 + solveRecursive(ind - 1, nums);

        return max(pick, notPick);
    }

    int robRecursive(const vector<int>& nums) {
        int n = nums.size();
        if (n == 0) return 0;
        return solveRecursive(n - 1, nums);
    }

    // -------------------------------------------------------------
    // 2. Memoization Approach (Top-Down DP)
    // Time Complexity:  O(N)
    // Space Complexity: O(N) dp array + O(N) recursion stack
    // -------------------------------------------------------------
    int solveMemo(int ind, const vector<int>& nums, vector<int>& dp) {
        if (ind == 0) return nums[0];
        if (ind < 0) return 0;

        if (dp[ind] != -1) return dp[ind];

        int pick = nums[ind] + solveMemo(ind - 2, nums, dp);
        int notPick = 0 + solveMemo(ind - 1, nums, dp);

        return dp[ind] = max(pick, notPick);
    }

    int robMemo(const vector<int>& nums) {
        int n = nums.size();
        if (n == 0) return 0;
        vector<int> dp(n, -1);
        return solveMemo(n - 1, nums, dp);
    }

    // -------------------------------------------------------------
    // 3. Tabulation Approach (Bottom-Up DP)
    // Time Complexity:  O(N)
    // Space Complexity: O(N) dp table
    // -------------------------------------------------------------
    int robTabulation(const vector<int>& nums) {
        int n = nums.size();
        if (n == 0) return 0;

        vector<int> dp(n, 0);
        dp[0] = nums[0];

        for (int i = 1; i < n; i++) {
            int pick = nums[i];
            if (i > 1) pick += dp[i - 2];

            int notPick = 0 + dp[i - 1];

            dp[i] = max(pick, notPick);
        }

        return dp[n - 1];
    }

    // -------------------------------------------------------------
    // 4. Space-Optimized Approach (Most Optimal)
    // Time Complexity:  O(N)
    // Space Complexity: O(1)
    // -------------------------------------------------------------
    int robSpaceOptimized(const vector<int>& nums) {
        int n = nums.size();
        if (n == 0) return 0;

        int prev = nums[0];  // Represents dp[i - 1]
        int prev2 = 0;       // Represents dp[i - 2]

        for (int i = 1; i < n; i++) {
            int take = nums[i];
            if (i > 1) take += prev2;

            int notTake = 0 + prev;

            int curi = max(take, notTake);
            prev2 = prev;
            prev = curi;
        }

        return prev;
    }
};

// 🔹 Driver Code
int main() {
    /*
        Example:
        nums = [2, 1, 4, 9]

        Subsets without adjacent indices:
        - [2, 4] -> sum = 6
        - [2, 9] -> sum = 11 (Optimal)
        - [1, 9] -> sum = 10
    */

    vector<int> nums = {2, 1, 4, 9};

    Solution solver;
    cout << "1. Recursive:        " << solver.robRecursive(nums) << "\n";
    cout << "2. Memoization:      " << solver.robMemo(nums) << "\n";
    cout << "3. Tabulation:       " << solver.robTabulation(nums) << "\n";
    cout << "4. Space-Optimized:  " << solver.robSpaceOptimized(nums) << "\n";

    return 0;
}
