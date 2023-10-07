#include<bits/stdc++.h>
#define int long long
using namespace std;

signed main(){
	
	int m, n;
	cin>>m>>n;
	
	vector<vector<int>> arr(m, vector<int>(n));
	for(int i=0; i<m; i++){
		for(int j=0; j<n; j++){
			cin>>arr[i][j];
		}
	}
	
	vector<int> rowValue(m, 0);
	
	for(int j=0; j<n;j++){
		int maxi = arr[0][j];
		for(int i=1; i<m; i++)
			maxi = max(maxi, arr[i][j]);
		for(int i=0; i<m; i++)
			if(arr[i][j]==maxi) rowValue[i]++;
	}
	
	int maxi = 0;
	for(int i : rowValue) maxi = max(maxi, i);
	
	vector<int> candidateInd;
	
	for(int i=0; i<m; i++)
		if(maxi==rowValue[i]) candidateInd.push_back(i);
	
	int ansId = 0;
	double ans = 0;
	
	for(int ind : candidateInd){
		double sum = 0;
		for(int j=0; j<n; j++)
			sum += arr[ind][j];
		if(sum>ans){
			ans = sum;
			ansId = ind;
		}
	}
	cout<<ansId<<" "<<maxi;
	return 0;
}


/*

Input:

4 5
7 2 6 6 14
14 12 23 14 17
11 13 13 12 18
11 12 11 50 9

*/