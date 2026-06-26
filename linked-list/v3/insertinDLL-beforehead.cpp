// LeetCode: Insert a Node Before Head of a Doubly Linked List
// Time Complexity: O(1)
// Space Complexity: O(1)
#include <iostream>
#include <bits/stdc++.h>
using namespace std;

class Node {
public:
    int data;
    Node* next;
    Node* back;
    
    Node(int data1) {
        data = data1;
        next = nullptr;
        back = nullptr;
    }
    
    Node(int data1, Node* next1, Node* back1) {
        data = data1;
        next = next1;
        back = back1;
    }
};

// Helper function to convert a vector into a Doubly Linked List
Node* convertArr2DLL(vector<int> &arr) {
    if (arr.empty()) return nullptr;
    Node* head = new Node(arr[0]);
    Node* prev = head;
    for (int i = 1; i < arr.size(); i++) {
        Node* temp = new Node(arr[i], nullptr, prev);
        prev->next = temp;
        prev = temp;
    }
    return head;
}

// Helper function to print the doubly linked list forward
void print(Node* head) {
    while (head != nullptr) {
        cout << head->data << " ";
        head = head->next;
    }
    cout << "\n";
}

// Function to insert a new node before the head of a Doubly Linked List
Node* insertBeforeHead(Node* head, int val) {
    // Create a new node with 'next' pointing to the old head and 'back' pointing to nullptr
    Node* newHead = new Node(val, head, nullptr);
    
    // If the original list was not empty, link the old head's back pointer to the new head
    if (head != nullptr) {
        head->back = newHead;
    }
    
    return newHead;
}

int main() {
    vector<int> arr = {12, 5, 8, 7};
    Node* head = convertArr2DLL(arr);
    
    head = insertBeforeHead(head, 10); // Inserts 10 before the head node (12)
    print(head);                       // Outputs: 10 12 5 8 7
    
    return 0;
}