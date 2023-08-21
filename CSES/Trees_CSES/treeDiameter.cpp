/*
	You are given a tree consisting of n
	nodes.

	The diameter of a tree is the maximum distance between two nodes. Your task is to determine the diameter of the      tree.

	Input

	The first input line contains an integer n
	: the number of nodes. The nodes are numbered 1,2,…,n.

	Then there are n−1
	 lines describing the edges. Each line contains two integers a
	 and b
	: there is an edge between nodes a
	 and b.

	Output

	Print one integer: the diameter of the tree.

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
	3

	Explanation: The diameter corresponds to the path 2→1→3→5.


    Approach : 

	algo1: hard to prove
	
    pick any node u -> do bfs from that node
    there will be node v that is farthest node from node u
    from node v initiate another bfs and farthest node lets say k
    longest path v to k

	algo2: IMPLEMENTED dynamic programming
	
    root it at any node lets say node 1
    two options at any node it will be in the path or not in the path
   
    def: dp(node, 0) max diameter of subtree rooted at node and path not consist of node
         dp(node, 1) max diameter of subtree rooted at node and path consist of node
         
    ans: max(dp(1, 0), dp(1, 1))
    
 	rec: dp(node, 0) = for all child of node max(  ""max(dp(child, 0), dp(child, 1))"" )
         dp(node, 1) = max(downpath(child)) + (numOfChild>1?secondMax(downpath(child)) + 2:1)

    downpath(node) : longest path in the subtree rooted at node that starts at node
    basecase: downpath(leaf) = 0
    recurrence: downpath(node) = for all child of the node max(downpath(child)) + 1;

*/

#include<bits/stdc++.h>
using namespace std;


void calculateDownPath(int node, int parent, vector<int> adj[], vector<int> &downpath){
    downpath[node] = 0;
    for(int child : adj[node]){
        if(child!=parent){
            calculateDownPath(child, node, adj, downpath);
            downpath[node] = max(downpath[node], 1 + downpath[child]);
        }
    }
}

void calculateDiameter(int node, int parent, vector<int>adj[], vector<int> &downpath, vector<vector<int>> &dp){

    dp[node][0] = dp[node][1] = 0;
    bool leaf = true;
    for(int child : adj[node]){
        if(child!=parent){
            leaf = false;
            calculateDiameter(child, node, adj, downpath, dp);
        }
    }
    if(leaf) return;

    // current node is not in the path
    for(int child : adj[node]){
        if(child!=parent){
            dp[node][0] = max(dp[node][0], max(dp[child][0], dp[child][1]));
        }
    }

    // current node is in the path
    int longestPath = 0;
    vector<int> childDownpaths;
    for(int child : adj[node]){
        if(child!=parent) childDownpaths.push_back(downpath[child]);
    }
    sort(childDownpaths.begin(), childDownpaths.end(), greater<int>());
    longestPath += (1 + childDownpaths[0]);
    if(childDownpaths.size()>1){
        longestPath += (1 + childDownpaths[1]);
    }
    dp[node][1] = longestPath;
}

int solve(int n, vector<int> adj[]){

    vector<int> downpath(n+1, 0);
    calculateDownPath(1, 0, adj, downpath);

    vector<vector<int>> dp(n+1, vector<int>(2, 0));
    calculateDiameter(1, 0, adj, downpath, dp);
    return max(dp[1][1], dp[1][0]);
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
        cout<<solve(n, adj);
    }
}





