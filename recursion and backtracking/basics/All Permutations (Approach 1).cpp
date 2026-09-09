/*
 * Problem: Permutations (LeetCode 46)
 * ------------------------------------
 * Approach: Backtracking using Frequency / Visited Array (Approach 1)
 * 
 * Approach Explanation:
 * 1. A permutation contains every element of the array arranged in some order.
 * 2. `recurPermute(ds, nums, ans, freq)`:
 *    - Base Case: When `ds.size() == nums.size()`, a full permutation is built -> push `ds` to `ans` and return.
 * 3. Loop-based Exploration:
 *    - Iterate `i` from `0` to `nums.size() - 1`.
 *    - If `!freq[i]` (element at index `i` has not yet been chosen in current permutation):
 *        a. Pick: Push `nums[i]` into `ds` and set `freq[i] = 1`.
 *        b. Recurse: Call `recurPermute(ds, nums, ans, freq)`.
 *        c. Backtrack: Reset `freq[i] = 0` and pop from `ds` (`ds.pop_back()`).
 * 
 * Time Complexity:  O(N! * N) - There are N! permutations, each taking O(N) to copy into `ans`.
 * Space Complexity: O(N)       - O(N) recursion stack, O(N) for `freq` array, and O(N) for `ds`.
 */

#include <iostream>
#include <vector>

using namespace std;

class Solution {
private:
    void recurPermute(vector<int>& ds, vector<int>& nums, vector<vector<int>>& ans, int freq[]) {
        // Base Case: Subsequence length matches original array length
        if (ds.size() == nums.size()) {
            ans.push_back(ds);
            return;
        }

        // Try picking any available element
        for (int i = 0; i < nums.size(); i++) {
            if (!freq[i]) {
                ds.push_back(nums[i]);
                freq[i] = 1;

                recurPermute(ds, nums, ans, freq);

                // Backtrack
                freq[i] = 0;
                ds.pop_back();
            }
        }
    }

public:
    vector<vector<int>> permute(vector<int>& nums) {
        vector<vector<int>> ans;
        vector<int> ds;
        int freq[nums.size()];
        for (int i = 0; i < nums.size(); i++) freq[i] = 0;

        recurPermute(ds, nums, ans, freq);
        return ans;
    }
};

// 🔹 Driver Code
int main() {
    /*
        Input: nums = [1, 2, 3]
        Output: 
        [1 2 3], [1 3 2], [2 1 3], [2 3 1], [3 1 2], [3 2 1]
    */

    vector<int> nums = {1, 2, 3};
    Solution obj;
    vector<vector<int>> result = obj.permute(nums);

    cout << "All Permutations:\n";
    for (const auto& p : result) {
        cout << "[ ";
        for (int x : p) {
            cout << x << " ";
        }
        cout << "]\n";
    }

    return 0;
}
