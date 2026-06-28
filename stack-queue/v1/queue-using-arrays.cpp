// Data Structure: Standard Linear Queue using Arrays
// Time Complexity: O(1) for all operations
// Space Complexity: O(N) where N is the total capacity of the queue
#include <iostream>
#include <bits/stdc++.h>
using namespace std;

class Queue {
private:
    int size;       // Total maximum capacity
    int* q;         // Array representation of the queue
    int curSize;    // Keeps track of the current number of elements
    int start;      // Points to the front element index
    int end;        // Points to the rear element index

public:
    // Constructor using your initial configurations
    Queue() {
        size = 10;
        q = new int[size];
        curSize = 0;
        start = -1;
        end = -1;
    }

    // Function to add an element x to the linear queue
    void push(int n) {
        // Queue is full when end pointer reaches the last index of the array
        if (end == size - 1) {
            cout << "Queue is Full\n";
            return;
        }

        // If inserting the very first element
        if (curSize == 0) {
            start = 0;
            end = 0;
        } else {
            // Move end pointer forward linearly
            end = end + 1;
        }

        q[end] = n;
        curSize += 1;
    }

    // Function to remove the front element from the linear queue
    int pop() {
        if (curSize == 0) {
            cout << "Queue is Empty\n";
            return -1;
        }

        int el = q[start];

        // If only one element was left, reset pointers back to -1
        if (curSize == 1) {
            start = -1;
            end = -1;
        } else {
            // Move start pointer forward linearly
            start = start + 1;
        }

        curSize -= 1;
        return el;
    }

    // Function to view the top/front element of the queue
    int top() {
        if (curSize == 0) {
            cout << "Queue is Empty\n";
            return -1;
        }
        return q[start];
    }

    // Function to get the active count of items
    int size_func() {
        return curSize;
    }

    ~Queue() {
        delete[] q;
    }
};

int main() {
    Queue queue; // Create standard linear queue of size 10

    queue.push(5);
    queue.push(10);
    queue.push(15);

    cout << "Front element: " << queue.top() << "\n";       // Outputs: 5
    cout << "Queue size: " << queue.size_func() << "\n";    // Outputs: 3

    cout << "Popped: " << queue.pop() << "\n";              // Outputs: 5
    cout << "New Front element: " << queue.top() << "\n";     // Outputs: 10

    return 0;
}