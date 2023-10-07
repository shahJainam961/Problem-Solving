#include<bits/stdc++.h>
#define int long long
using namespace std;

signed main(){
	
	int n, m;
	cin>>n>>m;
	
	vector<vector<int>> adj[n];
	for(int i=0; i<m; i++){
		int u, v, stateDistance, nationalDistance;
		cin>>u>>v>>stateDistance>>nationalDistance;
		u--; v--;
		adj[u].push_back({v, stateDistance, nationalDistance});
		adj[v].push_back({u, stateDistance, nationalDistance});
	}
	
	int src, dst;
	cin>>src>>dst;
	src--; dst--;
	
	priority_queue<vector<int>, vector<vector<int>>, greater<vector<int>>> pq;
	vector<vector<int>> dist(n, vector<int>(2, 1e9));
	pq.push({0, src, 0});
	dist[src][0] = dist[src][1] = 0;
	
	while(!pq.empty()){
		auto it = pq.top(); pq.pop();
		int curDist = it[0];
		int city = it[1];
		int hasUsedNational = it[2];
		
		for(auto neig : adj[city]){
			int nextCity = neig[0];
			int stateDis = neig[1];
			int natDis = neig[2];
			
			if(hasUsedNational==0){
				if(dist[nextCity][1] > curDist + natDis){
					dist[nextCity][1] = curDist + natDis;
					pq.push({dist[nextCity][1], nextCity, 1});
				}
				if(dist[nextCity][0] > curDist + stateDis){
					dist[nextCity][0] = curDist + stateDis;
					pq.push({dist[nextCity][0], nextCity, 0});
				}
			}
			else{
				if(dist[nextCity][1] > curDist + stateDis){
					dist[nextCity][1] = curDist + stateDis;
					pq.push({dist[nextCity][1], nextCity, 1});
				}	
			}
		}
	}
	int answer = min(dist[dst][0], dist[dst][1]); // if answer==1e9 then print answer -1
	cout<<answer;
    return 0;
}



