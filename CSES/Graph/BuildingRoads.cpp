#include<bits/stdc++.h>
#define int long long
using namespace std;

void bfs(int node, vector<int> adj[], vector<bool> &vis){
	
	vis[node] = true;
	queue<int> q;
	q.push(node);
	
	while(!q.empty()){
		auto it = q.front(); q.pop();
		for(int child : adj[it]){
			if(!vis[child]){
				q.push(child);
				vis[child] = true;
			}
		}
	}
	return;
}

pair<int, vector<vector<int>>> f(int n, int m, vector<vector<int>> &roads){
	vector<int> adj[n+1];
	for(auto road : roads){
		adj[road[0]].push_back(road[1]);
		adj[road[1]].push_back(road[0]);
	}
	vector<bool> vis(n+1, false);
	vector<int> path;
	
	for(int i=1; i<=n; i++){
		if(!vis[i]){
			path.push_back(i);
			bfs(i, adj, vis);
		}
	}
	
	vector<vector<int>> ans;
	for(int i=0; i<(int)path.size()-1;i++){
		ans.push_back({path[i], path[i+1]});
	}
	return {ans.size(), ans};	
}

signed main(){
	
	int n, m;
	cin>>n>>m;
	
	vector<vector<int>> roads;
	for(int i=0; i<m; i++){
		int u, v;
		cin>>u>>v;
		roads.push_back({u, v});
	}
	
	pair<int, vector<vector<int>>> p = f(n, m, roads);
	
	cout<<p.first<<endl;
	for(auto it : p.second){
		cout<<it[0]<<" "<<it[1]<<endl;
	}
	
    return 0;
}
