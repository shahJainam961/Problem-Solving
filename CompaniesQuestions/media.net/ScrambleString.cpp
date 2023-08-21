#include<bits/stdc++.h>
using namespace std;

class Solution {
    int cnt = 0;
    bool f(int i1, int j1, int i2, int j2, string &s1, string &s2, vector<vector<vector<vector<int>>>> &dp){
        if(dp[i1][j1][i2][j2] != -1) return dp[i1][j1][i2][j2];
        
        if(i1==j1) return dp[i1][j1][i2][j2] = s1[i1]==s2[i2];

        bool ans = false;
        for(int k=i1; k<j1; k++){
            ans = ans or ( f(i1, k, i2, i2+k-i1, s1, s2, dp) and f(k+1, j1, j2-(j1-k-1), j2, s1, s2, dp) )
                    or ( f(i1, k, j2-(k-i1), j2, s1, s2, dp) and f(k+1, j1, i2, i2+j1-k-1, s1, s2, dp) );
        }
        cnt++;
        return dp[i1][j1][i2][j2] = ans;
    }

public:
    bool isScramble(string s1, string s2) {
        int n = s1.size();
        vector<vector<vector<vector<int>>>> dp(n+1, vector<vector<vector<int>>>(n+1, vector<vector<int>>(n+1, vector<int>(n+1, -1))));
        bool ans = f(0, n-1, 0, n-1, s1, s2, dp);
        cout<<cnt;
        return ans;
    }
};

//---------------------------------------
class Solution {
public:
    bool isScramble(string s1, string s2) {
        int n = s1.size();
        vector dp(n + 1, vector(n, vector<int>(n)));
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                dp[1][i][j] = s1[i] == s2[j];
            }
        }
        for (int length = 2; length <= n; length++) {
            for (int i = 0; i < n + 1 - length; i++) {
                for (int j = 0; j < n + 1 - length; j++) {
                    for (int newLength = 1; newLength < length; newLength++) {
                        const vector<int>& dp1 = dp[newLength][i];
                        const vector<int>& dp2 = dp[length - newLength][i + newLength];
                        dp[length][i][j] |= dp1[j] && dp2[j + newLength];
                        dp[length][i][j] |= dp1[j + length - newLength] && dp2[j];
                    }
                }
            }
        }
        return dp[n][0][0];
    }
};