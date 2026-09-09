/*
 * Problem: String Permutations (In-Place Swapping Approach)
 * ---------------------------------------------------------
 * Approach: Backtracking by In-Place Swapping (Approach 2)
 * 
 * Approach Explanation:
 * 1. Rather than maintaining an extra `freq` array and auxiliary container `ds`, 
 *    generate permutations directly in-place by swapping characters.
 * 2. `solve(idx, s, ans)`:
 *    - Base Case: When `idx == s.size()`, the string `s` represents a complete permutation.
 *      Push `s` into `ans` and return.
 * 3. Loop-based Swapping:
 *    - Iterate `i` from `idx` to `s.size() - 1`.
 *    - Swap `s[idx]` with `s[i]` to place character `s[i]` at the current position `idx`.
 *    - Recurse for the next index: `solve(idx + 1, s, ans)`.
 *    - Backtrack: Swap `s[idx]` with `s[i]` again to restore the original string state.
 * 
 * Space Optimization Benefit:
 * - Reduces auxiliary space from O(N) (visited/freq array + extra vector) down to purely O(N) 
 *   recursion stack space.
 * 
 * Note on Duplicates:
 * - If the input contains duplicate characters, this approach will produce duplicate permutations.
 *   To handle duplicates, either sort and use an unordered_set per recursion level, or track swapped characters.
 * 
 * Time Complexity:  O(N! * N) - N! permutations, each takes O(N) to push/copy into the result.
 * Space Complexity: O(N)       - Bounded only by the recursion stack depth (no extra visited arrays).
 */

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

class Solution {
public:
    void solve(int idx, string& s, vector<string>& ans) {
        if (idx == s.size()) {
            ans.push_back(s);
            return;
        }

        for (int i = idx; i < s.size(); i++) {
            // Place s[i] at index idx
            swap(s[idx], s[i]);

            // Recurse for remaining characters
            solve(idx + 1, s, ans);

            // Backtrack to restore original configuration
            swap(s[idx], s[i]);
        }
    }

    vector<string> permutations(string s) {
        vector<string> ans;
        solve(0, s, ans);
        return ans;
    }
};

// 🔹 Driver Code
int main() {
    /*
        Input: s = "ABC"
        Permutations: "ABC", "ACB", "BAC", "BCA", "CBA", "CAB"
    */

    string s = "ABC";
    Solution obj;
    vector<string> result = obj.permutations(s);

    cout << "Permutations of \"" << s << "\":\n";
    for (const string& str : result) {
        cout << str << "\n";
    }

    return 0;
}
