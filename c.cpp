// #include<iostream>
// #include<set>
// #include<vector>
// using namespace std;
// int main(){
//     // set<int> s;
//     // s.insert(5);
//     // s.insert(3);    
//     // s.insert(8);
//     // s.insert(1);
//     // for(int i=0;i<s.size();i++){
//     //     cout << s[i] << " ";
//     // }

//     cout<<3/2;
//     return 0;
//}


#include <iostream>
#include <vector>

using namespace std;

int main() {
    // 1. Create our matrix from the visual above
    vector<vector<int>> matrix = {
        {5, 8, 2},
        {1, 9, 4},
        {7, 6, 3}
    };
    cout<<matrix.size()<<"\n";

    // 2. The Outer Loop: Goes down row by row (Top to Bottom)
    for (int row = 0; row < matrix.size(); row++) {
        
        // 3. The Inner Loop: Goes across the current row (Left to Right)
        for (int col = 0; col < matrix[row].size(); col++) {
            
            // 4. Access the specific element
            cout << "Value at " << row << "," << col << " is: " << matrix[row][col] << "\n";
            
        }
    }
    
    return 0;
}