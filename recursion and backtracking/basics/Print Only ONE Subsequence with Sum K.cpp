/*
 * Problem: Recursion Pattern - Print Only ONE Subsequence with Sum K
 * -----------------------------------------------------------------
 * Approach: Pick / Not Pick with Early Stopping (Global Flag Technique)
 * 
 * Approach Explanation:
 * 1. To print only the first valid subsequence, use a boolean flag (`flag = false`).
 * 2. In the base case (`ind == n`):
 *    - If `s == sum` AND `flag == false`:
 *        - Mark `flag = true` to prevent any subsequent valid subsequences from printing.
 *        - Print the current subsequence stored in `ds`.
 * 3. Both branches ("pick" and "not pick") are executed, but printing is guarded by the flag.
 * 
 * Note on Optimization:
 * - A cleaner, more optimal pattern returns `bool` from the function (`true` when an answer is found)
 *   to immediately stop further recursion and prune remaining recursive branches.
 * 
 * Time Complexity:  O(2^N) - Traverses recursive tree until base cases are evaluated.
 * Space Complexity: O(N)   - Recursion depth and data structure size.
 */

#include <iostream>
#include <vector>

using namespace std;

bool flag = false;

void printS(int ind, vector<int>& ds, int s, int sum, int arr[], int n) {
    // Base Case
    if (ind == n) {
        // Condition satisfied and no sequence has been printed yet
        if (s == sum && flag == false) {
            flag = true;
            for (auto it : ds) cout << it << " ";
            cout << endl;
        }
        return;
    }

    // Pick condition
    ds.push_back(arr[ind]);
    s += arr[ind];

    printS(ind + 1, ds, s, sum, arr, n);

    // Backtrack
    s -= arr[ind];
    ds.pop_back();

    // Not Pick condition
    printS(ind + 1, ds, s, sum, arr, n);
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
