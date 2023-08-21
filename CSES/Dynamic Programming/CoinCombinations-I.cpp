/*

Consider a money system consisting of n
coins. Each coin has a positive integer value. Your task is to calculate the number of distinct ways you can produce a money sum x
using the available coins.

For example, if the coins are {2, 3, 5}
and the desired sum is 9
, there are 8
ways:
2 + 2 + 5

2 + 5 + 2

5 + 2 + 2

3 + 3 + 3

2 + 2 + 2 + 3

2 + 2 + 3 + 2

2 + 3 + 2 + 2

3 + 2 + 2 + 2

Input

The first input line has two integers n
and x
: the number of coins and the desired sum of money.

The second line has n
distinct integers c1, c2, …, cn
: the value of each coin.

Output

Print one integer: the number of ways modulo 109 + 7
.

Constraints
1≤n≤100

1≤x≤106

1≤ci≤106

Example

Input:
3 9
2 3 5

Output:
8

*/
/*

	Approach:

	def : f(target) = no. of ways to achieve sum as target
	ans : f(x)
	rec : f(target) = for all indexes i sum(f(target-coinVal[i]));
	bas : f(0) = 1;

*/

#include<bits/stdc++.h>
using namespace std;


// int f(int target, vector<int> &coinVal, int n, vector<int> &dp) {

// 	if (target == 0) return 1;
// 	if (dp[target] != -1) return dp[target];
// 	int ways = 0;

// 	for (int i = 0; i < (int)coinVal.size(); i++) {
// 		if (coinVal[i] <= target) {
// 			ways = (ways + f(target - coinVal[i], coinVal, n, dp)) % mod;
// 		}
// 	}
// 	return dp[target] = ways;
// }

// void solve(int n, int x, vector<int> &coinVal) {

// 	vector<int> dp(x + 1, 0);
// 	for (int target = 0; target <= x; target++) {
// 		if (target == 0) dp[target] = 1;
// 		else {
// 			int ways = 0;
// 			for (int i = 0; i < (int)coinVal.size(); i++) {
// 				if (coinVal[i] <= target) {
// 					ways = (ways + dp[target - coinVal[i]]) % mod;
// 				}
// 			}
// 			dp[target] = ways;
// 		}
// 	}

// 	cout << dp[x];
// }



int main() {

#ifndef ONLINE_JUDGE
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
#endif
	int mod = 1e9 + 7;
	int n, x;
	cin >> n >> x;

	vector<int> coinVal(n);
	for (int &v : coinVal)
		cin >> v;
	// solve(n, x, coinVal);
	vector<int> dp(x + 1, 0);
	dp[0] = 1;
	for (int target = 1; target <= x; target++) {
		int ways = 0;
		for (int i = 0; i < n; i++) {
			if (coinVal[i] <= target) {
				ways = (ways + dp[target - coinVal[i]]) % mod;
			}
		}
		dp[target] = ways;
	}

	cout << dp[x];
	return 0;
}