// LeetCode: Insertion Sort (Standard Sorting Algorithm)
// Time Complexity: O(n^2)
// Space Complexity: O(1)
//Takes the current element and places it in its correct position in the sorted part of the array by shifting elements.
#include <bits/stdc++.h>
using namespace std;

void insertion_sort(int a[], int n) {
    // Outer loop: pick elements from index 0 to n-1
    for (int i = 0; i <= n - 1; i++) {
        int j = i; // Start from the picked element index

        // Inner loop: shift elements back into their correct sorted position
        while (j > 0 && a[j - 1] > a[j]) {
            swap(a[j - 1], a[j]);
            j--; // Move backwards
        }
    }
}

int main() {
    int a[] = {14, 9, 15, 12, 6, 8, 13};
    int n = sizeof(a) / sizeof(a[0]);

    insertion_sort(a, n);

    for (int i = 0; i < n; i++) {
        cout << a[i] << " ";
    }
    cout << "\n";
    return 0;
}