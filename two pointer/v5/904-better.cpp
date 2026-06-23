// LeetCode 904: Fruit Into Baskets (SLIDING WINDOW)
// Time Complexity: O(n)
// Space Complexity: O(1) -> Since map size is at most 3
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int totalFruit(vector<int>& fruits) {
        int n = fruits.size();
        int maxlen = 0;
        unordered_map<int, int> umpp; // Stores frequency of fruit types in current window

        int l = 0;
        int r = 0;

        // Expand the window
        while (r < n) {
            umpp[fruits[r]]++; // Include rightmost fruit

            // Shrink window if map size exceeds 2 distinct fruit types
            while (umpp.size() > 2) {
                umpp[fruits[l]]--; // Decrease frequency of leftmost fruit
                
                // If frequency becomes 0, remove the fruit type from map
                if (umpp[fruits[l]] == 0) {
                    umpp.erase(fruits[l]);
                }
                l++; // Move left pointer forward
            }

            // Update maxlen for valid window
            maxlen = max(maxlen, r - l + 1);
            r++; // Move right pointer forward
        }

        return maxlen;
    }
};

int main() {
    Solution sol;
    vector<int> fruits = {1, 2, 1, 2, 3};
    cout << sol.totalFruit(fruits) << "\n";
    return 0;
}