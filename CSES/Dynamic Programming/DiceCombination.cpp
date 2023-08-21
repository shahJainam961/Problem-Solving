/*Time limit: 1.00 s Memory limit: 512 MB
Your task is to count the number of ways to construct sum n
 by throwing a dice one or more times. Each throw produces an outcome between 1
 and 6
.

For example, if n=3
, there are 4
 ways:
1+1+1

1+2

2+1

3

Input

The only input line has an integer n
.

Output

Print the number of ways modulo 109+7
.

Constraints
1≤n≤106

Example

Input:
3

Output:
4*/


/*

	Approach:
		def : f(i) = number of ways to construct sum i by throwing a dice one or more times.
		ans : f(n)
		rec : f(i) = sum of all k=1->6 (f(i-k));
		bas : f(0) = f(1) = 1;
*/

#include<bits/stdc++.h>
#define ll long long
using namespace std;

int mod = 1e9 + 7;

ll getNumberOfCombination(ll n, vector<int> &dp) {
	if (n == 0 or n == 1) return 1;
	if (dp[n] != -1) return dp[n];
	ll ans = 0;
	for (int k = 1; k <= 6; k++) {
		if (n - k >= 0) ans = (ans + getNumberOfCombination(n - k, dp)) % mod;
		else break;
	}
	return dp[n] = ans % mod;
}

int main() {
#ifndef ONLINE_JUDGE
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
#endif

	ll num;
	cin >> num;
	vector<int> dp(num + 1, 0);
	
	for(int n=0; n<=num; n++){
		if (n == 0 or n == 1) dp[n] = 1;
		else{
			ll ans = 0;
			for (int k = 1; k <= 6; k++) {
				if (n - k >= 0) ans = (ans + dp[n-k]) % mod;
				else break;
			}
			dp[n] = ans % mod;
		}
	}
	
	cout << dp[num];

	return 0;
}
