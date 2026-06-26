// LeetCode: Delete Tail of a Doubly Linked List
// Time Complexity: O(n) -> For traversing to the end of the list
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

// Function to delete the last node (tail) of a Doubly Linked List
Node* deleteTail(Node* head) {
    // Case 1: If the list is empty or contains only a single node
    if (head == nullptr || head->next == nullptr) {
        delete head; // Free memory if a single node exists
        return nullptr;
    }

    Node* tail = head;
    // Traverse until we reach the last node
    while (tail->next != nullptr) {
        tail = tail->next;
    }

    Node* prev = tail->back; // Locate the second-to-last node
    prev->next = nullptr;   // Detach the forward link to the old tail
    tail->back = nullptr;      // Detach the backward link from the old tail

    delete tail;               // Free up the memory of the old tail node
    return head;               // Return the original head pointer
}

int main() {
    vector<int> arr = {12, 5, 8, 7};
    Node* head = convertArr2DLL(arr);
    
    head = deleteTail(head); // Deletes the tail node containing 7
    print(head);            // Outputs: 12 5 8
    
    return 0;
}