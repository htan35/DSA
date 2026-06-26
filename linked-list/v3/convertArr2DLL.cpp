// LeetCode: Convert Array to Doubly Linked List
// Time Complexity: O(n)
// Space Complexity: O(n) -> For creating 'n' nodes of the doubly linked list
#include <iostream>
#include <bits/stdc++.h>
using namespace std;

class Node {
public:
    int data;
    Node* next;
    Node* back; // Pointer to the previous node

public:
    // Constructor with data, next pointer, and back pointer
    Node(int data1, Node* next1, Node* back1) {
        data = data1;
        next = next1;
        back = back1;
    }

    // Constructor with data only (pointers initialized to nullptr)
    Node(int data1) {
        data = data1;
        next = nullptr;
        back = nullptr;
    }
};

// Function to convert a vector into a Doubly Linked List
Node* convertArr2DLL(vector<int> &arr) {
    if (arr.empty()) return nullptr;

    // Create the head node with the first element
    Node* head = new Node(arr[0]);
    Node* prev = head;

    // Iterate from the second element to the end of the array
    for (int i = 1; i < arr.size(); i++) {
        // Create a new node linking its back pointer to 'prev'
        Node* temp = new Node(arr[i], nullptr, prev); //connect to previous node "prev"
        prev->next = temp; // Link the next pointer of the previous node to 'temp'
        prev = temp;       // Move 'prev' pointer forward to the current node
    }
    return head;
}

// Function to print the doubly linked list forward
void print(Node* head) {
    while (head != nullptr) {
        cout << head->data << " ";
        head = head->next;
    }
    cout << "\n";
}

int main() {
    vector<int> arr = {12, 5, 8, 7};
    Node* head = convertArr2DLL(arr);
    
    print(head); // Outputs: 12 5 8 7
    return 0;
}