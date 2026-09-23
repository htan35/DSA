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
 * Time Complexity:  O(N) - Linear iteration across all elements.
 * Space Complexity: O(1) - Constant auxiliary space (for optimized iterative version).
 */

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    // ------------------------------------------------------------------
    // 1. Top-Down Approach (Memoization)
    // Time Complexity:  O(N)
    // Space Complexity: O(N)
    // ------------------------------------------------------------------
    int f(int ind, vector<int>& nums, vector<int>& dp) {
        if (ind == 0) return nums[ind];
        if (ind < 0) return 0;

        if (dp[ind] != -1) return dp[ind];

        int pick = nums[ind] + f(ind - 2, nums, dp);
        int notPick = 0 + f(ind - 1, nums, dp);

        return dp[ind] = max(pick, notPick);
    }

    // ------------------------------------------------------------------
    // 2. Space-Optimized Tabulation (Most Optimal)
    // Time Complexity:  O(N)
    // Space Complexity: O(1)
    // ------------------------------------------------------------------
    int maximumNonAdjacentSum(vector<int>& nums) {
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

        Possible non-adjacent subsets:
        - [2, 4] -> sum = 6
        - [2, 9] -> sum = 11 (Optimal)
        - [1, 9] -> sum = 10
        - [4], [9], etc.

        Expected Output: 11
    */

    vector<int> nums = {2, 1, 4, 9};
    int n = nums.size();

    Solution solver;

    // Memoization test
    vector<int> dp(n, -1);
    cout << "Maximum Sum (Memoization):     " << solver.f(n - 1, nums, dp) << "\n";

    // Space-optimized test
    cout << "Maximum Sum (Space-Optimized): " << solver.maximumNonAdjacentSum(nums) << "\n";

    return 0;
}