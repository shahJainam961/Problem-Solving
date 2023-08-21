#include<bits/stdc++.h>
using namespace std;

int up[200001][20];
vector<int> adj[200001];
vector<int> level(200001, -1);


void binaryLifting(int node, int parent){
	up[node][0] = parent;
	for(int i=1; i<20; i++){
		if(up[node][i-1]!=-1)
			up[node][i] = up[up[node][i-1]][i-1];
		else up[node][i] = -1;
	}
	
	for(int child : adj[node]){
		if(child!=parent)
			binaryLifting(child, node);
	}
}

void findLevels(int node, int parent){
	if(node==1) level[node] = 0;
	else level[node] = 1 + level[parent];
	
	for(int child : adj[node]){
		if(child!=parent)
			findLevels(child, node);
	}
}

int lift(int node, int jumps){
	if(node==-1 || jumps==0)  return node;
	for(int i=31; i>=0; i--){
		if((jumps&(1<<i))!=0){
			return lift(up[node][i], jumps^(1<<i));
		}
	}
	return -1;
}

// O(log sq n)
int getAns1(int u, int v){
		
	if(level[u]<level[v]) return getAns1(v, u);
	
	u = lift(u, level[u]-level[v]);
	
	int low = 0;
	int high = level[v];
	int ans = 0;

	while(low<=high){
		int mid = low + (high-low)/2;
		
		int lca1 = lift(u, mid);
		int lca2 = lift(v, mid);
		
		if(lca1 == lca2){
			ans = mid;
			high = mid-1;
		}
		else low = mid+1;
	}
	
	return lift(u, ans);
}

//O(log n)
int getAns(int u, int v){
		
	if(level[u]<level[v]) return getAns(v, u);
	
	u = lift(u, level[u]-level[v]);
	
	if(u==v) return u;

	for(int i=19; i>=0; i--){
		if(up[u][i]!=up[v][i]){
			u = up[u][i];
			v = up[v][i];
		}
	}

	return lift(u, 1);
}


int main(){
	int n;
	int q;
	cin>>n>>q;
	
	
	for(int i=2; i<=n; i++){
		int ele;
		cin>>ele;
		adj[i].push_back(ele);
		adj[ele].push_back(i);
	}
	findLevels(1, -1);
	binaryLifting(1, -1);
	for(int i=0; i<q; i++){
		int node1;
		int node2;
		cin>>node1>>node2;
		cout<<getAns(node1, node2)<<endl;
	}
	return 0;
}
