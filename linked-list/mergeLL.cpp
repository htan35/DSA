// LeetCode 21: Merge Two Sorted Lists (In-Place Iterative Approach)
// Time Complexity: O(l1 + l2)
// Space Complexity: O(1) -> Modifies pointers without extra nodes

//Core Idea: Always make l1 the smaller list

//Starting Pivot Set Karna: Sabse pehle hum check karte hain dono me se chota kaun hai.
//Hum hamesha l1 pointer ko chote element par rakhte hain aur l2 ko bade element par. Agar l1 bada hua, toh hum unhe swap(l1, l2) kar dete hain. 
//res pointer ko is initial l1 par set kar dete hain kyuki yahi hamara final head banega.

//Chote values ki chain trace karna: Ek while loop chalta hai jo l1 ko tab tak aage badhata rehta hai jab tak l1->val <= l2->val hai. 
//Hum ek tmp pointer rakhte hain jo l1 ki is continuous choti chain ka aakhri valid node track karta hai.

//Bridge banana aur roles swap karna: Jaise hi l1 par koi aisi value aati hai jo l2 se badi ho jaye, loop ruk jata hai. 
//Hum tmp->next = l2 karke choti chain ke aakhri node ko l2 se link kar dete hain.

//he Swap: Ab kyunki l2 ke paas choti values hain aur l1 ke paas badi values hain, hum swap(l1, l2) kar dete hain takia hamara core rule maintain rahe: l1 hamesha chota rehna chahiye.

#include <iostream>
#include <bits/stdc++.h>
using namespace std;

struct ListNode {
    int val;
    ListNode* next;
    ListNode(int x) : val(x), next(NULL) {}
};

class Solution {
public:
    ListNode* mergeTwoLists(ListNode* l1, ListNode* l2) {
        // Base cases: if either list is empty, return the other list
        if (l1 == NULL) return l2;
        if (l2 == NULL) return l1;

        // Ensure l1 always points to the list with the smaller initial value
        if (l1->val > l2->val) {
            std::swap(l1, l2);
        }

        // 'res' will store the ultimate head node of the merged list
        ListNode* res = l1;

        while (l1 != NULL && l2 != NULL) {
            ListNode* tmp = NULL;

            // Advance l1 as long as its values are smaller than or equal to l2's current value
            while (l1 != NULL && l1->val <= l2->val) {
                tmp = l1; // Track the last valid node of the l1 chain
                l1 = l1->next;
            }

            // Link the last valid node of the smaller chain to the head of the other list
            tmp->next = l2;
            
            // Swap the list pointers to continue tracking the smaller values in the next loop iteration
            std::swap(l1, l2);
        }

        return res;
    }
};

// Helper function to create a linked list from a vector
ListNode* createList(const vector<int>& values) {
    if (values.empty()) return NULL;
    ListNode* head = new ListNode(values[0]);
    ListNode* current = head;
    for (size_t i = 1; i < values.size(); ++i) {
        current->next = new ListNode(values[i]);
        current = current->next;
    }
    return head;
}

// Helper function to print a linked list
void printList(ListNode* head) {
    while (head != NULL) {
        cout << head->val << " ";
        head = head->next;
    }
    cout << "\n";
}

int main() {
    ListNode* l1 = createList({1, 2, 4});
    ListNode* l2 = createList({1, 3, 5});

    Solution sol;
    ListNode* mergedHead = sol.mergeTwoLists(l1, l2);

    printList(mergedHead); // Outputs: 1 1 2 3 4 5

    return 0;
}