// LeetCode: Implement Stack using Linked List
// Time Complexity: O(1) for all operations
// Space Complexity: O(N) where N is the number of elements currently in the stack
#include <iostream>
#include <bits/stdc++.h>
using namespace std;

class Node {
public:
    int data;
    Node* next;
    Node(int val) {
        data = val;
        next = nullptr;
    }
};

class ST {
private:
    Node* topNode; // Points to the top node of the stack
    int sizeVal;   // Keeps track of the current number of elements

public:
    // Constructor to initialize an empty stack
    ST() {
        topNode = nullptr;
        sizeVal = 0;
    }

    // Function to add an element x to the stack
    void push(int x) {
        Node* temp = new Node(x);
        temp->next = topNode;
        topNode = temp;
        sizeVal = sizeVal + 1;
    }

    // Function to remove the top element from the stack
    void pop() {
        if (topNode == nullptr) {
            cout << "Stack Underflow\n";
            return;
        }
        Node* temp = topNode;
        topNode = topNode->next;
        delete temp;
        sizeVal = sizeVal - 1;
    }

    // Function to get the top element's data
    int top() {
        if (topNode == nullptr) {
            cout << "Stack is empty\n";
            return -1;
        }
        return topNode->data;
    }

    // Function to return the current size of the stack
    int size() {
        return sizeVal;
    }

    // Destructor to clear out remaining nodes from memory
    ~ST() {
        while (topNode != nullptr) {
            Node* temp = topNode;
            topNode = topNode->next;
            delete temp;
        }
    }
};

int main() {
    ST stack;

    stack.push(10);
    stack.push(20);
    stack.push(30);

    cout << "Top element: " << stack.top() << "\n";  // Outputs: 30
    cout << "Stack size: " << stack.size() << "\n";  // Outputs: 3

    stack.pop();
    cout << "Top element after pop: " << stack.top() << "\n"; // Outputs: 20
    cout << "New stack size: " << stack.size() << "\n";       // Outputs: 2

    return 0;
}