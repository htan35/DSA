//from left find the first element which is greater than pivot and from right find the first element which is smaller than pivot and swap them. 
//Repeat this process until left index crosses right index. 
//Finally swap the pivot with the element at right index.

// LeetCode: Quick Sort (Standard Sorting Algorithm)
// Time Complexity: O(n log n) average, O(n^2) worst case
// Space Complexity: O(log n) auxiliary stack space


//IMPORTANT: if you want any other element as pivot, change these 2 lines in partition function
// int pivot = arr[x]; // Choosing the x element
// swap(arr[x], arr[j]);



#include <bits/stdc++.h>
using namespace std;

// Partition function to position the pivot correctly
int partition(vector<int>& arr, int low, int high) {
    int pivot = arr[low]; // Choosing the first element as pivot
    int i = low;
    int j = high;

    while (i < j) {
        // Move i forward while elements are smaller than or equal to pivot
        while (arr[i] <= pivot && i <= high - 1) {
            i++;
        }
        // Move j backward while elements are strictly greater than pivot
        while (arr[j] > pivot && j >= low + 1) {
            j--;
        }
        // If pointers haven't crossed, swap elements
        if (i < j) {
            swap(arr[i], arr[j]);
        }
    }

    // Place pivot at its final sorted index j
    swap(arr[low], arr[j]);
    return j;
}

// Recursive Quick Sort function
void quickSort(vector<int>& arr, int low, int high) {
    if (low < high) {
        int pIndex = partition(arr, low, high); // Get partition index
        quickSort(arr, low, pIndex - 1);        // Sort left subarray
        quickSort(arr, pIndex + 1, high);       // Sort right subarray
    }
}

int main() {
    vector<int> arr = {4, 6, 2, 5, 7, 9, 1, 3};
    quickSort(arr, 0, arr.size() - 1);

    for (int x : arr) {
        cout << x << " ";
    }
    cout << "\n";
    return 0;
}