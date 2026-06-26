// LeetCode: Insert an Element at K-th Position in a Linked List
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

// Function to insert element 'el' at position 'k'
Node* insertPosition(Node* head, int el, int k) {
    // Case 1: If the list is empty
    if (head == nullptr) {
        if (k == 1) {
            return new Node(el);
        } else {
            return head;
        }
    }

    // Case 2: Insertion at the head (k == 1)
    if (k == 1) {
        return new Node(el, head);
    }

    int cnt = 0;
    Node* temp = head;

    // Traverse to locate the (k-1)th node
    while (temp != nullptr) {
        cnt++;
        if (cnt == (k - 1)) {
            Node* x = new Node(el, temp->next); // Create new node linking to current node's next
            temp->next = x;                    // Link current node to the new node
            break;
        }
        temp = temp->next;
    }

    return head;
}

int main() {
    vector<int> arr = {12, 5, 8, 7};
    Node* head = convertArr2LL(arr);
    
    head = insertPosition(head, 100, 3); // Inserts 100 at 3rd position
    print(head);                        // Outputs: 12 5 100 8 7
    
    return 0;
}