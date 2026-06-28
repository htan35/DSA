// LeetCode / GeeksforGeeks: Postfix to Prefix Conversion using Stack
// Time Complexity: O(N) -> Where N is the length of the expression string
// Space Complexity: O(N) -> Auxiliary stack space allocation
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

// Core conversion function following your handwritten algorithm sequence
string postfixToPrefix(string s) {
    stack<string> st; // Stack initialization 'st' to store strings
    int n = s.length();
    int i = 0; // i = 0 initialization

    // Loop running while i < n
    while (i < n) {
        // if (operand)
        if (isOperand(s[i])) {
            // Convert character token to a string token before pushing
            string operandStr(1, s[i]);
            st.push(operandStr); // st.push(s[i])
        } 
        // else (operator)
        else {
            // Pop the top element first
            string t1 = st.top();
            st.pop(); // t1 = st.top  st.pop
            
            // Pop the next top element
            string t2 = st.top();
            st.pop(); // t2 = st.top  st.pop
            
            // Concatenate in prefix layout: operator + t2 + t1
            string con = s[i] + t2 + t1; // st.push(s[i] + t2 + t1)
            
            // Push resulting string back onto stack
            st.push(con);
        }
        i++; // Index counter advancement
    }

    // The remaining item sitting at the top of the stack is the final result
    return st.top(); // return st.top
}

int main() {
    // Test Case: AB+C*D- (Postfix notation)
    string postfix = "AB+C*D-";
    string prefix = postfixToPrefix(postfix);

    cout << "Postfix Expression: " << postfix << "\n";
    cout << "Prefix Expression:  " << prefix << "\n"; 
    // Output structural context matches: -*+ABCD

    return 0;
}