/*
	You are given a rooted tree consisting of n
	 nodes. The nodes are numbered 1,2,…,n
	, and node 1
	 is the root. Each node has a value.

	Your task is to process following types of queries:
	change the value of node s
	 to x

	calculate the sum of values in the subtree of node s

	Input

	The first input line contains two integers n
	 and q
	: the number of nodes and queries. The nodes are numbered 1,2,…,n
	.

	The next line has n
	 integers v1,v2,…,vn
	: the value of each node.

	Then there are n−1
	 lines describing the edges. Each line contans two integers a
	 and b
	: there is an edge between nodes a
	 and b
	.

	Finally, there are q
	 lines describing the queries. Each query is either of the form "1 s
	 x
	" or "2 s
	".

	Output

	Print the answer to each query of type 2.

	Constraints
	1≤n,q≤2⋅105

	1≤a,b,s≤n

	1≤vi,x≤109

	Example

	Input:
	5 3
	4 2 5 2 1
	1 2
	1 3
	3 4
	3 5
	2 3
	1 5 3
	2 3

	Output:
	8
	10
	
	Approach
	
	build a flattened array of the given tree according to the order of elements in the dfs
	then simple point update and range queries because subtree values will be a continuous subarray and range can be
	maintained by timer.
	
*/
#include<bits/stdc++.h>
#define ll long long
using namespace std;

class SegTree{
	private:
		vector<ll> seg;
		
	public:
		SegTree(ll n){
			seg.resize(4*n);
		}
		
		void build(ll ind, ll low, ll high, vector<ll> &arr){
			if(low==high){
				seg[ind] = arr[low];
				return;
			}
			ll mid = low + (high-low)/2;
			build(2*ind+1, low, mid, arr);
			build(2*ind+2, mid+1, high, arr);
			seg[ind] = seg[2*ind+1] + seg[2*ind+2];
		}
		
		void pointUpdate(ll ind, ll low, ll high, ll key, ll val){
			if(low==high){
				seg[ind] = val;
				return;
			}
			ll mid = low + (high-low)/2;
			if(key<=mid) pointUpdate(2*ind+1, low, mid, key, val);
			else pointUpdate(2*ind+2, mid+1, high, key, val);
			seg[ind] = seg[2*ind+1] + seg[2*ind+2];
		}
		
		ll rangeQueries(ll ind, ll low, ll high, ll l, ll r){
			// In the range l low high r
			if(l<=low and high<=r) return seg[ind];
			
			//Not in the range l r low high OR low high l r
			else if(r<low or high<l) return 0;
			
			else{
				ll mid = low + (high-low)/2;
				ll leftValue = rangeQueries(2*ind+1, low, mid, l, r);
				ll rightValue = rangeQueries(2*ind+2, mid+1, high, l, r);
				return leftValue + rightValue;
			}
		}
};

void dfs(ll node, ll parent, vector<ll> adj[], vector<ll> &arr, vector<ll> &end, ll &timer, vector<ll> &values, vector<ll> &start){
	start[node] = timer;
	arr[timer] = values[node];
	for(ll child : adj[node]){
		if(child==parent) continue;
		timer++;
		dfs(child, node, adj, arr, end, timer, values, start);
	}
	end[node] = timer;
}

void solve(ll n, ll q, vector<ll> adj[], vector<ll> queries[], vector<ll> &values){
	
	ll timer = 1;
	vector<ll> end(n+1);
	vector<ll> arr(n+1);
	vector<ll> start(n+1);
	dfs(1, -1, adj, arr, end, timer, values, start);
	SegTree s(arr.size());
	s.build(1, 1, arr.size(), arr);
	
	for(ll i=0; i<q; i++){
		if(queries[i][0]==1){
			ll key = start[queries[i][1]];
			ll val = queries[i][2];
			s.pointUpdate(1, 1, arr.size(), key, val); 
		}
		else{
			ll node = queries[i][1];
			ll l = start[node];
			ll r = end[node];
			cout<<s.rangeQueries(1, 1, arr.size(), l, r)<<endl;
		}
	}
}


int main(){
	ll n,q;
	cin>>n>>q;
	vector<ll> values(n+1);
	for(ll i=1; i<=n; i++) cin>>values[i];
	vector<ll> adj[n+1];
	for(ll i=1; i<n; i++){
		ll u, v;
		cin>>u>>v;
		adj[u].push_back(v);
		adj[v].push_back(u);
	}
	vector<ll> queries[q];
	for(ll i=0; i<q; i++){
		ll type;
		cin>>type;
		if(type==1){
			ll node, val;
			cin>>node>>val;
			queries[i].push_back(type);
			queries[i].push_back(node);
			queries[i].push_back(val);
		}
		else{
			ll node;
			cin>>node;
			queries[i].push_back(type);
			queries[i].push_back(node);
		}
	}
	solve(n, q, adj, queries, values);
	return 0;
}


