/*

Problem 1

There are N cities numbered from 1 to N connected by M bidirectional roads. A concert is going to be held in each city and i_th city concert costs A[i] amount. Travelling through the roads also costs some amount given.

For each city i from 1 to N : find the minimum amount a person from city i has to spend to visit a concert in any of the city and come back to own city.
It may not be guarenteed that each city is reachable from other city.

N,M<=10^5

Input :
n -> number of nodes
price[] -> price at nodes
m -> number of edges
edges[x, y, z] -> x to y using z cost

Output
ans for all nodes minimizing the cost to attend and returning back to src city

*/





/*
Approach:
    Let price of ticket in city i is price(i)
    and the main answer of city i be ans(i)
    initially ans(i) = price(i) for all cities
    We know at city c a person will by at that city only provided ticket price at city c is the lowest among all cities
    Hence ans(c) = price(c) will not change
    Add all cities in min heap -> {ans[i], i} for all cities
    while min heap not empty
        Relaxing neightbours of c (minCost City) and poping c out
        Forall neigbour j
            if(ans[j]>2*cost[c][j]+ans[c]){
                ans[j]>2*cost[c][j]+ans[c]
                push {ans[j], j} in min heap
            }
    return ans;
*/





#include<bits/stdc++.h>
using namespace std;


void solve(int n, vector<int> &cost, vector<vector<int>> adj[]){

    vector<int> ans(n+1, 0);
    for(int i=1; i<=n; i++) ans[i] = cost[i];
    
    // Initially all can buy tickets at theirs cities and pq will have the city which has the lowest cost at the top
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    for(int i=1; i<=n; i++) pq.push({ans[i], i});

    while(!pq.empty()){

        auto it = pq.top(); pq.pop();
        int currentCity = it.second;
        int currentCost = it.first;

        for(auto gt : adj[currentCity]){
            int adjCity = gt[0];
            int edgeWeight = gt[1];

            if(ans[adjCity] > currentCost + 2*edgeWeight){
                ans[adjCity] = currentCost + 2*edgeWeight;
                pq.push({ans[adjCity], adjCity});
            }

        }
    }

    // Printing the ans------------------------------------------
    for(int node=1; node<=n; node++) cout<<ans[node]<<" ";
    // -----------------------------------------------------------
    return;
}

int main(){

    int t;
    // cin>>t;
    t = 1;

    while(t--){
        int n; cin>>n;
        vector<int> cost(n+1, 0);
        for(int i=1; i<=n; i++) cin>>cost[i];
        int m; cin>>m;
        vector<vector<int>> adj[n+1];
        for(int  i=1; i<=m; i++){
            int u, v, weight;
            cin>>u>>v>>weight;
            adj[u].push_back({v, weight});
            adj[v].push_back({u, weight});
        }
        solve(n, cost, adj);
    }

}
