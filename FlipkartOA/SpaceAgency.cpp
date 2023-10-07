#include<bits/stdc++.h>
#define int long long
using namespace std;


class Solution {

    void dfs(int i, int j, int n, vector<vector<int>> &grid, set<pair<int, int>> &st, vector<vector<int>> &vis){
        vis[i][j] = 2;
        int dr[] = {1, 0, -1, 0};
        int dc[] = {0, -1, 0, 1};
        st.insert({i, j});
        for(int k=0; k<4; k++){
            int ni = i + dr[k];
            int nj = j + dc[k];
            if(ni>=0 and nj>=0 and nj<n and ni<n and !vis[ni][nj] and grid[ni][nj]==1){
                dfs(ni, nj, n, grid, st, vis);
            }
        }
    }

    void dfs1(int i, int j, int n, vector<vector<int>> &grid, queue<pair<int, int>> &q, vector<vector<int>> &vis){
        vis[i][j] = 1;
        int dr[] = {1, 0, -1, 0};
        int dc[] = {0, -1, 0, 1};
        q.push({i, j});
        for(int k=0; k<4; k++){
            int ni = i + dr[k];
            int nj = j + dc[k];
            if(ni>=0 and nj>=0 and nj<n and ni<n and !vis[ni][nj] and grid[ni][nj]==1){
                dfs1(ni, nj, n, grid, q, vis);
            }
        }
    }

public:
    int shortestBridge(vector<vector<int>>& grid) {
        int n = grid.size();
        vector<vector<int>> vis(n, vector<int>(n, 0));
        set<pair<int, int>> st;
        queue<pair<int, int>> q;
        int cnt = 0;

        for(int i=0; i<n; i++){
            for(int j=0; j<n; j++){
                if(cnt==1 and !vis[i][j] and grid[i][j]==1){
                        dfs1(i, j, n, grid, q, vis);
                        break;
                }
                else if(!vis[i][j] and grid[i][j]==1){
                    dfs(i, j, n, grid, st, vis);
                    cnt++;
                }
            }
        }
        int ans = 0;
        int dr[] = {1, 0, -1, 0};
        int dc[] = {0, -1, 0, 1};
        while(true){
            int size = q.size();
            for(int i=0; i<size; i++){
                int x = q.front().first;
                int y = q.front().second;
                q.pop();
                if(st.find({x, y})!=st.end()) return ans-1;
                for(int k=0; k<4; k++){
                    int nx = x + dr[k];
                    int ny = y + dc[k];

                    if(nx<n and nx>=0 and ny<n and ny>=0 and vis[nx][ny]!=1){
                        q.push({nx, ny});
                        vis[nx][ny] = 1;
                    }
                }
            }
            ans++;
        }
        return ans;
    }
};

signed main(){

    return 0;
}
