#include<bits/stdc++.h>
using namespace std;


void solve(int n, int m, int k, int vi, int vj, vector<pair<int, int>> &friendsPos){

    set<pair<int, int>> st;
    int dr[] = {1, 0, -1, 0};
    int dc[] = {0, -1, 0, 1};

    for(int p=1; p<=4; p++){
        int nx = vi + dr[p-1];
        int ny = vj + dc[p-1];

        if(nx>=1 and ny>=1 and nx<=n and ny<=m) st.insert({nx, ny});
    }

    int count = st.size();

    for(int i=0; i<friendsPos.size(); i++){
        for(int p=1; p<=4; p++){
            int nx = friendsPos[i].first + dr[p-1];
            int ny = friendsPos[i].second + dc[p-1];

            if(nx>=1 and ny>=1 and nx<=n and ny<=m){
                if(st.find({nx, ny})!=st.end()){
                    st.erase({nx, ny});
                    count--;
                }
            }
        }
    }
    if(count==0) cout<<"NO";
    else cout<<"YES";
}

int main(){
    // #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    // #endif
    int t;
    cin>>t;

    while(t--){
        int n, m, k;
        cin>>n>>m>>k;
        int vi, vj;
        cin>>vi>>vj;
        vector<pair<int, int>> friendsPos;
        for(int i=1; i<=k; i++){
            int x, y; cin>>x>>y;
            friendsPos.push_back({x, y});
        }
        solve(n, m, k, vi, vj, friendsPos);
        cout<<endl;
    }
}