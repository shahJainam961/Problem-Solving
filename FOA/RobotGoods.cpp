#include<bits/stdc++.h>
#define int long long
using namespace std;


bool isValid(int i, int j, int m, int n){
	return i>=0 and i<m and j>=0 and j<n;
}

int f(int i, int j1, int j2, vector<vector<int>> &goods, vector<vector<vector<int>>> &dp){
	int m = goods.size();
	int n = goods[0].size();
	
	if(i==m) return 0;
    if(dp[i][j1][j2]!=-1) return dp[i][j1][j2];
	int ans = 0;
	
	int dc[] = {-1, 0, 1};
	
	for(int k1=0; k1<3; k1++){
		for(int k2=0; k2<3; k2++){
			int ni = i + 1;
			int nj1 = j1 + dc[k1];
			int nj2 = j2 + dc[k2];
			if(isValid(ni, nj1, m, n) and isValid(ni, nj2, m, n)){
				ans = max(ans, f(ni, nj1, nj2, goods, dp));
			}
		}
	}
	
	ans += (j1==j2)?goods[i][j1]:goods[i][j1]+goods[i][j2];
	
	return dp[i][j1][j2] = ans;
}

int getMaxGoods(vector<vector<int>> &goods){
	int n = goods[0].size();
	int m = goods.size();
	vector<vector<vector<int>>> dp(m, vector<vector<int>>(n, vector<int>(n, -1)));
	return f(0, 0, n-1, goods, dp);
}

signed main(){
	int m, n;
	cin>>m>>n;
	
	vector<vector<int>> goods(m, vector<int>(n));
	
	for(int i=0; i<m; i++)
		for(int j=0; j<n; j++)
			cin>>goods[i][j];
			
	int ans = getMaxGoods(goods);
	cout<<ans;
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