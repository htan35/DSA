// LeetCode 1004: Max Consecutive Ones III (OPTIMIZED SLIDING WINDOW WITH IF-STATEMENT)
// Time Complexity: O(n)
// Space Complexity: O(1)
#include <bits/stdc++.h>
using namespace std;

int longestOnes(vector<int>& nums, int k) {
    int l = 0, r = 0, zeros = 0, maxLen = 0;

    // Expand the window
    while (r < nums.size()) {
        if (nums[r] == 0) {
            zeros++;
        }

        // Single 'if' instead of inner 'while' loop to maintain maximum window size
        if (zeros > k) {
            if (nums[l] == 0) {
                zeros--;
            }
            l++;
        }

        // Update maxLen if the window is valid
        if (zeros <= k) {
            int len = r - l + 1;
            maxLen = max(maxLen, len);
        }

        r++; // Move right pointer forward
    }

    return maxLen;
}

int main() {
    vector<int> nums = {1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 0};
    int k = 2;
    cout << longestOnes(nums, k) << "\n";
    return 0;
}