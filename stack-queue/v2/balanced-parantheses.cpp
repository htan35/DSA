// LeetCode 20: Valid Parentheses
// Time Complexity: O(n) -> Where n is the length of the string
// Space Complexity: O(n) -> In the worst-case scenario (e.g., all opening brackets)
#include <iostream>
#include <stack>
#include <string>

using namespace std;

bool isValid(string s) {
    stack<char> st; // Stack declaration matching 'stack s;' from notes
    int n = s.length();

    // Loop running from i = 0 to n - 1
    for (int i = 0; i < n; i++) {
        // Condition checking for all types of opening brackets
        if (s[i] == '(' || s[i] == '[' || s[i] == '{') {
            st.push(s[i]);
        } 
        else {
            // If stack is empty when facing a closing bracket, it's invalid
            if (st.empty()) {
                return false;
            }

            // Extracting the top element and popping it from the stack
            char ch = st.top();
            st.pop();

            // Verifying valid matching pairs
            if ((s[i] == ')' && ch == '(') || 
                (s[i] == ']' && ch == '[') || 
                (s[i] == '}' && ch == '{')) {
                // Matching pair found, continue checking the rest of the string
                continue;
            } 
            else {
                // Mismatched closing bracket type encountered
                return false;
            }
        }
    }

    // Returns true if stack is empty, false if opening brackets remain unclosed
    return st.empty();
}

int main() {
    // Test cases
    string s1 = "[()]{}";
    string s2 = "[(])";

    cout << "Is \"" << s1 << "\" valid? " << (isValid(s1) ? "True" : "False") << "\n"; // Outputs: True
    cout << "Is \"" << s2 << "\" valid? " << (isValid(s2) ? "True" : "False") << "\n"; // Outputs: False

    return 0;
}