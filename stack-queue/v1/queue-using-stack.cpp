// LeetCode 232: Implement Queue using Stacks (Costly Push Approach)
// Time Complexity: Push: O(2N) -> O(N), Pop/Top: O(1)
// Space Complexity: O(N) auxiliary stack space
#include <iostream>
#include <stack>
using namespace std;

class Q {
private:
    stack<int> s1; // Primary storage stack
    stack<int> s2; // Auxiliary helper stack

public:
    // Function to add an element x to the queue
    void push(int x) {
        // Step 1: Shift all elements from s1 over to s2
        while (s1.size()) {
            s2.push(s1.top());
            s1.pop();
        }

        // Step 2: Push the new element onto the empty s1
        s1.push(x);

        // Step 3: Shift all elements back from s2 onto s1
        while (s2.size()) {
            s1.push(s2.top());
            s2.pop();
        }
    }

    // Function to remove the element from the front of the queue
    void pop() {
        if (s1.empty()) {
            cout << "Queue Underflow\n";
            return;
        }
        s1.pop();
    }

    // Function to look at the front element of the queue
    int top() {
        if (s1.empty()) {
            cout << "Queue is Empty\n";
            return -1;
        }
        return s1.top();
    }

    // Helper function to check if the queue is empty
    bool empty() {
        return s1.empty();
    }

    // Helper function to get current size of the queue
    int size() {
        return s1.size();
    }
};

int main() {
    Q queue;

    queue.push(10);
    queue.push(20);
    queue.push(30);

    cout << "Front element: " << queue.top() << "\n";  // Outputs: 10 (FIFO order)
    cout << "Queue size: " << queue.size() << "\n";    // Outputs: 3

    queue.pop();
    cout << "Front after pop: " << queue.top() << "\n"; // Outputs: 20

    return 0;
}