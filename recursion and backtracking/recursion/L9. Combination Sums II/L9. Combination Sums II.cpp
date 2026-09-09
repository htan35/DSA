/*
 * Problem: Combination Sum II (LeetCode 40)
 * ----------------------------------------
 * Approach: Backtracking with Duplicate Skipping & Pruning
 * 
 * Approach Explanation:
 * 1. Each number in `candidates` may only be used ONCE in the combination, 
 *    and the solution set must NOT contain duplicate combinations.
 * 2. Sorting:
 *    - Sort `candidates` upfront so identical elements sit adjacent to each other.
 * 3. Base Case:
 *    - If `target == 0`, we found a valid combination -> push `ds` into `ans` and return.
 * 4. Loop-based Exploration from `i = ind` to `arr.size() - 1`:
 *    - Duplicate Pruning: If `i > ind && arr[i] == arr[i - 1]`, skip with `continue`.
 *      This ensures we never start the same combination with the same number at the same recursion depth.
 *    - Early Termination: If `arr[i] > target`, break immediately. Because the array is sorted, 
 *      all subsequent elements will also exceed the target.
 *    - Recurse: Push `arr[i]` into `ds`, call `findCombination(i + 1, target - arr[i], ...)` 
 *      (moving to `i + 1` ensures each element is used only once).
 *    - Backtrack: Pop `arr[i]` from `ds`.
 * 
 * Time Complexity:  O(2^N * K) - At most 2^N state transitions, copying `ds` takes O(K).
 * Space Complexity: O(K)       - Max recursion depth bounded by K (average combination length).
 */

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    void findCombination(int ind, int target, vector<int>& arr, vector<vector<int>>& ans, vector<int>& ds) {
        if (target == 0) {
            ans.push_back(ds);
            return;
        }

        for (int i = ind; i < arr.size(); i++) {
            // Skip duplicate elements at the same tree depth
            if (i > ind && arr[i] == arr[i - 1]) continue;

            // Since the array is sorted, no subsequent elements can fit
            if (arr[i] > target) break;

            ds.push_back(arr[i]);
            // Move to i + 1 because each element can only be used once
            findCombination(i + 1, target - arr[i], arr, ans, ds);
            ds.pop_back(); // Backtracking step
        }
    }

    vector<vector<int>> combinationSum2(vector<int>& candidates, int target) {
        sort(candidates.begin(), candidates.end()); // Essential for duplicate skipping and early pruning
        vector<vector<int>> ans;
        vector<int> ds;

        findCombination(0, target, candidates, ans, ds);
        return ans;
    }
};

// 🔹 Driver Code
int main() {
    /*
        Candidates = [10, 1, 2, 7, 6, 1, 5], Target = 8
        Sorted = [1, 1, 2, 5, 6, 7, 10]

        Expected Unique Combinations:
        [1, 1, 6]
        [1, 2, 5]
        [1, 7]
        [2, 6]
    */

    vector<int> candidates = {10, 1, 2, 7, 6, 1, 5};
    int target = 8;

    Solution obj;
    vector<vector<int>> result = obj.combinationSum2(candidates, target);

    cout << "Unique combinations summing to " << target << ":\n";
    for (const auto& comb : result) {
        cout << "[ ";
        for (int val : comb) {
            cout << val << " ";
        }
        cout << "]\n";
    }

    return 0;
}
