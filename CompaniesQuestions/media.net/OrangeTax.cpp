/*

Problem Description

You live in orange town. There are a lot of markets around that are connected with roads.
These markats sell oranges at some prices.
The town is not very well developed and they still use carts to transport goods from one place to the other.
The roads connect two markets together and have two attributes associated with them.
One is the price to go from one market to the other in an empty cart and the other is the tax factor.
The tax factor is the number by which the price associated with a road needs to be multiplied,
so it can go from one market to the other if you are carrying oranges in your cart.
So if a road's original price was 5 coins and tax factor was 6,
then in an empty cart it would take 5 coins to travel the road,
but if the cart contained oranges, it would cost 5*6=30 coins.

You wonder what would be the cheapest way to buy oranges if you were initially at each market.
You can either buy at the market you are at or travel to some other market,
buy oranges there, and travel back to the original market

You are given an integer A denoting the number of total markets in orange town,
an integer array B denoting the price of purchasing oranges at each market and a 2-D array C containing the information
about the roads. First two values denote the market numbers that are bi-directionally connected via a road,
3rd value is the price. D is tax factor of Orange Town

Find and return the required array.
The minimum cost to buy oranges at each market such that the starting and ending point is that market.

Problem Constraints

2 <= A <= 1e5
B.size() == A
1 <= B[i] <= 1e7
1 <= C.size() <= 2e5
1 <= C[0] <= A
1 <= C[1] <= A
1 <= C[2] <= 1e3
1<=D<=5

*/

#include<bits/stdc++.h>
using namespace std;


void solve(int n, vector<int> &cost, vector<vector<int>> &edges, int tax){
    vector<vector<int>> adj[n+1];
    for(auto edge : edges){
        int u = edge[0]; int v = edge[1]; int weight = edge[2];

        adj[u].push_back({v, weight});
        adj[v].push_back({u, weight});
        
    }

    vector<int> ans(n+1, 0);
    for(int i=1; i<=n; i++) ans[i] = cost[i];

    priority_queue<vector<int>, vector<vector<int>>, greater<vector<int>>> pq;
    for(int i=1; i<=n; i++) pq.push({ans[i], i});
    
    while(!pq.empty()){
        auto it = pq.top(); pq.pop();

        int node = it[1];
        int cost = it[0];

        for(auto gt : adj[node]){
            int adjNode = gt[0];
            int weight = gt[1];
            int taxWeight = tax*weight;

            if(ans[adjNode] > weight + taxWeight + ans[node]){
                ans[adjNode] = weight + taxWeight + ans[node];
                pq.push({ans[adjNode], adjNode});
            }
        }
    }

    // Printing the answer
    for(int i=1; i<=n; i++) cout<<ans[i]<<" ";
    

}


int main(){

    int t;
    // cin>>t;
    t = 1;

    while(t--){
        int n;
        cin>>n;
        vector<int> cost(n+1, 0);
        for(int i=1; i<=n; i++) cin>>cost[i];
        int m; cin>>m;
        vector<vector<int>> edges;
        for(int  i=1; i<=m; i++){
            int u, v, weight;
            cin>>u>>v>>weight;
            edges.push_back({u, v, weight});
        }
        int tax;
        cin>>tax;
        solve(n, cost, edges, tax);
    }

}


/*

FollowUp Question if for going out of the city you have certain tax
so for all cities cityTax[i] may be different

Idea:



*/