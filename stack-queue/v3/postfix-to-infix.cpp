// LeetCode / GeeksforGeeks: Postfix to Infix Conversion using Stack
// Time Complexity: O(N) -> Where N is the length of the string
// Space Complexity: O(N) -> Stack space storing intermediate expression strings
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

// Core conversion function matching your class algorithm sequence
string postfixToInfix(string s) {
    stack<string> st; // Note: 'st -> string' as highlighted in notes
    int n = s.length();
    int i = 0; // i = 0 initial state

    while (i < n) {
        // if (operand)
        if (isOperand(s[i])) {
            // Convert character token to an intermediate string before pushing
            string operandStr(1, s[i]); 
            st.push(operandStr); // st.push(s[i])
        } 
        // else (operator)
        else {
            // Retrieve first top element
            string t1 = st.top();
            st.pop();
            
            // Retrieve second top element
            string t2 = st.top();
            st.pop();
            
            // Construct compound structural string context: con = '(' + t2 + operator + t1 + ')'
            string con = "(" + t2 + s[i] + t1 + ")";
            
            // Push resulting string structural fragment back onto primary evaluation stream
            st.push(con);
        }
        i++; // Linear scale index advance
    }

    // Return the final complete evaluation state left on top of the stack
    return st.top();
}

int main() {
    // Test Case: AB+C*D- (Postfix notation)
    string postfix = "AB+C*D-";
    string infix = postfixToInfix(postfix);

    cout << "Postfix Expression: " << postfix << "\n";
    cout << "Infix Expression:   " << infix << "\n"; 
    // Output structural context matches: ((A+B)*C)-D

    return 0;
}