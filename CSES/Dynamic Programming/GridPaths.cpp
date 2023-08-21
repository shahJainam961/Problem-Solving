// Consider an n×n
//  grid whose squares may have traps. It is not allowed to move to a square with a trap.

// Your task is to calculate the number of paths from the upper-left square to the lower-right square. You can only move right or down.

// Input

// The first input line has an integer n
// : the size of the grid.

// After this, there are n
//  lines that describe the grid. Each line has n
//  characters: . denotes an empty cell, and * denotes a trap.

// Output

// Print the number of paths modulo 109+7
// .

// Constraints
// 1≤n≤1000

// Example

// Input:
// 4
// ....
// .*..
// ...*
// *...

// Output:
// 3

/*

Approach:
	def : f(i, j) from 0,0 to i,j
	ans : f(n-1, n-1)

*/

#include<bits/stdc++.h>
#define ll long long
using namespace std;

int mod = 1e9 + 7;

int f(int i, int j, vector<vector<int>> &grid, int n, vector<vector<int>> &dp) {
	if(i==0 and j==0) return 1;
	
	//			i-1, j
	//  i, j-1   i,j
	int ans = 0;
	if(j-1>=0 and grid[i][j-1]!=1){
		left = f();
	}
	if(){
		up = f();
	}
	return up + left
	
}

int solve(int n, vector<vector<int>> &grid) {
	//vector<vector<int>> dp(n + 1, vector<int>(n + 1, 0));
	
	
	if (grid[0][0] == 1 or grid[n - 1][n - 1] == 1) return 0;
	vector<int> cur(n+1, 0), prev(n+1, 0);

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (i == 0 and j == 0) cur[j] = 1;
			else {
				int ans = 0;
				if (j - 1 >= 0 and grid[i][j - 1] == 0) {
					ans = (ans + cur[j - 1]) % mod;
				}
				if (i - 1 >= 0 and grid[i - 1][j] == 0) {
					ans = (ans + prev[j]) % mod;
				}
				cur[j] = ans;
			}
		}
		prev = cur;
	}

	return prev[n - 1];
}


int main() {
#ifndef ONLINE_JUDGE
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
#endif
	int n;
	cin >> n;

	vector<vector<int>> grid(n, vector<int>(n));
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			char c;
			cin >> c;
			grid[i][j] = (c == '*') ? 1 : 0; // 1 is trap
		}
	}
	cout << solve(n, grid);
	return 0;
}
