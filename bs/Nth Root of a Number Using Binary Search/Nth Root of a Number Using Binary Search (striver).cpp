/*
 * Problem: N-th Root of a Number using Binary Search
 * --------------------------------------------------
 * Approach: Floating Point Binary Search on Range [1, m]
 * 
 * Approach Explanation:
 * 1. Define search space: `low = 1.0`, `high = m`.
 * 2. Precision Threshold: `eps = 1e-6` (10^-6) for accuracy up to 6 decimal places.
 * 3. Loop while `(high - low) > eps`:
 *    a. Calculate `mid = (low + high) / 2.0`.
 *    b. Calculate `mid^n` using helper function `multiply(mid, n)`.
 *    c. If `mid^n < m`, answer lies in right half -> set `low = mid`.
 *    d. Else, answer lies in left half -> set `high = mid`.
 * 4. Print or return `low` (or `high`), both will be accurate within 1e-6 limit.
 * 
 * Time Complexity:  O(N * log_2(M * 10^d)) where d is decimal precision.
 * Space Complexity: O(1) Auxiliary Space.
 */
// why binary search works here?
// Binary search works here because the function f(x) = x^n is monotonically increasing
// for x > 0. This means that as x increases, f(x) also increases, allowing us to effectively narrow down the search space for the N-th root of M using binary search.
// anywhere the numbers are monotonically increasing or decreasing, binary search can be applied to find a specific value or threshold efficiently.
#include <iostream>
#include <cmath>

using namespace std;

// Helper function to calculate number^n
double multiply(double number, int n) {
    double ans = 1.0;
    for (int i = 1; i <= n; i++) {
        ans = ans * number;
    }
    return ans;
}

// Function to find N-th root of M
double getNthRoot(int n, int m) {
    double low = 1.0;
    double high = m;
    double eps = 1e-6; // Precision threshold

    while ((high - low) > eps) {
        double mid = (low + high) / 2.0;

        if (multiply(mid, n) < m) {
            low = mid;  // Move right
        } else {
            high = mid; // Move left
        }
    }

    // `low` and `high` converge within `eps` threshold
    cout << "Calculated " << n << "-th root of " << m << " : " << low << endl;
    
    // Check against standard library pow function
    cout << "Verification using pow(): " << pow(m, 1.0 / n) << endl;

    return low;
}

//  Driver Code
int main() {
    int n = 3, m = 27; // 3rd root of 27 is 3.0

    cout << "Finding " << n << "-th root of " << m << "...\n" << endl;
    getNthRoot(n, m);

    return 0;
}