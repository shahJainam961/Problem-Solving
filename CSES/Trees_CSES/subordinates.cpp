/*
	Given the structure of a company, your task is to calculate for each employee the number of their subordinates.

	Input

	The first input line has an integer n
	: the number of employees. The employees are numbered 1,2,…,n
	, and employee 1
	 is the general director of the company.

	After this, there are n−1
	 integers: for each employee 2,3,…,n
	 their direct boss in the company.

	Output

	Print n
	 integers: for each employee 1,2,…,n	
	 the number of their subordinates.

	Constraints
	1≤n≤2⋅105

	Example

	Input:
	5
	1 1 2 3

	Output:
	4 1 1 0 0


	Approach : 

	def : dp(node) = number of subordinates node has
	ans : all nodes dps
	rec : dp(node) = for all childs c of node -> sum(dp(c) + 1)
	bas : dp(node) = 0; node is a leaf node

*/

#include<bits/stdc++.h>
using namespace std;

void calcSubordinates(int node, int parent, vector<int> adj[], vector<int> &dp){
	
	dp[node] = 0;
	
	for(int child : adj[node]){
		if(child==parent) continue;
		calcSubordinates(child, node, adj, dp);
		dp[node] += dp[child] + 1;
	}
	
}

void solve(vector<int> &boss, int n){

	vector<int> adj[n+1];
	vector<int> dp(n+1, 0);
		
	for(int i=2; i<=n; i++){
		adj[boss[i]].push_back(i);
		adj[i].push_back(boss[i]);
	}	
	calcSubordinates(1, -1, adj, dp);	
	for(int i=1; i<=n; i++) cout<<dp[i]<<" ";
}

int main(){
	int n;
	cin>>n;
	vector<int> boss(n+1, -1);
	for(int i=2; i<=n; i++){
		cin>>boss[i];
	}
	solve(boss, n);
	return 0;
}


