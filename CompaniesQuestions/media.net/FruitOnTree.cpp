

#include <bits/stdc++.h>
using namespace std;


// typedef long long int ll;
#define int long long int

int N=1e5+10;
vector<vector<int>>g(N);
vector<int>vis(N);
vector<int>depth(N);
vector<int>ans(N);


void dfs(int v,vector<int>&init,vector<int>&capacity){
    vis[v]=1;
    int mx=0;
    int isLeaf=1;
    int sum=0;

    for(auto ch:g[v]){
        if(!vis[ch]){
            isLeaf=0;
            dfs(ch,init,capacity);
            depth[v]=max(depth[v],depth[ch]+1);
            mx=max(mx,ans[ch]);
            sum+=(ans[ch]-depth[ch]);
            
        }
    }
    if(isLeaf){
        // depth[v]=1;
        ans[v]=init[v];
    }else{
        ans[v]=mx+ min(capacity[v],sum-(mx-depth[v]));
    }
}
void solve()
{
    int n;
    cin>>n;
    vector<int>init(n);
    vector<int>capacity(n);
    
    for(int i=0;i<n;++i)cin>>init[i];
    for(int i=0;i<n;++i)cin>>capacity[i];

    for(int i=0;i<n-1;++i){
        int a,b;
        cin>>a>>b;
        --a,--b;
        g[a].push_back(b);
        g[b].push_back(a);
    }

    dfs(0,init,capacity);
    cout<<ans[0]<<'\n';

}
int32_t main()
{
    solve();

    return 0;
}