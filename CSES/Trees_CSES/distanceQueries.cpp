
/*

	You are given a tree consisting of n
	 nodes.

	Your task is to process q
	 queries of the form: what is the distance between nodes a
	 and b
	?

	Input

	The first input line contains two integers n
	 and q
	: the number of nodes and queries. The nodes are numbered 1,2,…,n
	.

	Then there are n−1
	 lines describing the edges. Each line contains two integers a
	 and b
	: there is an edge between nodes a
	 and b
	.

	Finally, there are q
	 lines describing the queries. Each line contains two integer a
	 and b
	: what is the distance between nodes a
	 and b
	?

	Output

	Print q
	 integers: the answer to each query.

	Constraints
	1≤n,q≤2⋅105

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
	1
	3
	2


	Approach:
		
	Pre-requistes : LCA finding in logn time
	ans(a, b) = f(a) + f(b) - 2*f(lca(a,b))
	f(node) = distance from the root to the node


*/

#include<bits/stdc++.h>
using namespace std;

int up[200001][20];
int level[200001];
int dp[200001];

void binaryLift(int node, int parent, vector<int> adj[]){
	if(parent==-1) level[node] = 0;
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
		binaryLift(child, node, adj);
	}
}

int lift(int node, int jump){
	if(node==-1 || jump==0) return node;
	for(int i=31; i>=0; i--){
		if((jump&(1<<i))!=0){
			return lift(up[node][i], jump^(1<<i));
		}
	}
	return -1;
}


int getLca(int u, int v){
	if(level[u]<level[v]) return getLca(v, u);
	u = lift(u, level[u] - level[v]);
	if(u==v) return v;
	for(int i=19; i>=0; i--){
		if(up[u][i]!=up[v][i]){
			u = up[u][i];
			v = up[v][i];
		}
	}
	return lift(u, 1);
}

void calcDistanceFromRoot(int node, int parent, vector<int> adj[]){
	if(node==1) dp[node] = 0;
	else dp[node] = 1 + dp[parent];
	
	for(int child : adj[node]){
		if(child==parent) continue;
		calcDistanceFromRoot(child, node, adj);
	}
}


void solve(int n, int q, vector<int> adj[], vector<int> queries[]){
	binaryLift(1, -1, adj);
	calcDistanceFromRoot(1, -1, adj);
	for(int i=0; i<q; i++){
		int a = queries[i][0];
		int b = queries[i][1];
		int lca = getLca(a, b);
		int ans = dp[a] + dp[b] - 2*dp[lca];
		cout<<ans<<endl;
	}
}

int main(){
	int n, q;
	cin>>n>>q;
	vector<int> adj[n+1];
	for(int i=1; i<n; i++){
		int u, v;
		cin>>u>>v;
		adj[u].push_back(v);
		adj[v].push_back(u);
	}
	vector<int> queries[q];
	for(int i=0; i<q; i++){
		int a, b;
		cin>>a>>b;
		queries[i].push_back(a);
		queries[i].push_back(b);
	}
	solve(n, q, adj, queries);
}






















