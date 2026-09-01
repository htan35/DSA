#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    void subset(int start, vector<int>& nums, vector<int>& ds, vector<vector<int>>& ans) {
        
        ans.push_back(ds);

        int n = nums.size();

        for(int i = start; i < n; i++) {
            
            ds.push_back(nums[i]);

            subset(i + 1, nums, ds, ans);

            ds.pop_back();
        }
    }

    vector<vector<int>> subsets(vector<int>& nums) {
        
        vector<vector<int>> ans;
        vector<int> ds;

        subset(0, nums, ds, ans);

        return ans;
    }
};

int main() {
    
    vector<int> nums = {1, 2, 3};

    Solution obj;

    vector<vector<int>> ans = obj.subsets(nums);

    for(auto v : ans) {
        cout << "[ ";
        for(auto x : v) {
            cout << x << " ";
        }
        cout << "]" << endl;
    }

    return 0;
}
