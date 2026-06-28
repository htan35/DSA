// LeetCode: Infix to Prefix Conversion using Stack
// Time Complexity: O(N) -> Where N is the length of the string
// Space Complexity: O(N) -> For stack storage and modified result string
#include <iostream>
#include <stack>
#include <string>
#include <algorithm>

using namespace std;

// Helper function to establish operator precedence/priority
int priority(char op) {
    if (op == '^') return 3;
    if (op == '*' || op == '/') return 2;
    if (op == '+' || op == '-') return 1;
    return 0; // for parentheses and non-operators
}

// Helper function to check if character is an alphanumeric operand
bool isOperand(char ch) {
    return (ch >= 'a' && ch <= 'z') || 
           (ch >= 'A' && ch <= 'Z') || 
           (ch >= '0' && ch <= '9');
}

// Core conversion function following the sequence in your lecture notes
string infixToPrefix(string s) {
    // Step 1: Reverse the string
    reverse(s.begin(), s.end());

    // FIX: Explicitly handle parenthesis swapping after reversal
    for (int i = 0; i < s.length(); i++) {
        if (s[i] == '(') {
            s[i] = ')';
        } else if (s[i] == ')') {
            s[i] = '(';
        }
    }

    stack<char> st;
    string ans = "";
    int n = s.length();
    int i = 0;

    // Step 2: Main scanning loop
    while (i < n) {
        // Condition: if (operand)
        if (isOperand(s[i])) {
            ans += s[i];
        }
        // Condition: else if (opening) -> matches reversed fixed '('
        else if (s[i] == '(') {
            st.push(s[i]);
        }
        // Condition: else if (closing) -> matches reversed fixed ')'
        else if (s[i] == ')') {
            while (!st.empty() && st.top() != '(') {
                ans += st.top();
                st.pop();
            }
            if (!st.empty()) {
                st.pop(); // Remove the '('
            }
        }
        // Condition: else -> handles operators
        else {
            if (s[i] == '^') {
                // Special check for power operator logic
                while (!st.empty() && priority(s[i]) < priority(st.top())) {
                    ans += st.top();
                    st.pop();
                }
            } else {
                // For regular operators (+, -, *, /)
                while (!st.empty() && priority(s[i]) <= priority(st.top())) {
                    ans += st.top();
                    st.pop();
                }
            }
            st.push(s[i]);
        }
        i++;
    }

    // Step 3: Pop all remaining stack operators to the answer string
    while (!st.empty()) {
        ans += st.top();
        st.pop();
    }

    // Step 4: Reverse the final accumulated expression string to produce Prefix output
    reverse(ans.begin(), ans.end());
    return ans;
}

int main() {
    // Example test: (A-B/C)*(A/K-L)
    string infix = "(A-B/C)*(A/K-L)";
    string prefix = infixToPrefix(infix);

    cout << "Infix Expression:  " << infix << "\n";
    cout << "Prefix Expression: " << prefix << "\n"; 
    // Output matches: *-A/BC-/AKL

    return 0;
}