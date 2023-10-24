#include<bits/stdc++.h>
#define int long long
using namespace std;

bool isValid(int i, int j, int m, int n){
	return i>=0 and i<m and j>=0 and j<n;
}

void bfs(int i, int j, vector<vector<bool>> &vis, vector<vector<char>> &mat){
	int m = mat.size(); int n = mat[0].size();
	
	queue<vector<int>> q;
	q.push({i, j});
	vis[i][j] = true;
	
	int dr[] = {1, 0, -1, 0};
	int dc[] = {0, -1, 0, 1};
	
	while(!q.empty()){
		auto it = q.front(); q.pop();
		int r = it[0]; int c = it[1];
		for(int k=0; k<4; k++){
			int nr = r + dr[k];
			int nc = c + dc[k];
			if(isValid(nr, nc, m, n) and !vis[nr][nc] and mat[nr][nc]=='.'){
				q.push({nr, nc});
				vis[nr][nc] = true;
			}
		}
	}
	
}

signed main(){

	int m, n;
	cin>>m>>n;
	
	vector<vector<char>> mat(m, vector<char>(n));
	vector<vector<bool>> vis(m, vector<bool>(n, false));
	
	for(int i=0; i<m; i++){
		for(int j=0; j<n; j++){
			cin>>mat[i][j];
		}
	}
	int rooms = 0;
	
	for(int i=0; i<m; i++){
		for(int j=0; j<n; j++){
			if(!vis[i][j] and mat[i][j]=='.'){
				bfs(i, j, vis, mat);
				rooms++;
			}
		}
	}
	
	cout<<rooms;	

    return 0;
}
