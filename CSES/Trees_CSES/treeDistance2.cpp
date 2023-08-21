
/*

	You are given a tree consisting of n
	 nodes.

	Your task is to determine for each node the sum of the distances from the node to all other nodes.

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

	Print n
	 integers: for each node 1,2,…,n
	, the sum of the distances.

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
	6 9 5 8 8

	def1 : nodes(i) = total nodes in the subtree of i including i
	recurrence : nodes(i) = sum of all child of i nodes(child) + 1
	baseCase : nodes(i) = 1; i is a leaf node

	def2 : subTreeSum(i) = total sum distance from node i to all other node in subtree of i
	recurrence : subTreeSum(i) = for all child do sum of (subTreeSum(child) + nodes(child))
	baseCase : subTreeSum(i) = 0; i is a leaf node

	main problem defnition( rerooting technique )
	baseCase: dp(1) = subTreeSum(1)
	for each child Ci: dp(Ci) = subTreeSum(Ci) + partialAns + totalNodes - nodes(Ci);
	partialAns(i|Ci) = dp(i) - subTreeSum(Ci) - nodes(Ci);

	ans : dp

*/

#include<bits/stdc++.h>
#define ll long long
using namespace std;

void calcNodes(ll node, ll parent, vector<ll> adj[], vector<ll> &nodes){
    nodes[node] = 1;
    for(ll child : adj[node]){
        if(child == parent) continue;
        calcNodes(child, node, adj, nodes);
        nodes[node] += nodes[child];
    }
}

void calcSubTreeSum(ll node, ll parent, vector<ll> adj[], vector<ll> &subTreeSum, vector<ll> &nodes){
    subTreeSum[node] = 0;
    for(ll child : adj[node]){
        if(child==parent) continue;
        calcSubTreeSum(child, node, adj, subTreeSum, nodes);
        subTreeSum[node] += subTreeSum[child] + nodes[child];
    }
}

void calcAns(ll node, ll parent, vector<ll> adj[], vector<ll> &nodes, vector<ll> &subTreeSum, ll partialAns, vector<ll> &dp, ll n){

    if(node==1) dp[node] = subTreeSum[node];
    else dp[node] = subTreeSum[node] + partialAns + n - nodes[node];

    for(ll child : adj[node]){
        if(child==parent) continue;
        ll newPartialAns = dp[node] - subTreeSum[child] - nodes[child];
        calcAns(child, node, adj, nodes, subTreeSum, newPartialAns, dp, n);
    }
}

void solve(ll n, vector<ll> adj[]){
    vector<ll> subTreeSum(n+1, 0);
    vector<ll> nodes(n+1, 0);
    vector<ll> dp(n+1, 0);

    calcNodes(1, 0, adj, nodes);
    calcSubTreeSum(1, 0, adj, subTreeSum, nodes);
    calcAns(1, 0, adj, nodes, subTreeSum, -1, dp, n);

    for(ll i=1; i<=n; i++) cout<<dp[i]<<" "; 
}

class Solution {

    int f(int mask, int ind, int n){

        if(mask == 0 || ind==n) return 1;
        int ans = 0;

        for(int num=1; num<=n; num++){
            if((mask&(1<<(num-1)))==1  and (num%(ind+1)==0 or (ind+1)%num==0)){
                int newMask = mask ^ (1<<(num-1));
                ans += f(newMask, ind+1, n);
            }
        }
        return ans;
    }

public:
    int countArrangement(int n) {
        return f((1<<n)-1, 0, n);
    }
};

int main(){
    // ll t;
    // // cin>>t;
    // t = 1;

    // while(t--){
    //     ll n; cin>>n;
    //     vector<ll> adj[n+1];
    //     for(ll i=1; i<n; i++){
    //         ll a, b;
    //         cin>>a>>b;
    //         adj[a].push_back(b);
    //         adj[b].push_back(a);
    //     }
    //     solve(n, adj);
    // }

    Solution s;
    cout<<s.countArrangement(2);
    
}
