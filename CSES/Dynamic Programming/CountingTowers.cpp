/*Your task is to build a tower whose width is 2
 and height is n
. You have an unlimited supply of blocks whose width and height are integers.

For example, here are some possible solutions for n=6
:

Given n
, how many different towers can you build? Mirrored and rotated towers are counted separately if they look different.

Input

The first input line contains an integer t
: the number of tests.

After this, there are t
 lines, and each line contains an integer n
: the height of the tower.

Output

For each test, print the number of towers modulo 109+7
.

Constraints
1≤t≤100

1≤n≤106

Example

Input:
3
2
6
1337

Output:
8
2864
640403945*/


/*

Approach:

	if n==1 return 2

	for n>=2

	linked = 0 -> 2 blocks of width 1 ---- linked = 1 -> 1 block of width 2
	def : f(ind, linked) = total number of ways to build tower from ind to n, provide it is linked or not on ind-1
	ans : f(2, 0) + f(2, 1)
	rec : f(ind, 0) = 1. do not extend => f(ind+1, 0) + f(ind+1, 1)
					  2. extend both => f(ind+1, 0)
					  3. extend one of the two => 2*f(ind+1, 0)
		  f(ind, 1) = 1. do not extend => f(ind+1, 0) + f(ind+1, 1)
		  			  2. extend => f(ind+1, 1)

*/


#include<bits/stdc++.h>
#define int long long
using namespace std;
vector<vector<int>> dp;
// int f(int ind, int linked, int n, vector<vector<int>> &dp) {
// 	int mod = 1e9 + 7;
// 	if (ind == n + 1) return 1;
// 	if (dp[ind][linked] != -1) return dp[ind][linked];
// 	if (!linked)
// 		return dp[ind][linked] = (4 * f(ind + 1, 0, n, dp) + f(ind + 1, 1, n, dp)) % mod;
// 	else
// 		return dp[ind][linked] = (f(ind + 1, 0, n, dp) + 2 * f(ind + 1, 1, n, dp)) % mod;
// }

int solve(int n) {
	if (n == 1) return 2;
	int mod = 1e9 + 7;
	for (int ind = n + 1; ind >= 2; ind--) {
		if (ind == n + 1) dp[ind][0] = dp[ind][1] = 1;
		else {
			dp[ind][0] = (4 * dp[ind + 1][0] + dp[ind + 1][1]) % mod;
			dp[ind][1] = (dp[ind + 1][0] + 2 * dp[ind + 1][1]) % mod;
		}
	}


	return (dp[2][0] + dp[2][1]) % mod;
}

signed main() {
#ifndef ONLINE_JUDGE
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
#endif
	int t;
	cin >> t;
	dp.resize(1000002, vector<int>(2, 0));
	while (t--) {
		int n;
		cin >> n;
		cout << solve(n);
		if (t != 0) cout << endl;
	}
	return 0;
}
