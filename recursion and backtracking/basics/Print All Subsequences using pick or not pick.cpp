/*
 * Problem: Recursion on Subsequences | Printing All Subsequences
 * -------------------------------------------------------------
 * Approach: Pick / Not Pick (Include / Exclude) Recursion Pattern
 * 
 * Approach Explanation:
 * 1. A subsequence is a contiguous or non-contiguous sequence derived by 
 *    deleting zero or more elements without changing the order of the remaining elements.
 * 2. At every index `ind`, we make two recursive choices:
 *    a. "Pick / Take":
 *       - Add `arr[ind]` to the data structure `ds`.
 *       - Recurse for the next index: `printF(ind + 1, ds, arr, n)`.
 *       - Backtrack by removing `arr[ind]` using `ds.pop_back()` so the container
 *         is clean for the other choice.
 *    b. "Not Pick / Not Take":
 *       - Without adding `arr[ind]`, recurse directly: `printF(ind + 1, ds, arr, n)`.
 * 3. Base Case:
 *    - When `ind == n`, we have decided on every element.
 *    - Print all elements currently stored in `ds`. If `ds` is empty, print `{}`.
 *    - Return to backtrack.
 * 
 * Time Complexity:  O(2^N * N) - 2^N possible subsequences, each takes up to O(N) to print.
 * Space Complexity: O(N)       - Recursion stack depth is N, and `ds` holds at most N elements.
 */

#include <iostream>
#include <vector>

using namespace std;

void printF(int ind, vector<int>& ds, int arr[], int n) {
    // Base Case: Reached the end of the array
    if (ind == n) {
        for (auto it : ds) {
            cout << it << " ";
        }
        if (ds.size() == 0) {
            cout << "{}";
        }
        cout << endl;
        return;
    }

    // Choice 1: Take / Pick the element at the current index
    ds.push_back(arr[ind]);
    printF(ind + 1, ds, arr, n);
    ds.pop_back(); // Backtracking step

    // Choice 2: Not Pick / Ignore the element at the current index
    printF(ind + 1, ds, arr, n);
}

// 🔹 Driver Code
int main() {
    int arr[] = {3, 1, 2};
    int n = sizeof(arr) / sizeof(arr[0]);
    vector<int> ds;

    cout << "All Subsequences of [3, 1, 2]:\n" << endl;
    printF(0, ds, arr, n);

    return 0;
}
