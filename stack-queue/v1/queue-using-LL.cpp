// LeetCode: Implement Queue using Linked List
// Time Complexity: O(1) for all operations
// Space Complexity: O(N) where N is the current number of elements in the queue
#include <iostream>
#include <bits/stdc++.h>
using namespace std;

class Node {
public:
    int val;
    Node* next;
    Node(int x) {
        val = x;
        next = nullptr;
    }
};

class Queue {
private:
    Node* start;
    Node* end;
    int size;

public:
    // Constructor matching the initial state initialization
    Queue() {
        start = nullptr;
        end = nullptr;
        size = 0;
    }

    // Function to add an element x to the back of the queue
    void push(int x) {
        Node* temp = new Node(x);

        if (start == nullptr) {
            start = end = temp;
        } else {
            end->next = temp;
            end = temp; // <-- FIX: Update the end pointer to point to the new last element
        }

        size += 1;
    }

    // Function to remove the front element from the queue
    void pop() {
        if (start == nullptr) {
            cout << "Queue Underflow\n";
            return;
        }

        Node* temp = start;
        start = start->next;
        
        // If the queue becomes empty after popping, reset end pointer to nullptr
        if (start == nullptr) {
            end = nullptr;
        }

        delete temp;
        size -= 1;
    }

    // Function to get the front element's value
    int top() {
        if (start == nullptr) {
            cout << "Queue is Empty\n";
            return -1;
        }
        return start->val;
    }

    // Function to get the active item count
    int size_func() {
        return size;
    }

    // Destructor to clear remaining memory allocation
    ~Queue() {
        while (start != nullptr) {
            Node* temp = start;
            start = start->next;
            delete temp;
        }
    }
};

int main() {
    Queue q;

    q.push(10);
    q.push(20);
    q.push(30);

    cout << "Front element: " << q.top() << "\n";       // Outputs: 10
    cout << "Queue size: " << q.size_func() << "\n";    // Outputs: 3

    q.pop();
    cout << "Front element after pop: " << q.top() << "\n"; // Outputs: 20
    cout << "New queue size: " << q.size_func() << "\n";    // Outputs: 2

    return 0;
}