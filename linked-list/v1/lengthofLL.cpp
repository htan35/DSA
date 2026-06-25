// LeetCode: Convert Array to Singly Linked List
// Time Complexity: O(n)
// Space Complexity: O(n) -> For creating 'n' nodes of the linked list
#include <bits/stdc++.h>
#include<iostream>
using namespace std;

class Node {
public:
    int data;
    Node* next;

public:
    // Constructor with data and next pointer
    Node(int data1, Node* next1) {
        data = data1;
        next = next1;
    }

    // Constructor with data only (next pointer defaulted to nullptr)
    Node(int data1) {
        data = data1;
        next = nullptr;
    }
};

// Function to convert a vector into a Linked List
Node* convertArr2LL(vector<int> &arr) {
    // Create the head node with the first element
    Node* head = new Node(arr[0]);
    Node* mover = head;

    // Iterate from the second element to the end of the array
    for (int i = 1; i < arr.size(); i++) {
        Node* temp = new Node(arr[i]); // Create a new node
        mover->next = temp;            // Link current node to the new node
        mover = temp;                  // Move pointer to the new node
    }
    return head;
}

int lengthofLL(Node* head) {
    int length = 0;
    Node* temp = head;

    while (temp != nullptr) {
        length++;
        temp = temp->next;
    }

    return length;
}

int main() {
    vector<int> arr = {12, 5, 8, 7};
    Node* head = convertArr2LL(arr);
    cout<<lengthofLL(head)<<"\n";
    return 0;
}