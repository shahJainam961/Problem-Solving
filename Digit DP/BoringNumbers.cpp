#include<bits/stdc++.h>
using namespace std;

class Solution{

public:
    Solution(){}

    int f(string &s, int ind, int pos, int tight, vector<vector<vector<int>>> &dp){
        if(dp[ind][pos][tight] != -1) return dp[ind][pos][tight];
        int n = s.size();
        if(ind==n) return dp[ind][pos][tight] = pos!=2;
        int ans = 0;
        int ub;
        if(tight) ub = s[ind]-'0';
        else ub = 9;

        for(int dig=0; dig<=ub; dig++){
            if(pos==2){
                if(dig==0) ans += f(s, ind+1, 2, 0, dp);
                else{
                    if(dig&1) ans += f(s, ind+1, 0, tight&&(dig==ub), dp);
                }
            }
            else{
                if(dig%2==pos) ans += f(s, ind+1, 1-pos, tight&&(dig==ub), dp);
            }
        }
        return dp[ind][pos][tight] = ans;
    }

    bool isBoringNumber(string &s){
        int pos = 1;
        int ind = 0;
        int n = s.size();

        while(ind<n){
            if((s[ind]-'0')%2 != pos) return false;
            pos = 1-pos;
            ind++;
        }
        return true;
    }

    int getBoringNumbers(string &s1, string &s2){
        vector<vector<vector<int>>> dp(s1.size()+1, vector<vector<int>>(3, vector<int>(2, -1)));
        int ans1 = f(s1, 0, 2, 1, dp);
        vector<vector<vector<int>>> dp1(s2.size()+1, vector<vector<int>>(3, vector<int>(2, -1)));
        int ans2 = f(s2, 0, 2, 1, dp1);
        return ans2-ans1+isBoringNumber(s1);
    }

};

int main(){
    // #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    // #endif

    int t;
    cin>>t;
    Solution* sol = new Solution();

    while(t--){
        string s1, s2;
        cin>>s1>>s2;
        cout<<sol->getBoringNumbers(s1, s2);
        if(t!=0) cout<<endl;
    }

}