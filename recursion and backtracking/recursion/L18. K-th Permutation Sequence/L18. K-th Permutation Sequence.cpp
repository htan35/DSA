/*
 * Problem: Permutation Sequence / K-th Permutation Sequence (LeetCode 60)
 * ---------------------------------------------------------------------
 * Approach: Mathematical Direct Construction via Factorials (O(N^2) instead of O(N!))
 * 
 * Approach Explanation:
 * 1. Generating all permutations takes O(N! * N), which TLEs for larger N. 
 *    Instead, we determine each digit position-by-position using factorial blocks.
 * 2. Precomputation:
 *    - Store digits `[1, 2, ..., n]` in a list/vector `numbers`.
 *    - Compute `fact = (n - 1)!`, which represents how many permutations start with each number.
 * 3. 0-based Indexing:
 *    - Convert `k` to 0-based index: `k = k - 1`.
 * 4. Digit Extraction Loop:
 *    - The current digit index is `k / fact`. Append `numbers[k / fact]` to `ans`.
 *    - Erase the picked digit from `numbers` to prevent reuse.
 *    - If `numbers` becomes empty, break.
 *    - Update `k = k % fact` (offset inside the block).
 *    - Update `fact = fact / numbers.size()` to get the block size for the next position.
 * 
 * Time Complexity:  O(N^2) - N positions to determine, each vector erase takes O(N).
 * Space Complexity: O(N)   - Auxiliary storage for `numbers` array and result string.
 */

#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Solution {
public:
    string getPermutation(int n, int k) {
        int fact = 1;
        vector<int> numbers;

        // Compute (n-1)! and initialize numbers array with [1, 2, ..., n-1]
        for (int i = 1; i < n; i++) {
            fact = fact * i;
            numbers.push_back(i);
        }
        // Include n in numbers: [1, 2, ..., n]
        numbers.push_back(n);

        string ans = "";
        k = k - 1; // Convert 1-based k to 0-based index

        while (true) {
            // Determine which number falls at the current position
            ans = ans + to_string(numbers[k / fact]);

            // Remove used number from available pool
            numbers.erase(numbers.begin() + k / fact);

            // When no numbers are left, permutation is complete
            if (numbers.size() == 0) {
                break;
            }

            // Update k and factorial for the next digit position
            k = k % fact;
            fact = fact / numbers.size();
        }

        return ans;
    }
};

// 🔹 Driver Code
int main() {
    /*
        Example: n = 4, k = 17
        All permutations starting with:
        - '1': 6 permutations (indices 0-5)
        - '2': 6 permutations (indices 6-11)
        - '3': 6 permutations (indices 12-17) -> 17th falls here!
        Result: "3412"
    */

    int n = 4, k = 17;
    Solution obj;
    string result = obj.getPermutation(n, k);

    cout << "The " << k << "-th permutation for n = " << n << " is: " << result << endl;

    return 0;
}
