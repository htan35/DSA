// LeetCode: Implement Stack using Arrays (Standard Data Structure Implementation)
// Time Complexity: O(1) for all operations
// Space Complexity: O(N) where N is the maximum size of the stack
#include <iostream>
#include <bits/stdc++.h>
using namespace std;

class MyStack {
private:
    int topIndex;
    int maxSize;
    int* st;

public:
    // Constructor to initialize the stack
    MyStack(int size = 10) {
        maxSize = size;
        st = new int[maxSize];
        topIndex = -1; // Stack is initially empty
    }

    // Function to add an element x to the stack
    void push(int x) {
        // Check for stack overflow condition
        if (topIndex >= maxSize - 1) {
            cout << "Stack Overflow\n";
            return;
        }
        topIndex = topIndex + 1;
        st[topIndex] = x;
    }

    // Function to remove the top element from the stack
    void pop() {
        // Check for stack underflow condition
        if (topIndex == -1) {
            cout << "Stack Underflow\n";
            return;
        }
        topIndex = topIndex - 1;
    }

    // Function to return the top element of the stack
    int top() {
        if (topIndex == -1) {
            cout << "Stack is empty\n";
            return -1;
        }
        return st[topIndex];
    }

    // Function to return the current size of the stack
    int size() {
        return topIndex + 1;
    }

    // Destructor to free up allocated memory
    ~MyStack() {
        delete[] st;
    }
};

int main() {
    MyStack s(10); // Create a stack of max capacity 10
    
    s.push(2);
    s.push(3);
    s.push(4);
    
    cout << "Top element: " << s.top() << "\n";  // Outputs: 4
    cout << "Stack size: " << s.size() << "\n";  // Outputs: 3
    
    s.pop();
    cout << "Top element after pop: " << s.top() << "\n"; // Outputs: 3
    
    return 0;
}