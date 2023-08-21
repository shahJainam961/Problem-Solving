/*
	You are given a tree consisting of n
	 nodes, and m
	 paths in the tree.

	Your task is to calculate for each node the number of paths containing that node.

	Input

	The first input line contains integers n
	 and m
	: the number of nodes and paths. The nodes are numbered 1,2,…,n
	.

	Then there are n−1
	 lines describing the edges. Each line contains two integers a
	 and b
	: there is an edge between nodes a
	 and b
	.

	Finally, there are m
	 lines describing the paths. Each line contains two integers a
	 and b
	: there is a path between nodes a
	 and b
	.

	Output

	Print n
	 integers: for each node 1,2,…,n
	, the number of paths containing that node.

	Constraints
	1≤n,m≤2⋅105

	1≤a,b≤n

	Example

	Input:
	5 3
	1 2
	1 3
	3 4
	3 5
	1 3
	2 5
	1 4

	Output:
	3 1 3 1 1
	
	Approach:
		
	prerequiste : finding lca by binaryLifting in logN times
	for each path u-->v  nodes[u]++;  nodes[v]++;  nodes[lca(u, v)]--; nodes[parent(lca(u, v)]--;
	nodes[i] = value at that node
	do simple subtreesum
	
	dp(node) = all nodes value sum in the subtree rooted at node
	dp(leaf) = leaf->value;
	dp(node) = node->value + sum over all child dp(child);
	ans : each node's dp value
	
*/

#include<bits/stdc++.h>
using namespace std;

int level[200001];
int up[200001][20];
int dp[200001];

void binaryLifting(int node, int parent, vector<int> adj[]){
	if(node==1) level[node] = 0;
	else level[node] = 1 + level[parent];
	
	up[node][0] = parent;
	for(int i=1; i<20; i++){
		if(up[node][i-1]!=-1){
			up[node][i] = up[up[node][i-1]][i-1];
		}
		else up[node][i] = -1;
	}
	for(int child : adj[node]){
		if(child==parent) continue;
		binaryLifting(child, node, adj);
	}
}

int lift(int node, int jumps){
	if(node==-1 || jumps==0) return node;
	for(int i=19; i>=0; i--){
		if((jumps&(1<<i))!=0){
			return lift(up[node][i],jumps^(1<<i));
		}
	}
	return -1;
}

int getLca(int u, int v){
	if(level[u]<level[v]) return getLca(v, u);
	u = lift(u, level[u]-level[v]);
	if(u==v) return v;
	for(int i=19; i>=0; i--){
		if(up[u][i]!=up[v][i]){
			u = up[u][i];
			v = up[v][i];
		}
	}
	return lift(u, 1);
}

void calcSubTreeSum(int node, int parent, vector<int> adj[], vector<int> &nodes){
	dp[node] = nodes[node];
	for(int child : adj[node]){
		if(child==parent) continue;
		calcSubTreeSum(child, node, adj, nodes);
		dp[node] += dp[child];
	}
}

// 20n + n + m*logn => n + m*logn
void solve(int n, int m, vector<int> adj[], vector<int> paths[], vector<int> &nodes){
	binaryLifting(1, -1, adj);  // 20n
	for(int i=1; i<=m; i++){    // m*logn
		int u = paths[i][0];
		int v = paths[i][1];
		nodes[u]++;
		nodes[v]++;
		int lca = getLca(u, v);
		int parentOfLca = up[lca][0];
		nodes[lca]--;
		if(parentOfLca>0) nodes[parentOfLca]--;
	}
	calcSubTreeSum(1, -1, adj, nodes); // n
	for(int i=1; i<=n; i++) cout<<dp[i]<<" ";
	return;
}

int main(){
	int n, m;
	cin>>n>>m;
	vector<int> adj[n+1];
	vector<int> nodes(n+1, 0);
	for(int i=1; i<n; i++){
		int u, v;
		cin>>u>>v;
		adj[u].push_back(v);
		adj[v].push_back(u);
	}
	vector<int> paths[m+1];
	for(int i=1; i<=m; i++){
		int u, v;
		cin>>u>>v;
		paths[i].push_back(u);
		paths[i].push_back(v);
	}
	solve(n, m, adj, paths, nodes);
}


























