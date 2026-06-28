// LeetCode / GeeksforGeeks: Prefix to Postfix Conversion using Stack
// Time Complexity: O(N) -> Single pass scan over the expression string
// Space Complexity: O(N) -> For storing intermediate concatenated strings inside the stack
#include <iostream>
#include <stack>
#include <string>

using namespace std;

// Helper function to check if the character is an alphanumeric operand
bool isOperand(char ch) {
    return (ch >= 'a' && ch <= 'z') || 
           (ch >= 'A' && ch <= 'Z') || 
           (ch >= '0' && ch <= '9');
}

// Core conversion function following your handwritten algorithm layout
string prefixToPostfix(string s) {
    stack<string> st; // Stack 'st' initialized to store structural text strings
    int n = s.length();
    int i = n - 1; // Start from right-to-left scan

    // Loop running while i >= 0
    while (i >= 0) {
        // if (operand)
        if (isOperand(s[i])) {
            // Convert character token to a string token before pushing
            string operandStr(1, s[i]);
            st.push(operandStr); // st.push(s[i])
        } 
        // else (operator)
        else {
            // Retrieve first popped element
            string t1 = st.top();
            st.pop(); // t1 = st.top  st.pop
            
            // Retrieve second popped element
            string t2 = st.top();
            st.pop(); // t2 = st.top  st.pop
            
            // Concatenate in postfix format layout: t1 + t2 + operator
            string con = t1 + t2 + s[i]; // st.push(t1 + t2 + s[i])
            
            // Push resulting string evaluation back onto working stack
            st.push(con);
        }
        i--; // Decrement index counter backwards to scan right-to-left
    }

    // The remaining expression string at the top of the stack is the final result
    return st.top(); // return st.top
}

int main() {
    // Test Case: /-AB*CD (Prefix notation)
    string prefix = "/-AB*CD";
    string postfix = prefixToPostfix(prefix);

    cout << "Prefix Expression:  " << prefix << "\n";
    cout << "Postfix Expression: " << postfix << "\n"; 
    // Output structural context matches: AB-CD*/

    return 0;
}