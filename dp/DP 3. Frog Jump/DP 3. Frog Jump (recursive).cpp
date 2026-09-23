/*
 * Problem: Frog Jump (Coding Ninjas / CodeStudio) 
 * -----------------------------------------------
 * Approach: Top-Down Dynamic Programming (Memoization) 
 * 
 * Approach Explanation:
 * 1. Overlapping Subproblems:
 *    - The pure recursive approach makes duplicate calls for smaller indices (e.g., ind - 2 
 *      can be called both directly and via (ind - 1) -> left branch).
 *    - To avoid recalculating, store the computed minimum cost for each index in `dp`.
 * 2. State & Array:
 *    - `dp[ind]` stores the minimum energy required to reach index `ind` from index 0 .
 *    - Initialized to size `n + 1` filled with `-1` .
 * 3. Base Case & Memoized Lookup:
 *    - If `ind == 0`, energy consumed is 0 .
 *    - If `dp[ind] != -1`, return the precomputed value immediately .
 * 4. Recurrence Transitions:
 *    - `left`: Jump from `ind - 1` with energy `abs(heights[ind] - heights[ind - 1])` .
 *    - `right`: If `ind > 1`, jump from `ind - 2` with energy `abs(heights[ind] - heights[ind - 2])` .
 *    - Return `dp[ind] = min(left, right)` .
 * 
 * Time Complexity:  O(N) - Each state from 0 to N-1 is solved exactly once.
 * Space Complexity: O(N) - Auxiliary recursion stack depth O(N) + DP array of size O(N).
 */

#include <bits/stdc++.h> 
using namespace std;

// Helper function with memoization
int f(int ind, vector<int> &heights, vector<int> &dp) { 
    if (ind == 0) return 0; 
    if (dp[ind] != -1) return dp[ind]; 

    int left = f(ind - 1, heights, dp) + abs(heights[ind] - heights[ind - 1]); 
    int right = INT_MAX; 
    if (ind > 1) right = f(ind - 2, heights, dp) + abs(heights[ind] - heights[ind - 2]); 

    return dp[ind] = min(left, right); 
} 

int frogJump(int n, vector<int> &heights) { 
    vector<int> dp(n + 1, -1); 
    return f(n - 1, heights, dp); 
} 

// 🔹 Driver Code
int main() {
    /*
        Example:
        n = 4
        heights = [10, 20, 30, 10]
        
        Options:
        - 0 -> 1 -> 3: |10-20| + |20-10| = 10 + 10 = 20
        - 0 -> 2 -> 3: |10-30| + |30-10| = 20 + 20 = 40
        - 0 -> 1 -> 2 -> 3: |10-20| + |20-30| + |30-10| = 10 + 10 + 20 = 40
        Optimal: 20
    */

    vector<int> heights = {10, 20, 30, 10};
    int n = heights.size();

    cout << "Minimum Energy Required: " << frogJump(n, heights) << endl;

    return 0;
}
