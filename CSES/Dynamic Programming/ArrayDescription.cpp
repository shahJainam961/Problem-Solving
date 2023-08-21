// You know that an array has n
// integers between 1
// and m
// , and the absolute difference between two adjacent values is at most 1
// .

// Given a description of the array where some values may be unknown, your task is to count the number of arrays that match the description.

// Input

// The first input line has two integers n
// and m
// : the array size and the upper bound for each value.

// The next line has n
// integers x1, x2, …, xn
// : the contents of the array. Value 0
// denotes an unknown value.

// Output

// Print one integer : the number of arrays modulo 109 + 7
// .

// Constraints
// 1≤n≤105

// 1≤m≤100

// 0≤xi≤m

// Example

// Input :
// 3 5
// 2 0 2

// Output :
// 3

// Explanation : The arrays [2, 1, 2]
// 	, [2, 2, 2]
// 	and [2, 3, 2]
// 	match the description.


/*

	Approach:

*/
#include<bits/stdc++.h>
#define ll long long
using namespace std;



// int f(int ind, int prev, int m, int n, vector<int> &arr, vector<vector<int>> &dp) {

// 	if (ind == n) return 1;
// 	if (dp[ind][prev] != -1) return dp[ind][prev];
// 	int ans = 0;
// 	int l = 1, r = m;
// 	if (arr[ind] != 0) {
// 		l = arr[ind];
// 		r = arr[ind];
// 	}
// 	for (int i = l; i <= r; i++) {
// 		if (!prev or abs(prev - i) <= 1) {
// 			ans = (ans + f(ind + 1, i, m, n, arr, dp)) % mod;
// 		}
// 	}
// 	return dp[ind][prev] = ans;
// }

int solve(int n, int m, vector<int> &arr) {
	int mod = 1e9 + 7;
	vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));

	for (int ind = n; ind >= 0; ind--) {
		for (int prev = m; prev >= 0; prev--) {
			if (ind == n) dp[ind][prev] = 1;
			else {
				int ans = 0;
				int l = 1, r = m;
				if (arr[ind] != 0) {
					l = arr[ind];
					r = arr[ind];
				}
				else if (prev) {
					l = max(1, prev - 1);
					r = min(m, prev + 1);
				}
				for (int i = l; i <= r; i++) {
					if (!prev or abs(prev - i) <= 1) {
						ans = (ans + dp[ind + 1][i]) % mod;
					}
				}
				dp[ind][prev] = ans;
			}
		}
	}
	return dp[0][0];
}

int main() {
#ifndef ONLINE_JUDGE
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
#endif
	int n, m;
	cin >> n >> m;

	vector<int> arr(n);
	for (int &num : arr) cin >> num;

	cout << solve(n, m, arr);
	return 0;
}