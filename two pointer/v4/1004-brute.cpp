// MAX CONSECUTIVE ONES III (BRUTE FORCE)
// Time Complexity: O(n^2)
// Space Complexity: O(1)
//leetcode 1004
#include <bits/stdc++.h>
using namespace std;

int main() {
    vector<int> nums = {1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 0};
    int k = 2;
    int n = nums.size();

    int maxLen = 0;

    // Outer loop: choose starting point
    for (int i = 0; i < n; i++) {
        int zeros = 0;

        // Inner loop: choose ending point
        for (int j = i; j < n; j++) {
            // Count zeros in the current subarray
            if (nums[j] == 0) {
                zeros++;
            }

            // If valid number of flips, update maxLen
            if (zeros <= k) {
                int len = j - i + 1;
                maxLen = max(maxLen, len);
            } 
            // If zeros exceed k, break early (from your note)
            else {
                break; 
            }
        }
    }

    cout << maxLen << "\n";
    return 0;
}