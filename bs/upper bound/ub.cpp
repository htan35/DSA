
 #include <vector>

using std::vector;

class Solution {
  public:
    int upperBound(vector<int>& arr, int target) {
        // code here
        int low = 0;
        int high = arr.size(); // n is also a possible answer
        while(low < high){
            int mid = low + (high - low)/2;
            if(arr[mid]>target){
                high = mid; // keep mid (possible answer)
            }
            else{
                low = mid+1;
            }
            
        }
        return low;
    }
};