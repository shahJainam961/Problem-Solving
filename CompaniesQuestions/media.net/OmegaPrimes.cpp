#include <bits/stdc++.h>
using namespace std;
int dp[20000][1024];
int mod=1e9+7;
int prime[10]={2,3,5,7,11,13,17,19,23,29};

int getMask(int ele){
  int res = 0;
  
  for(int i=0; i<10; i++){
    if((ele%prime[i])==0){
      res = (res|(1<<i));
    }
  }
  
  return res;
}

int f(int ind, int mask, vector<int> &arr){
  int n = arr.size();
  if(ind == n) return (mask!=0);
  if(dp[ind][mask]!=-1) return dp[ind][mask];
  int way1 = f(ind+1, mask, arr)%mod;
  int way2 = 0;
  
  if((mask&arr[ind])==0){
    way2 = f(ind+1, mask|arr[ind], arr)%mod;
  }
  
  return dp[ind][mask] = (way1 + way2)%mod;
}

int main() {

  int n;
  cin>>n;
  vector<int> arr;
  for(int j=0; j<n; j++){
    int ele;
    cin>>ele;
    bool take = true;
    for(int i=0; (i<10 and prime[i]*prime[i]<=ele); i++){
      if(ele%(prime[i]*prime[i])==0){
        take = false;
        break;
      }
    }
    if(take) arr.push_back(getMask(ele));
  }
  
  memset(dp, -1, sizeof(dp));
  cout<<f(0, 0, arr);
  return 0;
} 


