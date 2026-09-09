/*
 * Problem: Subsets II / Subsets with Duplicates (LeetCode 90)
 * -----------------------------------------------------------
 * Approach: Backtracking via Loop-Based Decision Tree (Duplicate Skipping)
 * 
 * Approach Explanation:
 * 1. The input array may contain duplicates, but the solution set must not contain duplicate subsets.
 * 2. Sorting:
 *    - Sort the input array `nums` upfront. This clusters identical values together so duplicates 
 *      can be detected easily.
 * 3. Adding Subsets:
 *    - At each recursive call, the current state of `ds` is a valid subset, so immediately 
 *      push `ds` into `ansList`.
 * 4. Loop-based Branching:
 *    - Run a loop from `i = ind` to `nums.size() - 1`.
 *    - Duplicate Check: If `i != ind && nums[i] == nums[i - 1]`, continue (skip this branch).
 *      This ensures we do not pick the same element multiple times at the same recursion depth.
 *    - Pick `nums[i]`: Push to `ds`.
 *    - Recurse: Call `findSubsets(i + 1, nums, ds, ansList)`.
 *    - Backtrack: Pop the last element from `ds` before moving to `i + 1`.
 * 
 * Time Complexity:  O(2^N * N) - 2^N subsets generated, copying each takes up to O(N).
 * Space Complexity: O(N)       - Auxiliary space for the recursion stack and `ds` vector.
 */

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    void findSubsets(int ind, vector<int>& nums, vector<int>& ds, vector<vector<int>>& ansList) {
        // Every state reached represents a valid unique subset
        ansList.push_back(ds);

        for (int i = ind; i < nums.size(); i++) {
            // Skip duplicates at the same level of the recursion tree
            // so i<index is not possible because i starts with index 
            // and we are taking duplicates for the first iteration, that is the first recursion tree for that i = index
            // and to check duplicates nums[i] == nums[i - 1] but it will not add any, we want for first iteration, for that i>index or i!=index
            // to see recursive tree with i and index refer last page in pdf
            if (i != ind && nums[i] == nums[i - 1]) continue;

            ds.push_back(nums[i]);
            findSubsets(i + 1, nums, ds, ansList);
            ds.pop_back(); // Backtracking step
        }
    }

    vector<vector<int>> subsetsWithDup(vector<int>& nums) {
        sort(nums.begin(), nums.end()); // Step 1: Sort to bring duplicates together
        vector<vector<int>> ansList;
        vector<int> ds;

        findSubsets(0, nums, ds, ansList);
        return ansList;
    }
};

// 🔹 Driver Code
int main() {
    /*
        Input: nums = [1, 2, 2]
        Unique Subsets:
        [], [1], [1, 2], [1, 2, 2], [2], [2, 2]
    */

    vector<int> nums = {1, 2, 2};
    Solution obj;
    vector<vector<int>> result = obj.subsetsWithDup(nums);

    cout << "Unique Subsets:\n";
    for (const auto& subset : result) {
        cout << "[ ";
        for (int val : subset) {
            cout << val << " ";
        }
        cout << "]\n";
    }

    return 0;
}
