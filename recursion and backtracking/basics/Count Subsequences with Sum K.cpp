/*
 * Problem: Recursion Pattern - Count Subsequences with Sum K
 * ---------------------------------------------------------
 * Approach: Pick / Not Pick Recursion with Integer Return Value
 * 
 * Approach Explanation:
 * 1. Unlike printing where we maintain a container `ds`, here we only care about
 *    the TOTAL NUMBER of valid combinations, so `ds` is completely eliminated.
 * 2. Base Case (`ind == n`):
 *    - If `s == sum`, return 1 (indicates 1 valid subsequence found).
 *    - Else, return 0 (invalid path).
 * 3. Recursive Steps:
 *    a. "Pick" choice:
 *       - Add `arr[ind]` to running sum `s`.
 *       - Recurse and store the count of valid subsequences in `l`.
 *       - Backtrack: `s -= arr[ind]`.
 *    b. "Not Pick" choice:
 *       - Recurse without including `arr[ind]` and store count in `r`.
 * 4. Return `l + r` (sum of counts from both branches).
 * 
 * Time Complexity:  O(2^N) - Evaluates all 2^N leaf paths.
 * Space Complexity: O(N)   - Auxiliary recursion stack space of depth N.
 */

#include <iostream>

using namespace std;

int printS(int ind, int s, int sum, int arr[], int n) {
    // Base Case
    if (ind == n) {
        // Condition satisfied -> found 1 valid subsequence
        if (s == sum) return 1;
        // Condition not satisfied
        else return 0;
    }

    // Pick condition: Include arr[ind]
    s += arr[ind];
    int l = printS(ind + 1, s, sum, arr, n);

    // Backtracking step
    s -= arr[ind];

    // Not Pick condition: Exclude arr[ind]
    int r = printS(ind + 1, s, sum, arr, n);

    return l + r;
}

// 🔹 Driver Code
int main() {
    int arr[] = {1, 2, 1};
    int n = 3;
    int sum = 2;

    cout << "Count of subsequences with sum " << sum << " = " 
         << printS(0, 0, sum, arr, n) << endl;

    return 0;
}
