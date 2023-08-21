#include<bits/stdc++.h>
using namespace std;

class DisjointSet{
    private:
        vector<int> parent, rank, size;
    public:
        DisjointSet(int n){
            rank.resize(n+1, 0);
            parent.resize(n+1);
            for(int i=0; i<=n; i++){
                parent[i] = i;
            }
            size.resize(n+1, 1);
        }

        int findUParent(int node){
            if(node == parent[node])
                return node;
            return parent[node] = findUParent(parent[node]);
        }

        void unionByRank(int u, int v){
            int pu = findUParent(u);
            int pv = findUParent(v);

            if(pu == pv) return;
            if(rank[pu] > rank[pv])
                parent[pv] = pu;
            else if(rank[pv] > rank[pu])
                parent[pu] = pv;
            else{
                parent[pv] = pu;
                rank[pu]++;
            }
        }

        void unionBySize(int u, int v){
            int pu = findUParent(u);
            int pv = findUParent(v);

            if(pu == pv) return;
            if(size[pu] > size[pv]){
                parent[pv] = pu;
                size[pu] += size[pv];
            }
            else{
                parent[pu] = pv;
                size[pv] += size[pu];
            }
        }
};

int main(){
    // #ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    // #endif

    DisjointSet ds(7);
    ds.unionBySize(1, 2);
    ds.unionBySize(2, 3);
    ds.unionBySize(4, 5);
    ds.unionBySize(6, 7);
    ds.unionBySize(5, 6);

    if(ds.findUParent(1) == ds.findUParent(5))
        cout<<"Same\n";
    else cout<<"Not Same\n";

    ds.unionBySize(3, 4);

    if(ds.findUParent(3) == ds.findUParent(7))
        cout<<"Same\n";
    else cout<<"Not Same\n";
    return 0;
}