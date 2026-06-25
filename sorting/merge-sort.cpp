// LeetCode: Merge Sort (Standard Sorting Algorithm)
// Time Complexity: O(n log n)
// Space Complexity: O(n)
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    // Function to merge two sorted segments of the array
    void merge(vector<int>& arr, int low, int mid, int high) {
        vector<int> temp; // Temporary vector to hold merged result
        int left = low, right = mid + 1;

        // Compare elements from both halves and pick the smaller one
        while (left <= mid && right <= high) {
            if (arr[left] <= arr[right]) {
                temp.push_back(arr[left++]);
            } else {
                temp.push_back(arr[right++]);
            }
        }

        // Copy remaining elements from the left half if any
        while (left <= mid) {
            temp.push_back(arr[left++]);
        }

        // Copy remaining elements from the right half if any
        while (right <= high) {
            temp.push_back(arr[right++]);
        }

        // Transfer sorted elements from temp back into the original array
        for (int i = low; i <= high; i++) {
            arr[i] = temp[i - low];
        }
    }

    // Recursive function to divide and sort the array
    void mergeSort(vector<int>& arr, int low, int high) {
        // Base case: segment has 1 element or invalid indices
        if (low >= high) {
            return;
        }

        int mid = (low + high) / 2; // Split point

        mergeSort(arr, low, mid);      // Sort left half
        mergeSort(arr, mid + 1, high); // Sort right half
        merge(arr, low, mid, high);    // Merge sorted halves
    }
};

int main() {
    vector<int> arr = {5, 2, 8, 4, 1};
    Solution sol;
    
    sol.mergeSort(arr, 0, arr.size() - 1);
    
    for (int x : arr) {
        cout << x << " ";
    }
    cout << "\n";
    return 0;
}