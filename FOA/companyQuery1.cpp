#include<bits/stdc++.h>
using namespace std;

int up[200001][20];
vector<int> adj[200001];

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

int getAns(int node, int jumps){
	if(node==-1 || jumps==0)  return node;
	for(int i=31; i>=0; i--){
		if((jumps&(1<<i))!=0){
			return getAns(up[node][i], jumps^(1<<i));
		}
	}
	return -1;
}

int main(){
	int n;
	int q;
	cin>>n>>q;
	
	int ele;
	for(int i=2; i<=n; i++){
		cin>>ele;
		adj[i].push_back(ele);
		adj[ele].push_back(i);
	}
	binaryLifting(1, -1);
	for(int i=0; i<q; i++){
		int node;
		int jumps;
		cin>>node>>jumps;
		cout<<getAns(node, jumps)<<endl;
	}
	return 0;
}

















