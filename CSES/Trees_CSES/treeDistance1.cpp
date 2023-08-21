 /*
	 You are given a tree consisting of n
	 nodes.

	Your task is to determine for each node the maximum distance to another node.

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
	, the maximum distance to another node.

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
	2 3 2 3 3
 
 	algo: dynamic programming

    root the tree at node 1
    calculate all nodes depth
    def : depth(node) = longest down path
    recurrence : depth(node) = 1 + for all child max(depth(child))
    basecase : depth(node) = 0 ; node is a leaf node

    main problem
    dp(1) = depth(1)

    need to figure out its childs and subsequent childs which is another subproblem

    def : dp(node) = max distance between node and any other node
    recurrence : dp(node) = max(depth(node), 1 + dp(parent(node)that does not contain node as longest path))
    baseCase dp(1) = depth(1); 
    ans : dp
 
 */
// depthsofchild: 1 2 1 3 4
// prefixMAX:     1 2 2 3 4  
// suffixMAX:     4 4 4 4 4

#include<bits/stdc++.h>
using namespace std;


void calculateDepth(int node, int parent, vector<int> adj[], vector<int> &depth){
    depth[node] = 0;
    for(int child : adj[node]){
        if(child!=parent){
            calculateDepth(child, node, adj, depth);
            depth[node] = max(depth[node], 1+depth[child]);
        }
    }
}

void calulateDistance(int node, int parent, vector<int> adj[], vector<int> &depth, vector<int> &dp, int partialAns){
    
    // Child depths suffixMax, prefixMax
    vector<int> prefixMax, suffixMax;
    for(int child : adj[node]){
        if(child==parent) continue;
        prefixMax.push_back(depth[child]);
        suffixMax.push_back(depth[child]);
    }

    for(int i=1; i<prefixMax.size(); i++) prefixMax[i] = max(prefixMax[i], prefixMax[i-1]);
    for(int i=suffixMax.size()-2; i>=0; i--) suffixMax[i] = max(suffixMax[i], suffixMax[i+1]);

    dp[node] = max(depth[node], 1 + partialAns);

    int cNo = 0;
    for(int child : adj[node]){
        if(child==parent) continue;
        int leftMax = cNo==0?INT_MIN:prefixMax[cNo-1];
        int rightMax = cNo==suffixMax.size()-1?INT_MIN:suffixMax[cNo+1];
        int ppartialAns = max(1+partialAns, max(1+leftMax, 1+rightMax));
        calulateDistance(child, node, adj, depth, dp, ppartialAns);
        cNo++;
    }
    return;

}

void solve(int n, vector<int> adj[]){
    // calculate Depth
    vector<int> depth(n+1, 0);
    calculateDepth(1, 0, adj, depth);

    //main problem
    vector<int> dp(n+1, 0);
    int partialAns = -1;
    calulateDistance(1, 0, adj, depth, dp, partialAns);
    for(int i=1; i<=n; i++) cout<<dp[i]<<" ";
}

int main(){
    int t;
    // cin>>t;
    t = 1;

    while(t--){
        int n; cin>>n;
        vector<int> adj[n+1];
        for(int i=1; i<n; i++){
            int a, b;
            cin>>a>>b;
            adj[a].push_back(b);
            adj[b].push_back(a);
        }
        solve(n, adj);
    }
}
