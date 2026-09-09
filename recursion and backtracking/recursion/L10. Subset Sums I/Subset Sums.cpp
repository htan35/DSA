/*
 * Problem: Subset Sums (GFG)
 * ----------------------------
 * Approach 1: Pick / Not Pick using a Data Structure `ds` (Code in Screenshot)
 * Approach 2: Pick / Not Pick passing a Running `sum` (Optimized)
 * 
 * Approach 1 (From Screenshot):
 * 1. Maintain a vector `ds` representing the elements of the current subset.
 * 2. At each index:
 *    - Pick: push `arr[ind]` into `ds`, recurse to `ind + 1`, then pop `arr[ind]`.
 *    - Not Pick: recurse to `ind + 1` without adding to `ds`.
 * 3. Base Case: When `ind == n`, loop through `ds`, calculate total sum, and add to `ans`.
 * 
 * Approach 2 (Optimization Note):
 * - Instead of pushing into `ds` and running a loop at the base case (taking O(N) at each leaf),
 *   pass `sum` directly as a parameter (`sum + arr[ind]`), reducing leaf processing to O(1).
 * 
 * Time Complexity:
 *   - Approach 1 (Screenshot): O(2^N * N) due to iterating over `ds` of size <= N at each of the 2^N leaves.
 *   - Approach 2 (Optimized):  O(2^N) because sum is maintained incrementally.
 * Space Complexity: O(N) recursion stack depth.
 */

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    // Implementation exactly as written in the screenshot
    void subset(int ind, vector<int>& ds, vector<int>& arr, int n, vector<int>& ans) {
        if (ind == n) {
            int sum = 0;
            for (auto it : ds) {
                sum += it;
            }
            ans.push_back(sum);
            return;
        }

        // Pick the element
        ds.push_back(arr[ind]);
        subset(ind + 1, ds, arr, n, ans);

        // Backtrack
        ds.pop_back();

        // Not pick the element
        subset(ind + 1, ds, arr, n, ans);
    }

    // Optimized helper avoiding vector `ds` overhead
    void subsetOptimized(int ind, int currentSum, vector<int>& arr, int n, vector<int>& ans) {
        if (ind == n) {
            ans.push_back(currentSum);
            return;
        }

        // Pick element
        subsetOptimized(ind + 1, currentSum + arr[ind], arr, n, ans);

        // Not pick element
        subsetOptimized(ind + 1, currentSum, arr, n, ans);
    }

    vector<int> subsetSums(vector<int>& arr) {
        vector<int> ds;
        vector<int> ans;
        int n = arr.size();

        subset(0, ds, arr, n, ans);

        // Optional: sort output if required by problem
        // sort(ans.begin(), ans.end());
        return ans;
    }
};

// 🔹 Driver Code
int main() {
    /*
        Input: arr = [2, 3]
        Subsets: {}, {2}, {3}, {2, 3}
        Sums: 0, 2, 3, 5
    */

    vector<int> arr = {2, 3};
    Solution obj;
    vector<int> result = obj.subsetSums(arr);

    cout << "Subset Sums: ";
    for (int sumVal : result) {
        cout << sumVal << " ";
    }
    cout << endl;

    return 0;
}
