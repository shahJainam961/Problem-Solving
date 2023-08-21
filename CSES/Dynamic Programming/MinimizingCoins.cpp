/*Consider a money system consisting of n
 coins. Each coin has a positive integer value. Your task is to produce a sum of money x
 using the available coins in such a way that the number of coins is minimal.

For example, if the coins are {1,5,7}
 and the desired sum is 11
, an optimal solution is 5+5+1
 which requires 3
 coins.

Input

The first input line has two integers n
 and x
: the number of coins and the desired sum of money.

The second line has n
 distinct integers c1,c2,…,cn
: the value of each coin.

Output

Print one integer: the minimum number of coins. If it is not possible to produce the desired sum, print −1
.

Constraints
1≤n≤100

1≤x≤106

1≤ci≤106

Example

Input:
3 11
1 5 7

Output:
3*/

#include<bits/stdc++.h>
#define ll long long

using namespace std;

// f(0, x, coinVal, dp)
// ind = 0 -> n-1,   target = x -> 0
// 
int f(int ind, int target, int n, vector<int> &coinVal, vector<vector<int>> &dp) {
	if (ind == n - 1) return ((target% coinVal[ind]) == 0) ? target / coinVal[ind] : 1e9;
	if (dp[ind][target] != -1) return dp[ind][target];
	int ans = 1e9;
	if (coinVal[ind] <= target) {
		ans = min(ans, 1 + f(ind, target - coinVal[ind], n, coinVal, dp));
	}
	ans = min(ans, f(ind + 1, target, n, coinVal, dp));
	return dp[ind][target] = ans;
}

void solve(int n, int x, vector<int> &coinVal) {
	vector<vector<int>> dp(n + 1, vector<int>(x + 1, 0));
	
	for(int ind=n-1; ind>=0; ind--){
		for(int target=0; target<=x; target++){
			if (ind == n - 1) dp[ind][target] = ((target% coinVal[ind]) == 0) ? target / coinVal[ind] : 1e9;
			else{
				int ans = 1e9;
				if (coinVal[ind] <= target) {
					ans = min(ans, 1 + dp[ind][target-coinVal[ind]]);
				}
				ans = min(ans, dp[ind+1][target]);
				dp[ind][target] = ans;
			}
		}
	}
	
	return dp[0][x];
}

int main() {

#ifndef ONLINE_JUDGE
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
#endif

	int n, x;
	cin >> n >> x; // 3 11
	vector<int> coinVal;
	for (int i = 1; i <= n; i++) {
		int val;
		cin >> val;
		coinVal.push_back(val);
	}
	solve(n, x, coinVal);
}
