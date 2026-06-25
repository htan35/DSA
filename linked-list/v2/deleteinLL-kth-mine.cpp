// LeetCode: Delete Head of a Linked List
// Time Complexity: O(n) for printing, O(1) for deletion
// Space Complexity: O(1)
#include <bits/stdc++.h>
#include<iostream>

using namespace std;

class Node {
public:
    int data;
    Node* next;
    Node(int data1) {
        data = data1;
        next = nullptr;
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

// Function to print the linked list
void print(Node* head) {
    while (head != nullptr) {
        cout << head->data << " ";
        head = head->next;
    }
    cout << "\n";
}

// Function to remove the tail node
Node* removeskthElement(Node* head, int k) {
    if (head == NULL) return NULL; // Base case: list is empty

    if(k==1){
        Node* temp = head;       // Point temp to old head
        head = head->next;       // Shift head to next node
        delete temp;             // Free the memory of old head
        return head;
    }

    Node* temp = head;
    Node* temp2 = temp;     // Point temp2 to old head
    while(k-1>1){
        temp=temp->next;
        temp2 = temp->next->next; 
        k--;
    }
    delete temp->next;
    temp->next=temp2;
    return head;
}

int main() {
    vector<int> arr = {12, 5, 8,1, 6 ,9 ,5, 7};
    Node* head = convertArr2LL(arr);
    
    head = removeskthElement(head,5); // Deletes node with data 6
    print(head);              // Outputs: 12 5 8 1 9 5 7
    
    return 0;
}