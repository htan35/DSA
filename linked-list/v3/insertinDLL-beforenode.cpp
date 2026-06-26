// LeetCode: Insert a Node Before a Given Node in a Doubly Linked List
// Time Complexity: O(1) -> Direct insertion using the pointer to the node
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

// Function to insert a new node with value 'val' right before a given node pointer
void insertBeforeNode(Node* node, int val) {
    // Locate the node sitting directly behind the target node
    Node* prev = node->back;

    // Create the new node with next pointing to 'node' and back pointing to 'prev'
    Node* newNode = new Node(val, node, prev);

    // Readjust the neighboring structural pointers to secure the new node in place
    prev->next = newNode;
    node->back = newNode;
}

int main() {
    vector<int> arr = {12, 5, 8, 7};
    Node* head = convertArr2DLL(arr);
    
    // head->next points to the node containing 5
    insertBeforeNode(head->next, 100); // Inserts 100 right before 5
    
    print(head); // Outputs: 12 100 5 8 7
    return 0;
}