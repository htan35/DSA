/*
 * Problem: Recursion Pattern - Print Only ONE Subsequence with Sum K (Optimal Pruning)
 * -----------------------------------------------------------------------------------
 * Approach: Pick / Not Pick Recursion with Boolean Return for Early Exit
 * 
 * Approach Explanation:
 * 1. Unlike using a global flag (which continues traversing remaining recursion branches),
 *    returning a `bool` stops and unwinds the recursion call stack immediately upon finding the first valid answer.
 * 2. Base Case (`ind == n`):
 *    - If `s == sum`: print the subsequence in `ds` and `return true`.
 *    - Else: `return false`.
 * 3. Recursive Steps:
 *    a. "Pick" branch:
 *       - Add `arr[ind]` to `ds`, add to running sum (`s += arr[ind]`).
 *       - If `printS(...) == true`, immediately `return true` (no need to explore further or backtrack).
 *       - Backtrack: `s -= arr[ind]` and `ds.pop_back()`.
 *    b. "Not Pick" branch:
 *       - If `printS(...) == true`, immediately `return true`.
 * 4. If neither choice leads to a valid subsequence, `return false`.
 * 
 * Time Complexity:  O(2^N) worst-case (if no answer exists), but stops at the very first valid subsequence.
 * Space Complexity: O(N) auxiliary space for recursion stack and `ds`.
 */

#include <iostream>
#include <vector>

using namespace std;

bool printS(int ind, vector<int>& ds, int s, int sum, int arr[], int n) {
    // Base Case
    if (ind == n) {
        // Condition satisfied
        if (s == sum) {
            for (auto it : ds) cout << it << " ";
            cout << endl;
            return true;
        }
        // Condition not satisfied
        else return false;
    }

    // Pick condition: Add current element
    ds.push_back(arr[ind]);
    s += arr[ind];

    if (printS(ind + 1, ds, s, sum, arr, n) == true) {
        return true;
    }

    // Backtracking step
    s -= arr[ind];
    ds.pop_back();

    // Not Pick condition: Skip current element
    if (printS(ind + 1, ds, s, sum, arr, n) == true) {
        return true;
    }

    return false;
}

// 🔹 Driver Code
int main() {
    int arr[] = {1, 2, 1};
    int n = 3;
    int sum = 2;
    vector<int> ds;

    cout << "First subsequence with sum " << sum << ":\n";
    printS(0, ds, 0, sum, arr, n);

    return 0;
}
