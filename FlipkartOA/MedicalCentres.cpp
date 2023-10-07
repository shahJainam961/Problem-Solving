#include<bits/stdc++.h>
#define int long long
using namespace std;

signed main(){

	// int n;
	// cin>>n;
	// vector<int> arr(n);
	// for(auto &i : arr) cin>>i;
// 	
	// int ans = 0;
	// priority_queue<int> pq;
	// for(int num : arr) pq.push(num);
// 	
	// while(pq.size()>1){
		// int num1 = pq.top(); pq.pop();
		// int num2 = pq.top(); pq.pop();
		// ans += (2*num2);
		// num1 = num1 - num2;
		// if(num1>0) pq.push(num1);
	// }
	// if(pq.size()==1) ans++;
	// cout<<ans;	
// 
    // return 0;
    
    
    int n;cin>>n;
  int maxi = INT_MIN;
  int sum = 0;
  for(int i=0; i<n; i++){
    int x;cin>>x;
    sum += x;
    maxi = max(maxi, x);
  }
  
  sum -= maxi;
  
  if(sum >= maxi){
    cout<<sum + maxi<<endl;
  }else{
    cout<<2*sum + 1<<endl;
  }

  return 0;
    
}



