/*
 * Problem: Frog Jump (Coding Ninjas / CodeStudio)[cite: 22]
 * -----------------------------------------------
 * Approach: Bottom-Up Dynamic Programming (Tabulation)[cite: 22]
 * 
 * Approach Explanation:
 * 1. Base Case:
 *    - Starting at stair 0 consumes 0 energy, so `dp[0] = 0`[cite: 22].
 * 2. Iterative Transition:
 *    - Iterate `i` from 1 up to `n - 1` to iteratively build solutions from smaller subproblems[cite: 22].
 *    - `fs` (First Step): Jump from index `i - 1` consuming:
 *        `dp[i - 1] + abs(heights[i] - heights[i - 1])`[cite: 22]
 *    - `ss` (Second Step): If `i > 1`, jump from index `i - 2` consuming:
 *        `dp[i - 2] + abs(heights[i] - heights[i - 2])`[cite: 22]
 *    - Store the optimal cost: `dp[i] = min(fs, ss)`[cite: 22].
 * 3. Final Result:
 *    - `dp[n - 1]` contains the minimum total energy required to reach the last stair[cite: 22].
 * 
 * Time Complexity:  O(N) - Single pass loop from 1 to N - 1.
 * Space Complexity: O(N) - Tabulation table `dp` of size N (no recursion call stack).
 */

#include <bits/stdc++.h>[cite: 22]
using namespace std;

int frogJump(int n, vector<int> &heights) {[cite: 22]
    vector<int> dp(n, 0);[cite: 22]
    dp[0] = 0;[cite: 22]

    for (int i = 1; i < n; i++) {[cite: 22]
        int fs = dp[i - 1] + abs(heights[i] - heights[i - 1]);[cite: 22]
        int ss = INT_MAX;[cite: 22]

        if (i > 1) ss = dp[i - 2] + abs(heights[i] - heights[i - 2]);[cite: 22]

        dp[i] = min(fs, ss);[cite: 22]
    }[cite: 22]

    return dp[n - 1];[cite: 22]
}[cite: 22]

// 🔹 Driver Code
int main() {
    /*
        Example:
        n = 4
        heights = [10, 20, 30, 10]
        
        Step-by-step DP table filling:
        - dp[0] = 0
        - dp[1] = dp[0] + |20 - 10| = 10
        - dp[2] = min(dp[1] + |30 - 20|, dp[0] + |30 - 10|) = min(10 + 10, 0 + 20) = 20
        - dp[3] = min(dp[2] + |10 - 30|, dp[1] + |10 - 20|) = min(20 + 20, 10 + 10) = 20
        
        Result: 20
    */

    vector<int> heights = {10, 20, 30, 10};
    int n = heights.size();

    cout << "Minimum Energy Required (Tabulation): " << frogJump(n, heights) << endl;

    return 0;
}
