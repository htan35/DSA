// LeetCode 225: Implement Stack using Queues (Single Queue Optimization)
// Time Complexity: Push: O(N), Pop/Top: O(1)
// Space Complexity: O(N) auxiliary space used by the queue
#include <iostream>
#include <queue>
using namespace std;

class MyStack {
private:
    queue<int> q; // The single queue used to simulate stack behavior

public:
    // Push element x onto stack.
    void push(int x) {
        // Get the current size before adding the element
        int current_size = q.size();
        
        // Step 1: Push the new element to the back of the queue
        q.push(x);
        
        // Step 2: Rotate the queue to bring the new element to the front
        for (int i = 0; i < current_size; i++) {
            q.push(q.front()); // Take front element and put it at the back
            q.pop();           // Remove that front element
        }
    }

    // Removes the element on top of the stack (Front of the queue)
    void pop() {
        if (q.empty()) {
            cout << "Stack Underflow\n";
            return;
        }
        q.pop();
    }

    // Get the top element of the stack (Front of the queue)
    int top() {
        if (q.empty()) {
            cout << "Stack is empty\n";
            return -1;
        }
        return q.front();
    }

    // Returns whether the stack is empty
    bool empty() {
        return q.empty();
    }

    // Returns current size of the stack
    int size() {
        return q.size();
    }
};

int main() {
    MyStack st;
    
    st.push(10);
    st.push(20);
    st.push(30);

    cout << "Top element: " << st.top() << "\n";  // Outputs: 30 (LIFO behavior)
    cout << "Stack size: " << st.size() << "\n";   // Outputs: 3

    st.pop();
    cout << "Top after pop: " << st.top() << "\n"; // Outputs: 20

    return 0;
}