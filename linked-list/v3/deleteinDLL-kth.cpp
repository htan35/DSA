// LeetCode: Delete K-th Node of a Doubly Linked List
// Time Complexity: O(n)
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

// Helper function to delete the head node
Node* deleteHead(Node* head) {
    if (head == nullptr || head->next == nullptr) {
        delete head;
        return nullptr;
    }
    Node* prev = head;
    head = head->next;
    head->back = nullptr;
    prev->next = nullptr;
    delete prev;
    return head;
}

// Helper function to delete the tail node
Node* deleteTail(Node* head) {
    if (head == nullptr || head->next == nullptr) {
        delete head;
        return nullptr;
    }
    Node* tail = head;
    while (tail->next != nullptr) {
        tail = tail->next;
    }
    Node* newTail = tail->back;
    newTail->next = nullptr;
    tail->back = nullptr;
    delete tail;
    return head;
}

// Function to delete the K-th node from a Doubly Linked List
Node* deleteKthNode(Node* head, int k) {
    if (head == nullptr) return nullptr;

    int cnt = 0;
    Node* temp = head;

    // Traverse to locate the k-th node
    while (temp != nullptr) {
        cnt++;
        if (cnt == k) break;
        temp = temp->next;
    }

    // If k is greater than the number of nodes
    if (temp == nullptr) return head;

    Node* prev = temp->back;
    Node* front = temp->next;

    // Case 1: The list contains only one node
    if (prev == nullptr && front == nullptr) {
        delete temp;
        return nullptr;
    }
    // Case 2: Deleting the head node (k == 1)
    else if (prev == nullptr) {
        return deleteHead(head);
    }
    // Case 3: Deleting the tail node (k == last position)
    else if (front == nullptr) {
        return deleteTail(head);
    }
    // Case 4: Deleting a middle node
    else {
        prev->next = front;
        front->back = prev;
        
        temp->next = nullptr;
        temp->back = nullptr;
        delete temp;
    }

    return head;
}

int main() {
    vector<int> arr = {2, 3, 4, 1};
    Node* head = convertArr2DLL(arr);
    
    head = deleteKthNode(head, 2); // Deletes the 2nd node (element 3)
    print(head);                  // Outputs: 2 4 1
    
    return 0;
}