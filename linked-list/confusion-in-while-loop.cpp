#include <iostream>
#include <vector>

using namespace std;

// Definition for singly-linked list node.
struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(nullptr) {}
};

// Function 1: Uses while(temp != NULL)
void traverseTillNull(ListNode* head) {
    cout << "\n--- Running: while(temp != NULL) ---" << endl;
    ListNode* temp = head;
    
    cout << "Inside Loop (Elements visited): ";
    while (temp != NULL) {
        cout << temp->val << " ";
        temp = temp->next;
    }
    cout << endl;
    
    // Checking where temp ended up
    if (temp == nullptr) {
        cout << "After Loop: temp is now NULL (stepped off the list)" << endl;
    }
}

// Function 2: Uses while(temp->next != NULL)
void traverseTillTail(ListNode* head) {
    cout << "\n--- Running: while(temp->next != NULL) ---" << endl;
    if (head == nullptr) return; // Safety check
    
    ListNode* temp = head;
    
    cout << "Inside Loop (Elements visited): ";
    while (temp->next != NULL) {
        cout << temp->val << " ";
        temp = temp->next;
    }
    cout << endl;
    
    // Checking where temp ended up
    if (temp != nullptr) {
        cout << "After Loop: temp stopped ON the last node. Value = " << temp->val << endl;
    }
}

// Helper Function: Convert a C++ vector into a Linked List
ListNode* convertArrayToLinkedList(const vector<int>& arr) {
    if (arr.empty()) return nullptr;
    ListNode* head = new ListNode(arr[0]);
    ListNode* mover = head;
    for (size_t i = 1; i < arr.size(); i++) {
        mover->next = new ListNode(arr[i]);
        mover = mover->next;
    }
    return head;
}

int main() {
    // 1. Take a sample array/vector
    vector<int> arr = {10, 20, 30, 40, 50};
    
    // 2. Convert it to a Linked List: 10 -> 20 -> 30 -> 40 -> 50 -> NULL
    ListNode* head = convertArrayToLinkedList(arr);
    
    cout << "Original List: 10 -> 20 -> 30 -> 40 -> 50 -> NULL" << endl;
    
    // 3. Call both functions to observe outputs
    traverseTillNull(head);
    traverseTillTail(head);
    
    return 0;
}