#include<bits/stdc++.h>
#define int long long
using namespace std;

signed main(){

	int n;
	cin>>n;
	vector<int> marks(n);
	for(auto &i : marks) cin>>i;
	int low, high;
	cin>>low>>high;
	
	sort(marks.begin(), marks.end());
	
	vector<vector<int>> ans;
	
	int s = low;
	int e = low;
	
	for(int i=0; i<n; i++){
		int num = marks[i];
		e = num-1;
		if(s<e)
			ans.push_back({s, e});
		else if(s==e)
			ans.push_back({e});
		s = num + 1;
	}
	
	// for last range if any
	s = marks[n-1] + 1;
	e = high;
	if(s==e) ans.push_back({e});
	else if(s<e) ans.push_back({s, e});
	
	for(auto it : ans){
		for(auto i : it) cout<<i<<" ";
		cout<<endl;
	}
	
    return 0;
}
