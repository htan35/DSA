#include <bits/stdc++.h>
using namespace std;

int main() {
    vector<int> arr = {2, 5, 1, 10, 10};
    int K = 14;

    int n = arr.size();
    int l = 0, sum = 0;

    vector<int> temp;   // 1D vector

    for (int r = 0; r < n; r++) {
        sum += arr[r];

        while (sum > K) {
            sum -= arr[l];
            l++;
        }

        // Print all valid subarrays ending at r
        for (int start = l; start <= r; start++) {

            temp.clear();   // Reuse the same vector

            for (int i = start; i <= r; i++) {
                temp.push_back(arr[i]);
            }

            for (int x : temp) {
                cout << x << " ";
            }
            cout << endl;
        }
    }

    return 0;
}