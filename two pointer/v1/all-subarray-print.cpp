#include <bits/stdc++.h>
using namespace std;

int main() {
    vector<int> arr = {2, 5, 1, 7, 10};
    int n = arr.size();

    // Loop for starting point
    for (int i = 0; i < n; i++) {
        vector<int> current_subarray;
        
        // Loop for ending point
        for (int j = i; j < n; j++) {
            // Push the current element into the list
            current_subarray.push_back(arr[j]);
            
            // Print the current state of the vector
            for (int val : current_subarray) {
                cout << val << " ";
            }
            cout << "\n";
        }
    }
    return 0;
}