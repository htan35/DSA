// LeetCode: Remove the K-th Node from a Linked List
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

// Function to remove the k-th node from the list
Node* removeElement(Node* head, int element) {
    if(head == NULL) return NULL;
    if (head->data == element) {
        Node* temp = head;
        head = head->next;
        delete temp;
        return head;
    }

    Node* temp = head;
    Node* prev = NULL;

    // Traverse the list to find the node with the specified element
    while (temp != nullptr) {
        if (temp->data == element) {
            prev->next = prev->next->next;
            delete temp;
            return head;
        }
        prev = temp;
        temp = temp->next;
    }

    return head;
}


int main() {
    vector<int> arr = {12, 5, 8, 7};
    Node* head = convertArr2LL(arr);
    
    head = removeElement(head, 8); // Removes the node with data 8  
    print(head);             // Outputs: 12 5 7
    
    return 0;
}