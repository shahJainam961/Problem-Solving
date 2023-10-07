#include<bits/stdc++.h>
#define int long long
using namespace std;

bool comp(vector<int> &a, vector<int> &b){
	if(a[1] == b[1]) return a[0] <= b[0];
	else return a[1] < b[1];
}

signed main(){
	
	int n;
	cin>>n;
	vector<int> start(n), end(n);
	for(int &i : start) cin>>i;
	for(int &i : end) cin>>i;
	
	vector<vector<int>> meetings;
	for(int i=0; i<n; i++) meetings.push_back({start[i], end[i]});
	
	sort(meetings.begin(), meetings.end(), comp);
	
	int answer = 1;
	int lastEnd = meetings[0][1];
	for(int i=1; i<n; i++){
		if(lastEnd<=meetings[i][0]){
			answer++;
			lastEnd = meetings[i][1];
		}
	}
 	cout<<answer;
	return 0;
}
