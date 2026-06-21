// LONGEST SUBSTRING WITHOUT REPEATING CHARACTERS (BRUTE FORCE USING HASH ARRAY)
// Time Complexity: O(n^2)
// Space Complexity: O(256) -> O(1) constant space
//LEETCODE 3

#include <bits/stdc++.h>
using namespace std;

int main() {
    string s = "cadbzabcd";
    int n = s.length();
    
    int maxLen = 0;

    // Outer loop: choose starting character
    for (int i = 0; i < n; i++) {
        // Initialize hash array to tracking visited characters in the current substring
        int hash[256] = {0};

        // Inner loop: choose ending character
        for (int j = i; j < n; j++) {
            
            // If character is already seen, current substring is invalid -> break
            if (hash[s[j]] == 1) {
                break;
            }

            int len = j - i + 1;
            maxLen = max(len, maxLen);
            
            // Mark the character as seen
            hash[s[j]] = 1;
        }
    }

    cout << maxLen << "\n";
    return 0;
}