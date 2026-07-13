// LeetCode: Selection Sort (Standard Sorting Algorithm)
// Time Complexity: O(n^2)
// Space Complexity: O(1)
//Takes first element as minimum and then finds the absolute minimum in the remaining unsorted array and swaps it with the first element of unsorted part.
#include <bits/stdc++.h>
using namespace std;

void selection_sort(int arr[], int n) {
    // Outer loop: boundary moves one by one
    for (int i = 0; i <= n - 2; i++) {
        int mini = i; // Assume current index has the minimum value

        // Inner loop: find the absolute minimum in the remaining unsorted array
        for (int j = i; j <= n - 1; j++) {
            if (arr[j] < arr[mini]) {
                mini = j; // Update index of minimum element
            }
        }

        // Swap the found minimum element with the first element of unsorted part
        int temp = arr[mini];
        arr[mini] = arr[i];
        arr[i] = temp;
    }
}

int main() {
    int arr[] = {64, 25, 12, 22, 11};
    int n = sizeof(arr) / sizeof(arr[0]);

    selection_sort(arr, n);

    for (int i = 0; i < n; i++) {
        cout << arr[i] << " ";
    }
    cout << "\n";
    return 0;
}