/*
	You are given a tree consisting of n nodes.

	A matching is a set of edges where each node is an endpoint of at most one edge. What is the maximum number of edges in a matching?

	Input

	The first input line contains an integer n
	: the number of nodes. The nodes are numbered 1,2,…,n
	.

	Then there are n−1
	 lines describing the edges. Each line contains two integers a
	 and b
	: there is an edge between nodes a
	 and b
	.

	Output

	Print one integer: the maximum number of pairs.

	Constraints
	1≤n≤2⋅105

	1≤a,b≤n

	Example

	Input:
	5
	1 2
	1 3
	3 4
	3 5

	Output:
	2

	Explanation: One possible matching is (1,2)
	 and (3,4).


    Approach : 

	def : dp(node, 0) = maximal set size when there is an edge which has one of the endpoint as node.
		  dp(node, 1) = maximal set size when there are no edges which has one of the endpoints as node.
		  
    ans : max(dp(root, 0), dp(root, 1)).
    
    rec : dp(node, 0) = for all child c of node -> sum(max(dp(c, 0), dp(c, 1)).
    	  dp(node, 1) = for all child c of node -> max(prefixesChildSumMax0or1 + suffixesChildSumMax0or1 + 1 + dp(c, 0))
	
	bas : dp(leaf, 0) = dp(leaf, 1) = 0;
*/



#include<bits/stdc++.h>
using namespace std;

void calcTreeMatching(int node, int parent, vector<int> adj[], vector<vector<int>> &dp){
	bool isLeaf = true;
	dp[node][0] = dp[node][1] = 0;
	
	for(int child : adj[node]){
		if(child==parent) continue;
		calcTreeMatching(child, node, adj, dp);
		isLeaf = false;
	}
	if(isLeaf) return;
	vector<int> prefix;
	vector<int> suffix;
	
	for(int child : adj[node]){
		if(child==parent) continue;
		prefix.push_back(max(dp[child][0], dp[child][1]));
		suffix.push_back(max(dp[child][0], dp[child][1]));
	}
	
	for(int i=1; i<(int)prefix.size(); i++) prefix[i] += prefix[i-1];
	for(int i=suffix.size()-2;i>=0; i--) suffix[i] += suffix[i+1];
	
	dp[node][0] = suffix[0];
	
	int cNo = 0;
	for(int child : adj[node]){
		if(child==parent) continue;
		int leftValue = (cNo==0)?0:prefix[cNo-1];
		int rightValue = (cNo==(int)suffix.size()-1)?0:suffix[cNo+1];
		dp[node][1] = max(dp[node][1], leftValue + rightValue + 1 + dp[child][0]);
		cNo++;
	}
	return;
}

void solve(vector<int> adj[], int n){
	vector<vector<int>> dp(n+1, vector<int>(2, 0));
	calcTreeMatching(1, 0, adj, dp);
	cout<<max(dp[1][0], dp[1][1]);
	return;
}

int main(){
	int n;
	cin>>n;
	vector<int> adj[n+1];
	for(int i=1; i<=n-1; i++){
		int a, b;
		cin>>a>>b;
		adj[a].push_back(b);
		adj[b].push_back(a);
	}
	solve(adj, n);
	return 0;
}


