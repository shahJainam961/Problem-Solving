/*Given an a×b
rectangle, your task is to cut it into squares. On each move you can select a rectangle and cut it into two rectangles in such a way that all side lengths remain integers. What is the minimum possible number of moves?

Input

The only input line has two integers a
and b
.

Output

Print one integer : the minimum number of moves.

Constraints
1≤a, b≤500

Example

Input :
3 5

Output :
3*/

#include<bits/stdc++.h>
#define int long long
using namespace std;

int solve(int a, int b) {

	vector<vector<int>> dp(a + 1, vector<int>(b + 1, 1e9));

	for (int l1 = 1; l1 <= a; l1++) {
		for (int l2 = 1; l2 <= b; l2++) {
			if (l1 == l2) dp[l1][l2] = 0;
			else if (l1 == 1 or l2 == 1) dp[l1][l2] = ((l1 == 1) ? (l2 - 1) : (l1 - 1));
			else {
				for (int i = 1; i < l1; i++) {
					dp[l1][l2] = min(dp[l1][l2], 1 + dp[i][l2] + dp[l1 - i][l2]);
				}

				for (int i = 1; i < l2; i++) {
					dp[l1][l2] = min(dp[l1][l2], 1 + dp[l1][i] + dp[l1][l2 - i]);
				}
			}
		}
	}

	return dp[a][b];
}

signed main() {
#ifndef ONLINE_JUDGE
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
#endif
	int a, b;
	cin >> a >> b;
	cout << solve(a, b);
	return 0;
}