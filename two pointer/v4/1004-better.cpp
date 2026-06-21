// LeetCode 1004: Max Consecutive Ones III
// Time Complexity: O(n + n) -> O(n)
// Space Complexity: O(1)
#include <bits/stdc++.h>
using namespace std;

int longestOnes(vector<int>& nums, int k) {
    int maxLen = 0;
    int l = 0, r = 0;
    int zeros = 0;

    // Expand the window using the right pointer
    while (r < nums.size()) {
        if (nums[r] == 0) {
            zeros++;
        }

        // Shrink the window from the left if zeros exceed k
        while (zeros > k) {
            if (nums[l] == 0) {
                zeros--;
            }
            l++;
        }

        // Update maximum length when window is valid
        if (zeros <= k) {
            int len = r - l + 1;
            maxLen = max(len, maxLen);
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