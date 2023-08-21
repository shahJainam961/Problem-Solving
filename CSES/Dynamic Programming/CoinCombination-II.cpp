/*

Consider a money system consisting of n
 coins. Each coin has a positive integer value. Your task is to calculate the number of distinct ordered ways you can produce a money sum x
 using the available coins.

For example, if the coins are {2,3,5}
 and the desired sum is 9
, there are 3
 ways:
2+2+5

3+3+3

2+2+2+3

Input

The first input line has two integers n
 and x
: the number of coins and the desired sum of money.

The second line has n
 distinct integers c1,c2,…,cn
: the value of each coin.

Output

Print one integer: the number of ways modulo 109+7
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
3

*/
/*

	Approach:

	def : f(ind, target) = no. of distinct ways to reach target with coins from ind to n
	ans : f(0, x)
	rec : f(ind, target) = f(ind, target-coinVal[ind]) + f(ind+1, target)
	bas : f(n-1, target) = coinVal[n-1]%target==0

*/

#include<bits/stdc++.h>
#define ll long long
using namespace std;

int mod = 1e9 + 7;

int f(int ind, int target, vector<int> &coinVal, vector<vector<int>> &dp) {
	int n = coinVal.size();
	if (ind == n - 1) return (target % coinVal[n - 1]) == 0;
	if (dp[ind][target] != -1) return dp[ind][target];
	int ans = 0;

	if (target >= coinVal[ind])
		ans = (ans + f(ind, target - coinVal[ind], coinVal, dp)) % mod;

	ans = (ans + f(ind + 1, target, coinVal, dp)) % mod;

	return dp[ind][target] = ans;
}

int solve(int n, int x, vector<int> &coinVal) {
	// vector<vector<int>> dp(n + 1, vector<int>(x + 1, 0));
	vector<int> cur(x + 1, 0);

	for (int ind = n - 1; ind >= 0; ind--) {
		for (int target = 0; target <= x; target++) {
			if (ind == n - 1) cur[target] = (target % coinVal[n - 1]) == 0;

			else {
				int ans = 0;

				if (target >= coinVal[ind])
					ans = (ans + cur[target - coinVal[ind]]) % mod;

				ans = (ans + cur[target]) % mod;

				cur[target] = ans;
			}
		}
	}

	return cur[x];
}


int main() {

#ifndef ONLINE_JUDGE
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
#endif

	int n, x;
	cin >> n >> x;

	vector<int> coinVal;
	for (int i = 1; i <= n; i++) {
		int val;
		cin >> val;
		coinVal.push_back(val);
	}
	cout << solve(n, x, coinVal);
	return 0;
}