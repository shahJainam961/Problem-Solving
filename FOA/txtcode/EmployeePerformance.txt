#include<bits/stdc++.h>
#define int long long
using namespace std;

signed main(){
	
	int n;
	cin>>n;
	vector<int> employeeScore(n);
	for(auto &i : employeeScore) cin>>i;
	int k;
	cin>>k;
	
	vector<int> maxi(n), mini(n);
	maxi[0] = employeeScore[0];
	for(int i=1; i<n; i++) maxi[i] = max(employeeScore[i], maxi[i-1]);
	mini[n-1] = employeeScore[n-1];
	for(int i=n-2; i>=0; i--) mini[i] = min(employeeScore[i], mini[i+1]); 
	
	int answer = 0;
	for(int i=0; i<=n-2; i++)
		answer += (maxi[i]+mini[i+1] >= k);
		
	cout<<answer;
    return 0;
}
