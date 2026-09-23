/*
 * Problem: Frog Jump (Coding Ninjas / CodeStudio) 
 * -----------------------------------------------
 * Approach: Space-Optimized Dynamic Programming 
 * 
 * Approach Explanation:
 * 1. Observation from Tabulation:
 *    - To calculate the state `dp[i]`, we only ever need the values of the immediate 
 *      two preceding states: `dp[i - 1]` and `dp[i - 2]`.
 *    - An entire array of size N is therefore unnecessary.
 * 2. State Maintenance with Two Variables:
 *    - `prev`: Represents the minimum energy required to reach index `i - 1` .
 *    - `prev2`: Represents the minimum energy required to reach index `i - 2` .
 *    - Initialized for base step `i = 0`: `prev = 0`, `prev2 = 0` .
 * 3. Iterative Transition:
 *    - At each step `i` from 1 to `n - 1` :
 *        - `fs` = `prev + abs(heights[i] - heights[i - 1])` (single jump from `i - 1`) 
 *        - `ss` = `prev2 + abs(heights[i] - heights[i - 2])` (double jump from `i - 2`, valid if `i > 1`) 
 *        - `curi = min(fs, ss)` 
 *    - Shift state values for the next iteration :
 *        - `prev2 = prev` 
 *        - `prev = curi` 
 * 4. Result:
 *    - Upon loop termination, `prev` holds the optimal answer for reaching stair `n - 1` .
 * 
 * Time Complexity:  O(N) - Single loop iterating from 1 to N - 1 .
 * Space Complexity: O(1) - Constant auxiliary space using only primitive variables .
 */

#include <bits/stdc++.h>
using namespace std;

int frogJump(int n, vector<int> &heights) { 
    int prev = 0; 
    int prev2 = 0; 

    for (int i = 1; i < n; i++) { 
        int fs = prev + abs(heights[i] - heights[i - 1]); 
        int ss = INT_MAX; 
        if (i > 1) ss = prev2 + abs(heights[i] - heights[i - 2]); 

        int curi = min(fs, ss); 
        prev2 = prev; 
        prev = curi; 
    } 

    return prev; 
} 

// 🔹 Driver Code
int main() {
    /*
        Example:
        n = 4
        heights = [10, 20, 30, 10]

        Transitions:
        i = 1: fs = 0 + |20 - 10| = 10, ss = INF -> curi = 10; prev2 = 0, prev = 10
        i = 2: fs = 10 + |30 - 20| = 20, ss = 0 + |30 - 10| = 20 -> curi = 20; prev2 = 10, prev = 20
        i = 3: fs = 20 + |10 - 30| = 40, ss = 10 + |10 - 20| = 20 -> curi = 20; prev2 = 20, prev = 20

        Output: 20
    */

    vector<int> heights = {10, 20, 30, 10};
    int n = heights.size();

    cout << "Minimum Energy Required (Space Optimized): " << frogJump(n, heights) << endl;

    return 0;
}
