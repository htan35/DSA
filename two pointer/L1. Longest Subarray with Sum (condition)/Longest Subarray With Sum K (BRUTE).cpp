//LONGEST SUBARRAY WITH SUM K
#include <bits/stdc++.h>
using namespace std;

int main() {
    vector<int> arr = {2, 5, 1, 7, 10};
    int K = 14;
    int n = arr.size();

    int maxLen = 0;

    // Outer loop: choose starting point
    for (int i = 0; i < n; i++) {
        int sum = 0;
        
        // Inner loop: choose ending point
        for (int j = i; j < n; j++) {
            sum += arr[j]; // Add current element
            
            // Check if valid condition is met
            if (sum <= K) {
                maxLen = max(maxLen, j - i + 1); // Update max length
            }
            else if(sum > K) {
                break; // No need to continue if sum exceeds K
            }
        }
    }

    cout << maxLen << "\n";
    return 0;
}