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
Node* removeK(Node* head, int k) {
    if (head == nullptr) return head; // Base case: list is empty

    // Case 1: If the head node needs to be removed (k == 1)
    if (k == 1) {
        Node* temp = head;
        head = head->next;
        delete temp; // Free allocated memory
        return head;
    }

    int cnt = 0;
    Node* temp = head;
    Node* prev = nullptr;

    // Traverse the list to find the k-th node
    while (temp != nullptr) {
        cnt++;
        if (cnt == k) {
            prev->next = prev->next->next; // Bypass the k-th node
            delete temp;                    // Free the target node's memory
            break;
        }
        prev = temp;       // Keep track of the previous node
        temp = temp->next; // Move forward
    }

    return head;
}

int main() {
    vector<int> arr = {12, 5, 8, 7};
    Node* head = convertArr2LL(arr);
    
    head = removeK(head, 3); // Removes the 3rd node (element 8)
    print(head);             // Outputs: 12 5 7
    
    return 0;
}