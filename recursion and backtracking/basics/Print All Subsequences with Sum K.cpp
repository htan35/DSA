/*
 * Problem: Recursion Pattern - Print All Subsequences with Sum K
 * -------------------------------------------------------------
 * Approach: Pick / Not Pick Recursion with Running Sum
 * 
 * Approach Explanation:
 * 1. Maintain a running sum `s` alongside the container `ds` to track the current subsequence sum.
 * 2. At each index `ind`:
 *    a. Pick: Add `arr[ind]` to `ds`, add to running sum (`s += arr[ind]`), and recurse.
 *             Backtrack by subtracting `s -= arr[ind]` and popping from `ds`.
 *    b. Not Pick: Recurse to `ind + 1` without modifying `s` or `ds`.
 * 3. Base Case:
 *    - When `ind == n`, check if `s == sum`.
 *    - If condition holds, print all elements in `ds`.
 *    - Return to explore other branches.
 * 
 * Time Complexity:  O(2^N * N) - 2^N leaf paths, printing can take up to O(N).
 * Space Complexity: O(N)       - Recursion stack depth equals N.
 */

#include <iostream>
#include <vector>

using namespace std;

void printS(int ind, vector<int>& ds, int s, int sum, int arr[], int n) {
    // Base Case: Reached the end of the array
    if (ind == n) {
        if (s == sum) {
            for (auto it : ds) cout << it << " ";
            cout << endl;
        }
        return;
    }

    // Pick condition: Include current element in subsequence
    ds.push_back(arr[ind]);
    s += arr[ind];

    printS(ind + 1, ds, s, sum, arr, n);

    // Backtrack
    s -= arr[ind];
    ds.pop_back();

    // Not Pick condition: Do not include current element
    printS(ind + 1, ds, s, sum, arr, n);
}

// 🔹 Driver Code
int main() {
    int arr[] = {1, 2, 1};
    int n = 3;
    int sum = 2;
    vector<int> ds;

    cout << "Subsequences with sum " << sum << ":\n";
    printS(0, ds, 0, sum, arr, n);

    return 0;
}
