#include<bits/stdc++.h>
using namespace std;

void evaluateLPS(vector<int> &lps, string &needle){
    int n = needle.size();
    int i=1;
    int len = 0;
    lps[0] = 0;

    while(i<n){
        if(needle[i]==needle[len]){
            len++;
            lps[i] = len;
            i++;
        }
        else{
            if(len==0){
                lps[i] = 0;
                i++;
            }
            else len = lps[len-1];
        }
    }
}

void solve(string &str, string &pattern){
    int n = str.size();
    int m = pattern.size();

    vector<int> lps(m, 0);
    evaluateLPS(lps, pattern);

    int i=0;
    int j=0;

    while(i<n){
        if(str[i]==pattern[j]){
            i++;
            j++;
            if(j==m){
                cout<<i-j<<" ";
                j = lps[j-1];
            }
            else{
                if(j==0) i++;
                else j = lps[j-1];
            }
        }
    }
}

    // void solve(string haystack, string needle) {
    //     int n = haystack.size();
    //     int m = needle.size();
    //     vector<int> occurences;
    //     vector<int> lps(m, 0);
    //     evaluateLPS(lps, needle);
    //     int i=0;
    //     int j=0;

    //     while(i<n){
    //         if(haystack[i]==needle[j]){
    //             i++; j++;
    //             if(j==m){
    //                 cout<<i-j<<" ";
    //                 j = lps[j-1];
    //             }
    //         }
    
    //         else{
    //             if(j==0) i++;
    //             else j = lps[j-1];
    //         }
    //     }
    // }

int main(){
    string str="ababcababaad", pattern="aba";
    // cin>>str>>pattern;
    solve(str, pattern);
    return 0;
}