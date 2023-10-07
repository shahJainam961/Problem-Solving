#include<bits/stdc++.h>
#define int long long
using namespace std;

signed main(){
	int m; // num of arrays
	int n; // num of elements in each arr
	cin>>m>>n;
	
	int arr[m][n];
	
	for(int i=0; i<m; i++){
		for(int j=0; j<n; j++){
			cin>>arr[i][j];
		}
	}
	
	priority_queue<vector<int>, vector<vector<int>>, greater<vector<int>>> pq;
	vector<int> range;
	int len = INT_MAX;
	int maxi = INT_MIN;
	
	for(int i=0; i<m; i++){
		pq.push({arr[i][0], i, 0});
		maxi = max(maxi, arr[i][0]);
	}
	
	range.push_back(pq.top()[0]);
	range.push_back(maxi);
	len = maxi - pq.top()[0];
	
	while(1){
		
		auto it = pq.top(); pq.pop();
		int arrNum = it[1];
		int j = it[2];
		
		if(j+1==n) break;
		
		pq.push({arr[arrNum][j+1], arrNum, j+1});
		maxi = max(maxi, arr[arrNum][j+1]);
		if(len > maxi - pq.top()[0]){
			range[0] = pq.top()[0];
			range[1] = maxi;
			len = range[1] - range[0];
		}
	}
	cout<<range[0]<<" "<<range[1];
	
    return 0;
}



