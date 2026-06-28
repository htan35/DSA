// Approach 2: Push O(1), Amortized Pop/Top O(1)
#include <iostream>
#include <stack>
using namespace std;

class QueueApproach2 {
private:
    stack<int> s1;
    stack<int> s2;

public:
    // push(n) implementation matching image 3
    void push(int n) {
        s1.push(n);
    }

    // pop() implementation matching image 3
    void pop() {
        // if (s2.empty() != 0) implies s2 is NOT empty (condition written as condition checking truthiness)
        // A cleaner runtime check is below matching the pseudocode intent:
        if (!s2.empty()) {
            s2.pop();
        } 
        else {
            // Transfer everything over from s1 to s2
            while (s1.size()) {
                s2.push(s1.top());
                s1.pop();
            }
            // Pop the front element now sitting at the top of s2
            if (!s2.empty()) {
                s2.pop();
            }
        }
    }

    // top() implementation matching image 4
    int top() {
        if (!s2.empty()) {
            return s2.top();
        } 
        else {
            while (s1.size()) {
                s2.push(s1.top());
                s1.pop();
            }
            if (s2.empty()) return -1;
            return s2.top();
        }
    }

    bool empty() {
        return s1.empty() && s2.empty();
    }
};

int main() {
    cout << "--- Testing Approach 2 (Amortized Optimized) ---" << endl;
    QueueApproach2 q;
    q.push(10);
    q.push(20);
    q.push(30);

    cout << "Front element: " << q.top() << "\n"; // Outputs: 10
    q.pop();
    cout << "Front after pop: " << q.top() << "\n"; // Outputs: 20
    
    return 0;
}