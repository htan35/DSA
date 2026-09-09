/*
 * Problem: Aggressive Cows (Binary Search on Answer)
 * --------------------------------------------------
 * Approach: Binary Search on Min Distance Range [1, max(stalls) - min(stalls)]
 * 
 * Approach Explanation:
 * 1. The problem asks for the maximum possible minimum distance between any two cows.
 * 2. Sorting:
 *    - First sort the `stalls` array so we can greedily place cows left-to-right.
 * 3. Search Space for Distance:
 *    - `low = 1` (minimum possible separation).
 *    - `high = stalls[n - 1] - stalls[0]` (maximum possible separation between first and last stall).
 * 4. Greedy Validator (`canWePlace`):
 *    - Always place the 1st cow in `stalls[0]`.
 *    - For each subsequent stall, place a cow if `stalls[i] - last >= dist`.
 *    - If at any point `cntCows >= cows`, return true.
 *    - If we finish the stalls with fewer cows placed, return false.
 * 5. Binary Search:
 *    - If `dist = mid` is valid: we try for a larger distance -> `low = mid + 1`.
 *    - If not valid: reduce distance -> `high = mid - 1`.
 *    - Since `high` always points to the last valid distance when the loop terminates, return `high`.
 * 
 * Time Complexity:  O(N * log N + N * log(max_dist - min_dist))
 * Space Complexity: O(1) Auxiliary Space.
 */

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
private:
    bool canWePlace(const vector<int>& stalls, int dist, int cows) {
        int cntCows = 1;
        int last = stalls[0];

        for (size_t i = 1; i < stalls.size(); i++) {
            if (stalls[i] - last >= dist) {
                cntCows++;
                last = stalls[i];
            }
            if (cntCows >= cows) return true;
        }

        return false;
    }

public:
    int aggressiveCows(vector<int>& stalls, int k) {
        // Sort stalls to allow greedy placement
        sort(stalls.begin(), stalls.end());

        int n = stalls.size();
        int low = 1;
        int high = stalls[n - 1] - stalls[0];

        while (low <= high) {
            int mid = low + (high - low) / 2;

            if (canWePlace(stalls, mid, k)) {
                // Feasible distance found, try to maximize
                low = mid + 1;
            } else {
                // Distance too large, decrease upper bound
                high = mid - 1;
            }
        }

        return high;
    }
};

// 🔹 Driver Code
int main() {
    /*
        Stalls: [0, 3, 4, 7, 10, 9]
        Cows (k): 4

        Sorted Stalls: [0, 3, 4, 7, 9, 10]
        Placing 4 cows at positions: 0, 3, 7, 10 gives min distance = 3
    */

    vector<int> stalls = {0, 3, 4, 7, 10, 9};
    int k = 4;

    Solution obj;
    int maxMinDist = obj.aggressiveCows(stalls, k);

    cout << "Largest minimum distance: " << maxMinDist << endl;

    return 0;
}