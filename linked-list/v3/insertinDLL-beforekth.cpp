// LeetCode: Insert a Node Before K-th Element of a Doubly Linked List
// Time Complexity: O(n) -> In the worst case, we traverse up to the k-th node
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

// Function to insert a node right before the k-th element
Node* insertBeforeKthElement(Node* head, int k, int val) {
    // Case 1: If inserting before the 1st element, it's equivalent to inserting before the head
    if (k == 1) {
        return insertBeforeHead(head, val);
    }

    Node* temp = head;
    int cnt = 0;

    // Traverse the list to find the k-th element node
    while (temp != nullptr) {
        cnt++;
        if (cnt == k) break;
        temp = temp->next;
    }

    // Capture the node sitting right before the k-th element
    Node* prev = temp->back;

    // Create the new node with next pointing to temp and back pointing to prev
    Node* newNode = new Node(val, temp, prev);

    // Readjust pointers of neighboring nodes to anchor the new node in place
    prev->next = newNode;
    temp->back = newNode;

    return head;
}

int main() {
    vector<int> arr = {12, 5, 8, 7};
    Node* head = convertArr2DLL(arr);
    
    head = insertBeforeKthElement(head, 3, 10); // Inserts 10 right before the 3rd element (8)
    print(head);                                // Outputs: 12 5 10 8 7
    
    return 0;
}