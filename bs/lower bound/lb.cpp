 #include <vector>

using std::vector;

class Solution {
  public:
    
    int lb(vector<int>& arr, int low, int high, int target , int& ans){
        if(low>high){
            return ans;
        }
        int mid = low + (high - low)/2;
        if(arr[mid]>=target){
            ans = mid;
            return lb(arr,low,mid-1,target, ans);
            
        }
        else{
            return lb(arr,mid+1,high,target,ans);
        }
    }
  
    int lowerBound(vector<int>& arr, int target) {
        // code here
        int ans = arr.size();
        return lb(arr,0,arr.size(),target, ans);
        
    }
};