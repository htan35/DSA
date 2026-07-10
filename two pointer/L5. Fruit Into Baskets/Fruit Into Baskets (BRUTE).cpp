// LeetCode 904: Fruit Into Baskets
// Time Complexity: O(n^2)
// Space Complexity: O(1) -> Since set size is at most 3 before breaking
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int totalFruit(vector<int>& fruits) {
        int n = fruits.size();
        int maxlen = 0;

        // Outer loop: choose starting tree
        for (int i = 0; i < n; i++) {
            set<int> st; // Stores types of fruits in current subarray

            // Inner loop: choose ending tree
            for (int j = i; j < n; j++) {
                st.insert(fruits[j]); // Insert current fruit type

                // If we have 2 or fewer types of fruits, update maxlen
                if (st.size() <= 2) {
                    maxlen = max(maxlen, j - i + 1);
                } 
                // Break if we hit a 3rd distinct fruit type
                else {
                    break;
                }
            }
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