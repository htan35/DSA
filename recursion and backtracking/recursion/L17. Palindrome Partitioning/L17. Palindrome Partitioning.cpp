/*
 * Problem: Palindrome Partitioning (LeetCode 131)
 * -----------------------------------------------
 * Approach: Backtracking via Substring Partitioning with Palindrome Verification
 * 
 * Approach Explanation:
 * 1. The goal is to partition the string `s` such that every substring in the partition is a palindrome.
 * 2. `func(index, s, path, res)`:
 *    - Base Case: When `index == s.size()`, we have successfully partitioned the entire string 
 *      into valid palindromic substrings -> push `path` into `res` and return.
 * 3. Loop-based Partitioning:
 *    - Consider every possible partition cut from `i = index` to `s.size() - 1`.
 *    - Check if substring `s[index...i]` is a palindrome using `isPalindrome(s, index, i)`:
 *        a. If it IS a palindrome:
 *           - Push `s.substr(index, i - index + 1)` into `path`.
 *           - Recurse for the remaining suffix starting at `i + 1`: `func(i + 1, s, path, res)`.
 *           - Backtrack: Remove the substring from `path` (`path.pop_back()`).
 *        b. If NOT a palindrome:
 *           - Skip cutting at index `i` and continue testing larger substrings.
 * 
 * Time Complexity:  O(2^N * N) - There are 2^(N-1) possible partition configurations, and checking 
 *                               / copying substrings takes up to O(N).
 * Space Complexity: O(N)       - Recursion stack depth and `path` storage space.
 */

#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Solution {
public:
    // Helper to check if s[start...end] is a palindrome
    bool isPalindrome(const string& s, int start, int end) {
        while (start <= end) {
            if (s[start++] != s[end--])
                return false;
        }
        return true;
    }

    void func(int index, string s, vector<string>& path, vector<vector<string>>& res) {
        // Base Case: Reached the end of the string
        if (index == s.size()) {
            res.push_back(path);
            return;
        }

        // Try partitioning at every index i >= index
        for (int i = index; i < s.size(); ++i) {
            if (isPalindrome(s, index, i)) {
                // Pick: substring is valid palindrome
                path.push_back(s.substr(index, i - index + 1));
                
                // Recurse for remaining part of the string
                func(i + 1, s, path, res);
                
                // Backtrack
                path.pop_back();
            }
        }
    }

    vector<vector<string>> partition(string s) {
        vector<vector<string>> res;
        vector<string> path;
        func(0, s, path, res);
        return res;
    }
};

// 🔹 Driver Code
int main() {
    /*
        Input: s = "aabb"
        Valid Palindrome Partitions:
        - ["a", "a", "b", "b"]
        - ["a", "a", "bb"]
        - ["aa", "b", "b"]
        - ["aa", "bb"]
    */

    string s = "aabb";
    Solution obj;
    vector<vector<string>> result = obj.partition(s);

    cout << "All Palindromic Partitions of \"" << s << "\":\n";
    for (const auto& part : result) {
        cout << "[ ";
        for (const string& str : part) {
            cout << "\"" << str << "\" ";
        }
        cout << "]\n";
    }

    return 0;
}
