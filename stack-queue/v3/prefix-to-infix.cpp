// LeetCode / GeeksforGeeks: Prefix to Infix Conversion using Stack
// Time Complexity: O(N) -> Where N is the length of the string
// Space Complexity: O(N) -> Stack allocation for sub-expression strings
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
string prefixToInfix(string s) {
    stack<string> st; // Stack tracking intermediate string expressions
    int n = s.length();
    
    // Starting pointer at the end of the string for right-to-left scan
    int i = n - 1; // i = n - 1;

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
            // Retrieve first popped element from top
            string t1 = st.top();
            st.pop();
            
            // Retrieve second popped element from top
            string t2 = st.top();
            st.pop();
            
            // Construct infix string fragment context: con = '(' + t1 + s[i] + t2 + ')'
            string con = "(" + t1 + s[i] + t2 + ")";
            
            // Push resulting string evaluation back onto the main stack stream
            st.push(con);
        }
        i--; // Decrement index pointer to move right-to-left
    }

    // The remaining element on top of the stack is the final full expression
    return st.top();
}

int main() {
    // Test Case: *-A/BC-/AKL (Prefix notation)
    string prefix = "*-A/BC-/AKL";
    string infix = prefixToInfix(prefix);

    cout << "Prefix Expression: " << prefix << "\n";
    cout << "Infix Expression:  " << infix << "\n";
    // Output structural context matches: ((A-(B/C))*((A/K)-L))

    return 0;
}