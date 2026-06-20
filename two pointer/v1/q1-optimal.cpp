// LONGEST Length of SUBARRAY WITH SUM <= K (OPTIMIZED SLIDING WINDOW WITH IF-STATEMENT)
#include <bits/stdc++.h>
using namespace std;

int main() {
    vector<int> arr = {2, 5, 1, 10, 10}; // Example from previous image
    int K = 14;
    int n = arr.size();

    int l = 0, r = 0;
    int sum = 0;
    int maxLen = 0;

    // Outer loop: expand the window
    while (r < n) {
        sum += arr[r]; // Add current element

        // Single 'if' check instead of a inner while loop
        if (sum > K) {
            sum -= arr[l];
            l++;
        }

        // Check and update max length if condition holds
        if (sum <= K) {
            maxLen = max(maxLen, r - l + 1);
        }

        r++; // Move right pointer forward
    }

    cout << maxLen << "\n";
    return 0;
}