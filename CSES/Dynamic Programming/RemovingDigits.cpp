// You are given an integer n
// . On each step, you may subtract one of the digits from the number.

// How many steps are required to make the number equal to 0
// ?

// Input

// The only input line has an integer n
// .

// Output

// Print one integer : the minimum number of steps.

// Constraints
// 1≤n≤106

// Example

// Input :
// 27

// Output :
// 5

// Explanation : An optimal solution is 27→20→18→10→9→0
// .

/*



*/
#include<bits/stdc++.h>
#define ll long long
using namespace std;


int f(int n, vector<int> &dp) {

	if (n <= 9) return 1;
	if (dp[n] != -1) return dp[n];
	string str = to_string(n);
	vector<bool> vis(10, 0);
	for (char c : str) vis[c - '0'] = 1;

	int ans = INT_MAX;

	for (int dig = 1; dig <= 9; dig++) {
		if (vis[dig]) {
			ans = min(ans, 1 + f(n - dig, dp));
		}
	}
	return dp[n] = ans;
}

int solve(int num) {
	vector<int> dp(num + 1, 0);

	for (int n = 0; n <= num; n++) {
		if (n <= 9) dp[n] = 1;
		else {
			string str = to_string(n);
			vector<bool> vis(10, 0);
			for (char c : str) vis[c - '0'] = 1;

			int ans = INT_MAX;

			for (int dig = 1; dig <= 9; dig++) {
				if (vis[dig] and n - dig >= 0) {
					ans = min(ans, 1 + dp[n - dig]);
				}
			}
			dp[n] = ans;
		}
	}

	return dp[num];
}

int main() {

#ifndef ONLINE_JUDGE
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
#endif

	int n;
	cin >> n;

	cout << solve(n);

}