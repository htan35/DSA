// LONGEST SUBSTRING WITHOUT REPEATING CHARACTERS (OPTIMIZED SLIDING WINDOW WITH HASH MAP)
// Time Complexity: O(n)
// Space Complexity: O(256) -> O(1) constant space
#include <bits/stdc++.h>
using namespace std;

int main() {
    string s = "cadbzabcd"; // Example from previous image
    int n = s.length();

    int l = 0, r = 0;
    int maxLen = 0;

    // Initialize hash array with -1 to indicate unseen characters
    vector<int> hash(256, -1);

    while (r < n) {
        // If character exists in the map
        if (hash[s[r]] != -1) {
            // Move left pointer forward if the duplicate is inside current window
            if (hash[s[r]] >= l) {
                l = hash[s[r]] + 1;
            }
        }

        int len = r - l + 1;
        maxLen = max(len, maxLen);

        // Update / store the latest index of the character
        hash[s[r]] = r;
        r++;
    }

    cout << maxLen << "\n";
    return 0;
}