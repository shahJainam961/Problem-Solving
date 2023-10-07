#include<bits/stdc++.h>
using namespace std;

void calcSubTreeSum(int node, int parent, vector<int> adj[], vector<int> &val, vector<int> &subTreeSum){
    int ans = 0;
    for(int child : adj[node]){
        if(child==parent) continue;
        calcSubTreeSum(child, node, adj, val, subTreeSum);
        ans = max(ans, subTreeSum[child]);
    }
    ans += val[node];
    subTreeSum[node] = ans;
}

void calcAns(int node, int parent, int partialAns, vector<int> adj[],
                    vector<int> &val, vector<int> &subTreeSum, vector<int> &ans){

    vector<int> prefixMax, suffixMax;
    for(int child : adj[node]){
        if(child==parent) continue;
        prefixMax.push_back(subTreeSum[child]);
        suffixMax.push_back(subTreeSum[child]);
    }
    for(int i=1; i<prefixMax.size(); i++) prefixMax[i] += prefixMax[i-1];
    for(int i=suffixMax.size()-2; i>=0; i--) suffixMax[i] += suffixMax[i+1];  
    

    int cNo = 0;
    for(int child : adj[node]){
        if(child==parent) continue;
        int leftMax = cNo==0?INT_MIN:prefixMax[cNo-1];
        int rightMax = cNo==suffixMax.size()-1?INT_MIN:suffixMax[cNo+1];
        int newPartialAns = val[node] + max(leftMax, max(rightMax, partialAns));
        calcAns(child, node, newPartialAns, adj, val, subTreeSum, ans);
        cNo++;
    }

    if(node==1){
        ans[node] = subTreeSum[node];
    }
    else{
        ans[node] = max(subTreeSum[node], val[node] + partialAns);
    }
}

void solve(int n, vector<int> adj[], vector<int> &val){
    vector<int> subTreeSum(n+1, 0);
    calcSubTreeSum(1, 0, adj, val, subTreeSum);
    vector<int> ans(n+1, 0);
    calcAns(1, 0, INT_MIN, adj, val, subTreeSum, ans);

    int valueAns = 0;
    for(int i=1; i<=n; i++){
        valueAns = max(valueAns, ans[i] - val[i]);
    }
    cout<<valueAns;
    
}


int main(){
    int t;
    // cin>>t;
    t = 1;

    while(t--){
        int n; cin>>n;
        vector<int> val(n+1, 0);
        for(int i=1; i<=n; i++) cin>>val[i];
        vector<int> adj[n+1];
        for(int i=1; i<n; i++){
            int u, v;
            cin>>u>>v;
            adj[u].push_back(v);
            adj[v].push_back(u);
        }
        solve(n, adj, val);
    }
}

/*


Sample Input

5
4 1 3 6 5
1 2
1 3
2 4
2 5


Sample Output
14

*/
