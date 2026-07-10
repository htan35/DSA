// LONGEST SUBARRAY WITH SUM <= K (SLIDING WINDOW)
//Time Complexity: O(n+n)
//Space Complexity: O(1)
#include <bits/stdc++.h>
using namespace std;

int main() {
    vector<int> arr = {2, 5, 1, 10, 10};
    int K = 14;
    int n = arr.size();

    int l = 0, r = 0;
    int sum = 0;
    int maxLen = 0;

    // Expand the window using the right pointer
    while (r < n) {
        sum += arr[r]; // Add current element

        // Shrink the window from left if sum exceeds K
        while (sum > K) {
            sum -= arr[l];
            l++;
        }

        // Check and update max length if condition is valid
        if (sum <= K) {
            maxLen = max(maxLen, r - l + 1);
        }

        r++; // Move right pointer forward
    }

    cout << maxLen << "\n";
    return 0;
}