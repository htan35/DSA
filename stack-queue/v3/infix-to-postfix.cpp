#include <iostream>
#include <stack>
#include <string>

using namespace std;

// Operator ki priority/precedence check karne ke liye helper function
int priority(char ch) {
    if (ch == '^') return 3;
    if (ch == '*' || ch == '/') return 2;
    if (ch == '+' || ch == '-') return 1;
    return -1; // Brackets ke liye default lowest priority
}

string infixToPostfix(string s) {
    int i = 0;
    int n = s.length();
    stack<char> st;
    string ans = "";

    while (i < n) {
        // 1. Operand condition (A-Z, a-z, 0-9) -> Direct Output
        if ((s[i] >= 'A' && s[i] <= 'Z') || 
            (s[i] >= 'a' && s[i] <= 'z') || 
            (s[i] >= '0' && s[i] <= '9')) {
            ans = ans + s[i];
        }
        // 2. Opening Bracket '(' -> Direct Stack Push
        else if (s[i] == '(') {
            st.push(s[i]);
        }
        // 3. Closing Bracket ')' -> Pop till '(' is encountered
        else if (s[i] == ')') {
            while (!st.empty() && st.top() != '(') {
                ans += st.top();
                st.pop(); // Parentheses ke saath correction
            }
            if (!st.empty()) {
                st.pop(); // Opening bracket '(' ko bhi clean up karo
            }
        }
        // 4. Operators -> Handle based on relative priority rules
        else {
            // Jab tak incoming operator ki precedence top se kam ya barabar (<=) hai, tab tak pop karo
            while (!st.empty() && priority(s[i]) <= priority(st.top())) {
                ans += st.top();
                st.pop();
            }
            st.push(s[i]); // Finally push the current operator
        }
        i++;
    }

    // 5. Cleanup phase: Stack mein bache hue operators ko output mein append karo
    while (!st.empty()) {
        ans = ans + st.top();
        st.pop(); // Added correct function call syntax '();'
    }

    return ans;
}

int main() {
    string infix = "A+B*(C^D-E)";
    cout << "Infix Expression:  " << infix << endl;
    cout << "Postfix Expression: " << infixToPostfix(infix) << endl;
    return 0;
}