// #include<bits/stdc++.h>
// using namespace std;

// class DisjointSet{
//     private:
//         vector<int> parent, size;

//     public:
//         DisjointSet(int n){
//             size.resize(n+1, 1);
//             parent.resize(n+1);
//             for(int i=0; i<n; i++) parent[i] = i;
//         }

//         int findUParent(int node){
//             if(node == parent[node]) return node;
//             return parent[node] = findUParent(parent[node]);
//         }

//         bool unionBySize(int u, int v){
//             int pu = findUParent(u);
//             int pv = findUParent(v);

//             if(pu==pv) return false;

//             if(size[pu]>=size[pv]){
//                 parent[pv] = pu;
//                 size[pu] += size[pv];
//             }
//             else{
//                 parent[pu] = pv;
//                 size[pv] += size[pu];
//             }
//             return true;
//         }
// };

// class Solution{
//     private:
//         int mod = 1e9 + 7;

//         static bool cmp(vector<int> &a, vector<int> &b){
//             return a[2]<b[2];
//         }

//     public: 

//         int minCost(vector<vector<int>> &edges, int n){
//             sort(edges.begin(), edges.end(), cmp);
//             DisjointSet ds(n);
//             int minCost = 0;

//             for(vector<int> edge : edges){

//                 int u = edge[0];
//                 int v = edge[1];
//                 int cost = edge[2];

//                 if(ds.findUParent(u)==ds.findUParent(v)) continue;
//                 minCost = (minCost + cost)%mod;
//                 ds.unionBySize(u, v);

//             }

//             return minCost;
//         }

// };

// // there will be nodes from 0 to m*n - 1
// // num -> r = num/n and c = num%n  ------- (r, c) -> num = r*n + c
// int getCellNumber(int r, int c, int m, int n){
//     return r*n + c;
// }

// int main(){

//     int m, n;
//     cin>>m>>n;

//     vector<int> a(m-1);
//     vector<int> b(n-1);
//     vector<vector<int>> edges;
//     for(int i=0; i<m-1; i++) cin>>a[i];
//     for(int j=0; j<n-1; j++) cin>>b[j];

    

//     for(int i=0; i<m; i++){
//         for(int j=0; j<n; j++){
//             int curNode = getCellNumber(i, j, m, n);
//             if(j+1<n){
//                 int rightNode = getCellNumber(i, j+1, m, n);
//                 int cost = b[j];
//                 edges.push_back({curNode, rightNode, cost});
//             }
//             if(i+1<m){
//                 int downNode = getCellNumber(i+1, j, m, n);
//                 int cost = a[i];
//                 edges.push_back({curNode, downNode, cost});
//             }
//         }
//     }

//     Solution s;
//     cout<<s.minCost(edges, n*m-1);
//     return 0;
// }


// //----------------///


#include <bits/stdc++.h>
  using namespace std;

  int main() {
    int n,m;
    cin>>n>>m;
    vector<pair<int,int>> arr;
    for(int i=0;i<n-1;i++){
      int v;
      cin>>v;
      arr.push_back({v,0});
    }
    for(int i=0;i<m-1;i++){
      int v;
      cin>>v;
      arr.push_back({v,1});
    }
    sort(arr.begin(),arr.end());
    int cnt0=0,cnt1=0;
    long long ans=0;
    int mod=1e9+7;
    for(int i=0;i<arr.size();i++){
      if(arr[i].second==0){
        ans=(ans+1LL*(m-cnt1)*arr[i].first)%mod;
        cnt0++;
      }
      else{
        ans=(ans+1LL*(n-cnt0)*arr[i].first)%mod;
        cnt1++;
      }
    }
    cout<<ans<<endl;
  }
/*
    1  1  2
  1 0  1  2  3
  1 4  5  6  7
  1 8  9 10  11
   12 13 14  15

   1,0 r  -->> 4
   1,0 r  -->> 4
   1,0 r  -->> 4

   1,1 c
   1,1 c
   2,1 c

   cnt0 = 3;
   cnt1 = 0;

*/
