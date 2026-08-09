#include <bits/stdc++.h>
#include <iostream>
using namespace std;

class Solution {
public:
    int nthRoot(int n, int m) {

        double ans = pow(m, (double)1.0 / (double)n);
        int x = round(ans);

        if (pow(x, n) == m) {
            return x;
        }

        return -1;
    }
};

int main() {
    int t;
    cin >> t;

    while (t--) {
        int n, m;
        cin >> n >> m;

        Solution obj;
        cout << obj.nthRoot(n, m) << endl;
    }

    return 0;
}