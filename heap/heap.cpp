#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

// ============================================================================
// CUSTOM HEAP IMPLEMENTATION (1-Based Indexing)
// ============================================================================
class Heap {
public:
    int arr[100];
    int size;

    Heap() {
        arr[0] = -1; // Dummy value for index 0 to enforce 1-based indexing
        size = 0;
    }

    // Approach: Insert an element at the end and bubble it up to keep the max heap property.
    void insert(int val) {
        size = size + 1;
        int index = size;
        arr[index] = val;

        // Bubble up (Heapify-up) to maintain Max Heap property
        while (index > 1) {
            int parent = index / 2;

            if (arr[parent] < arr[index]) {
                swap(arr[parent], arr[index]);
                index = parent;
            } else {
                return;
            }
        }
    }

    // Approach: Remove the root, replace it with the last element, then heapify down.
    void deleteFromHeap() {
        if (size == 0) {
            cout << "nothing to delete" << endl;
            return;
        }

        // Replace root value with the last element
        arr[1] = arr[size];
        size--;

        // Trickle down (Heapify-down) to restore Max Heap property
        int i = 1;
        while (i <= size) {
            int leftIndex = 2 * i;
            int rightIndex = 2 * i + 1;
            int largest = i;

            if (leftIndex <= size && arr[largest] < arr[leftIndex]) {
                largest = leftIndex;
            }
            if (rightIndex <= size && arr[largest] < arr[rightIndex]) {
                largest = rightIndex;
            }

            if (largest != i) {
                swap(arr[i], arr[largest]);
                i = largest;
            } else {
                return;
            }
        }
    }

    void print() {
        for (int i = 1; i <= size; i++) {
            cout << arr[i] << " ";
        }
        cout << endl;
    }
};

// ============================================================================
// HEAPIFY OPERATIONS
// ============================================================================

// Approach: Heapify down a 1-based array to restore the max heap property.
void heapify(int arr[], int n, int i) {
    int largest = i;
    int left = 2 * i;
    int right = 2 * i + 1;

    if (left <= n && arr[largest] < arr[left]) {
        largest = left;
    }
    if (right <= n && arr[largest] < arr[right]) {
        largest = right;
    }

    if (largest != i) {
        swap(arr[largest], arr[i]);
        heapify(arr, n, largest);
    }
}

// Approach: Heapify down a 0-based vector to restore the min heap property.
void minHeapify(vector<int> &arr, int n, int i) {
    int smallest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && arr[smallest] > arr[left]) {
        smallest = left;
    }
    if (right < n && arr[smallest] > arr[right]) {
        smallest = right;
    }

    if (smallest != i) {
        swap(arr[smallest], arr[i]);
        minHeapify(arr, n, smallest);
    }
}

// Approach: Build a min heap by heapifying all non-leaf nodes from bottom to top.
vector<int> buildMinHeap(vector<int> &arr) {
    int n = arr.size();
    // Start from the last non-leaf node down to the root
    for (int i = n / 2 - 1; i >= 0; i--) {
        minHeapify(arr, n, i);
    }
    return arr;
}

// Approach: Use max heapify repeatedly to sort the array in place.
void heapSort(int arr[], int n) {
    int size = n;

    while (size > 1) {
        // Step 1: Swap root (largest element) with the last element
        swap(arr[size], arr[1]);
        // Step 2: Reduce the virtual size of the heap
        size--;
        // Step 3: Call heapify on the new root to restore max heap structural properties
        heapify(arr, size, 1);
    }
}

// ============================================================================
// MAIN EXECUTION CONTEXT
// ============================================================================
int main() {
    // ------------------------------------------------------------------------
    // Approach: Demonstrate custom heap operations and array heapify.
    // ------------------------------------------------------------------------
    cout << "--- Custom Max Heap Operations ---" << endl;
    Heap h;
    h.insert(50);
    h.insert(55);
    h.insert(53);
    h.insert(52);
    h.insert(54);
    cout << "Heap elements after inserts: ";
    h.print(); // Expected output shows a valid max heap arrangement

    h.deleteFromHeap();
    cout << "Heap elements after deleting root: ";
    h.print();
    cout << endl;

    cout << "--- In-Place Array Building via Heapify ---" << endl;
    int arr[6] = {-1, 54, 53, 55, 52, 50}; // 1-based array representation
    int n = 5;
    for (int i = n / 2; i > 0; i--) {
        heapify(arr, n, i);
    }
    cout << "Printing the heapified array now: ";
    for (int i = 1; i <= n; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;

    // Approach: Perform heap sort on the 1-based array.
    heapSort(arr, n);
    cout << "Printing sorted array after Heap Sort: ";
    for (int i = 1; i <= n; i++) {
        cout << arr[i] << " ";
    }
    cout << "\n\n";

    // ------------------------------------------------------------------------
    // Approach: Demonstrate STL priority_queue as a max heap.
    // ------------------------------------------------------------------------
    cout << "--- STL priority_queue (Max-Heap) ---" << endl;
    priority_queue<int> pq;
    pq.push(4);
    pq.push(2);
    pq.push(5);
    pq.push(3);

    cout << "element at Top: " << pq.top() << endl; // Should be 5
    pq.pop();
    cout << "element at Top: " << pq.top() << endl; // Should be 4
    cout << "Size is: " << pq.size() << endl;
    if (pq.empty()) {
        cout << "pq is empty" << endl;
    } else {
        cout << "pq is not empty" << endl;
    }
    cout << endl;

    // ------------------------------------------------------------------------
    // Approach: Demonstrate STL priority_queue as a min heap.
    // ------------------------------------------------------------------------
    cout << "--- STL priority_queue (Min-Heap) ---" << endl;
    priority_queue<int, vector<int>, greater<int>> minheap;
    minheap.push(4);
    minheap.push(2);
    minheap.push(5);
    minheap.push(3);

    cout << "element at Top: " << minheap.top() << endl; // Should be 2
    minheap.pop();
    cout << "element at Top: " << minheap.top() << endl; // Should be 3
    cout << "Size is: " << minheap.size() << endl;
    if (minheap.empty()) {
        cout << "minheap is empty" << endl;
    } else {
        cout << "minheap is not empty" << endl;
    }

    return 0;
}