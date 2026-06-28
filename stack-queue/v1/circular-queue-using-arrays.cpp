// LeetCode: Implement Queue using Arrays (Circular Queue Implementation)
// Time Complexity: O(1) for all operations
// Space Complexity: O(N) where N is the total capacity of the queue
#include <iostream>
#include <bits/stdc++.h>
using namespace std;

class Queue {
private:
    int* q;
    int maxSize;
    int curSize;
    int start;
    int end;

public:
    // Constructor to initialize the circular queue
    Queue(int size = 10) {
        maxSize = size;
        q = new int[maxSize];
        curSize = 0;
        start = -1;
        end = -1;
    }

    // Function to add an element x to the queue (Enqueuing)
    void push(int x) {
        // Check if queue is full
        if (curSize == maxSize) {
            cout << "Queue is Full\n";
            return;
        }

        // If inserting the very first element
        if (curSize == 0) {
            start = 0;
            end = 0;
        } else {
            // Circularly increment the end index
            end = (end + 1) % maxSize;
        }

        q[end] = x;
        curSize += 1;
    }

    // Function to remove the front element from the queue (Dequeuing)
    int pop() {
        // Check if queue is empty
        if (curSize == 0) {
            cout << "Queue is Empty\n";
            return -1;
        }

        int el = q[start];

        // If only one element was left, reset pointers
        if (curSize == 1) {
            start = -1;
            end = -1;
        } else {
            // Circularly increment the start index
            start = (start + 1) % maxSize;
        }

        curSize -= 1;
        return el;
    }

    // Function to return the top/front element of the queue
    int top() {
        if (curSize == 0) {
            cout << "Queue is Empty\n";
            return -1;
        }
        return q[start];
    }

    // Function to return the current size of the queue
    int size() {
        return curSize;
    }

    // Destructor to clean up memory
    ~Queue() {
        delete[] q;
    }
};

int main() {
    Queue queue(10); // Create a queue of capacity 10

    queue.push(5);
    queue.push(10);
    queue.push(15);

    cout << "Front element: " << queue.top() << "\n";  // Outputs: 5
    cout << "Queue size: " << queue.size() << "\n";    // Outputs: 3

    cout << "Popped: " << queue.pop() << "\n";         // Outputs: 5
    cout << "New Front element: " << queue.top() << "\n"; // Outputs: 10

    return 0;
}