#include<bits/stdc++.h>
#define ll long long
using namespace std;

class Solution{

public:
    Solution(){}

    ll f(string &s, int ind, int tight){
        int n = s.size();
        if(ind==n) return 0;

        ll ans = 0;
        ll ub = tight?s[ind]-'0':9;

        for(int dig=0; dig<=ub; dig++){
            ans += dig + f(s, ind+1, tight&&(dig==ub));
        }
        return ans;
    }

    ll getSum(string &s){
        int ind = 0;
        int n = s.size();
        ll sum = 0;
        while(ind<n){
            sum += (s[ind]-'0'); ind++;
        }
        return sum;
    }

    ll digitSum(string &s1, string &s2){
        ll ans1 = f(s1, 0, 1);
        ll ans2 = f(s2, 0, 1);
        return ans1;
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
        ll l, r;
        cin>>l>>r;
        l--;
        string s1= to_string(l);
        string s2 = to_string(r);
        cout<<sol->digitSum(s1, s2);
        if(t!=0) cout<<endl;
    }

}