class Solution {
public:
    void solve(int idx, string& s, vector<string>& ans) {
        if (idx == s.size()) {
            ans.push_back(s);
            return;
        }

        for (int i = idx; i < s.size(); i++) {
            swap(s[idx], s[i]);

            solve(idx + 1, s, ans);

            swap(s[idx], s[i]);
        }
    }

    vector<string> permutations(string s) {
        vector<string> ans;
        solve(0, s, ans);
        return ans;
    }
};