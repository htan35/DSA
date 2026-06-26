// LeetCode: Insert a Node Before a Given Value in a Linked List
// Time Complexity: O(n)
// Space Complexity: O(1)
#include <iostream>
#include <bits/stdc++.h>
using namespace std;

class Node {
public:
    int data;
    Node* next;
    
    Node(int data1) {
        data = data1;
        next = nullptr;
    }
    
    Node(int data1, Node* next1) {
        data = data1;
        next = next1;
    }
};

// Helper function to convert vector to linked list
Node* convertArr2LL(vector<int> &arr) {
    if (arr.empty()) return nullptr;
    Node* head = new Node(arr[0]);
    Node* mover = head;
    for (int i = 1; i < arr.size(); i++) {
        Node* temp = new Node(arr[i]);
        mover->next = temp;
        mover = temp;
    }
    return head;
}

// Helper function to print the linked list
void print(Node* head) {
    while (head != nullptr) {
        cout << head->data << " ";
        head = head->next;
    }
    cout << "\n";
}

// Function to insert element 'el' right before the node containing value 'val'
Node* insertBeforeValue(Node* head, int el, int val) {
    // Case 1: List is completely empty
    if (head == nullptr) {
        return nullptr;
    }

    // Case 2: The target value is found at the head node itself
    if (head->data == val) {
        return new Node(el, head);
    }

    Node* temp = head;
    
    // Traverse up to the second-to-last node
    while (temp->next != nullptr) {
        // Look ahead to check if the next node contains the target value
        if (temp->next->data == val) {
            Node* x = new Node(el, temp->next); // Point new node to the target node
            temp->next = x;                    // Link current node to the new node
            break;
        }
        temp = temp->next; // Advance forward
    }

    return head;
}

int main() {
    vector<int> arr = {12, 5, 8, 7};
    Node* head = convertArr2LL(arr);
    
    head = insertBeforeValue(head, 100, 5); // Inserts 100 right before 5
    print(head);                           // Outputs: 12 100 5 8 7
    
    return 0;
}