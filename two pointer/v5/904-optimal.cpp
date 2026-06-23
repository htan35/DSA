// LeetCode 340: Longest Substring with At Most K Distinct Characters
// (Or equivalent Array variation: Longest Subarray with At Most K Distinct Elements)
// Time Complexity: O(n)
// Space Complexity: O(k)
#include <bits/stdc++.h>
using namespace std;

int longestSubarrayAtMostKDistinct(vector<int>& arr, int k) {
    int n = arr.size();
    int l = 0, r = 0, maxlen = 0;
    unordered_map<int, int> mpp; // Frequency map for tracking distinct elements

    // Expand the window
    while (r < n) {
        mpp[arr[r]]++; // Include rightmost element

        // Single 'if' instead of 'while' to maintain maximum window size
        if (mpp.size() > k) {
            mpp[arr[l]]--; // Decrease frequency of leftmost element
            
            // If element frequency drops to 0, erase it from map
            if (mpp[arr[l]] == 0) {
                mpp.erase(arr[l]);
            }
            l++; // Move left pointer forward once
        }

        // Update maximum length when window size is valid
        if (mpp.size() <= k) {
            maxlen = max(maxlen, r - l + 1);
        }

        r++; // Move right pointer forward
    }

    return maxlen;
}

int main() {
    vector<int> arr = {3, 3, 3, 1, 2, 1, 1, 2, 3, 3, 4};
    int k = 2; // Example k value matching Fruit Into Baskets variation
    cout << longestSubarrayAtMostKDistinct(arr, k) << "\n";
    return 0;
}