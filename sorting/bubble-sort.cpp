// LeetCode: Bubble Sort (Standard Sorting Algorithm)
// Time Complexity: O(n^2)
// Space Complexity: O(1)
//Takes the maximum element by adjacent swaps and pushes it to the end of the unsorted part .
#include <bits/stdc++.h>
using namespace std;

void bubble_sort(int arr[], int n) {
    // Outer loop: controls the unsorted range boundary from back to front
    for (int i = n - 1; i >= 1; i--) {
        
        // Inner loop: pushes the maximum element in range [0...i] to the end
        for (int j = 0; j <= i - 1; j++) {
            
            // Swap if current element is greater than the next element
            if (arr[j] > arr[j + 1]) {
                int temp = arr[j + 1];
                arr[j + 1] = arr[j];
                arr[j] = temp;
            }
        }
    }
}

int main() {
    int arr[] = {13, 46, 24, 52, 20, 9};
    int n = sizeof(arr) / sizeof(arr[0]);

    bubble_sort(arr, n);

    for (int i = 0; i < n; i++) {
        cout << arr[i] << " ";
    }
    cout << "\n";
    return 0;
}