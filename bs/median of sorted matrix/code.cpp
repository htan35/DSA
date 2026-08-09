/*
 * Problem: Median in a Row-wise Sorted Matrix
 * -------------------------------------------
 * Approach: Binary Search on Answer Range + Upper Bound per Row
 * 
 * Approach Explanation:
 * 1. Determine Search Range:
 *    - `low`: Min element across all first columns `mat[i][0]`.
 *    - `high`: Max element across all last columns `mat[i][c-1]`.
 * 
 * 2. Binary Search Condition:
 *    - For candidate `mid`, count total elements in matrix <= `mid` using `upperBound`.
 *    - Required elements to the left of median: `req = (r * c) / 2`.
 *    - If `cnt <= req`, `mid` is too small -> `low = mid + 1`.
 *    - Else, `high = mid - 1`.
 * 
 * 3. Return `low` once `low > high` (it converges to the smallest number with > req elements <= it).
 * 
 * Time Complexity:  O(log_2_(10^9) * n * log guess) -> Binary search range takes max ~32 iterations, each counting takes R * log C.
 * Space Complexity: O(1) Auxiliary Space.
 */

#include <iostream>
#include <vector>
#include <climits>
#include <algorithm>

using namespace std;

class Solution {
public:
    // Custom upper_bound helper function: returns count of elements <= target
    int upperBound(const vector<int>& arr, int target) {
        int low = 0;
        int high = arr.size();

        while (low < high) {
            int mid = low + (high - low) / 2;

            if (arr[mid] <= target)
                low = mid + 1;
            else
                high = mid;
        }

        return low;
    }

    int median(vector<vector<int>> &mat) {
        int r = mat.size();
        int c = mat[0].size();

        int low = INT_MAX;
        int high = INT_MIN;

        // Find min and max values in the matrix
        for (int i = 0; i < r; i++) {
            low = min(low, mat[i][0]);
            high = max(high, mat[i][c - 1]);
        }

        int need = (r * c) / 2;

        while (low <= high) {
            int mid = low + (high - low) / 2;

            int cnt = 0;
            // Count elements <= mid across all rows
            for (int i = 0; i < r; i++) {
                cnt += upperBound(mat[i], mid);
            }

            if (cnt <= need)
                low = mid + 1;
            else
                high = mid - 1;
        }

        return low;
    }
};

// 🔹 Driver Code
int main() {
    /*
        Matrix:
        [1, 3, 5]
        [2, 6, 9]
        [3, 6, 9]

        Flattened & Sorted: [1, 2, 3, 3, 5, 6, 6, 9, 9]
        Median (5th element) = 5
    */

    vector<vector<int>> mat = {
        {1, 3, 5},
        {2, 6, 9},
        {3, 6, 9}
    };

    Solution obj;
    cout << "Median of Matrix = " << obj.median(mat) << endl;

    return 0;
}