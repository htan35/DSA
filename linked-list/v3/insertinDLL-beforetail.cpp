// LeetCode: Insert a Node Before Tail of a Doubly Linked List
// Time Complexity: O(n) -> For traversing to find the tail node
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

// Helper function to insert a new node before the head
Node* insertBeforeHead(Node* head, int val) {
    Node* newHead = new Node(val, head, nullptr);
    if (head != nullptr) {
        head->back = newHead;
    }
    return newHead;
}

// Function to insert a new node right before the tail node
Node* insertBeforeTail(Node* head, int val) {
    // Case 1: If the list has only a single node, insertion before tail means insertion before head
    if (head->next == nullptr) {
        return insertBeforeHead(head, val);
    }

    Node* tail = head;
    // Traverse until we reach the last node (tail)
    while (tail->next != nullptr) {
        tail = tail->next;
    }

    Node* prev = tail->back; // Locate the node right before the tail
    
    // Create the new node with its next pointer pointing to tail and back pointer pointing to prev
    Node* newNode = new Node(val, tail, prev);
    
    // Adjust the surrounding pointers to link the new node into the list
    prev->next = newNode;
    tail->back = newNode;

    return head;
}

int main() {
    vector<int> arr = {12, 5, 8, 7};
    Node* head = convertArr2DLL(arr);
    
    head = insertBeforeTail(head, 10); // Inserts 10 right before the tail node (7)
    print(head);                       // Outputs: 12 5 8 10 7
    
    return 0;
}