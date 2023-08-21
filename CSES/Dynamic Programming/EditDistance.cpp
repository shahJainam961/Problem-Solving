/*The edit distance between two strings is the minimum number of operations required to transform one string into the other.

The allowed operations are:
Add one character to the string.
Remove one character from the string.
Replace one character in the string.
For example, the edit distance between LOVE and MOVIE is 2, because you can first replace L with M, and then add I.

Your task is to calculate the edit distance between two strings.

Input

The first input line has a string that contains n
characters between A–Z.

The second input line has a string that contains m
characters between A–Z.

Output

Print one integer: the edit distance between the strings.

Constraints
1≤n, m≤5000

Example

Input:
LOVE
MOVIE

Output:
2*/

/*

	Approach: given s1 of length m and s2 of length n

	def: f(ind1, ind2) = min operations required such that s1[ind1..m]==s2[ind2..n]
	ans: f(0, 0)
	rec: f(ind1, ind2) = s1[ind1]==s2[ind2]?f(ind1+1, ind2+1):min(f(ind1, ind2+1), f(ind1+1, ind2), f(ind1+1, ind2+1))
	bas: f(m, ind2) = n - ind2
		 f(ind1, n) = m - ind1

*/


#include<bits/stdc++.h>
#define int long long
using namespace std;

int solve(string &s1, string &s2) {
	int m = s1.size();
	int n = s2.size();

	vector<vector<int>> dp(m + 1, vector<int>(n + 1 , 0));

	for (int ind1 = m; ind1 >= 0; ind1--) {
		for (int ind2 = n; ind2 >= 0; ind2--) {
			if (ind1 == m or ind2 == n) dp[ind1][ind2] = ind1 == m ? n - ind2 : m - ind1;
			else {
				if (s1[ind1] == s2[ind2])
					dp[ind1][ind2] = dp[ind1 + 1][ind2 + 1];
				else
					dp[ind1][ind2] = 1 + min(dp[ind1][ind2 + 1], min(dp[ind1 + 1][ind2], dp[ind1 + 1][ind2 + 1]));

			}
		}
	}
	return  dp[0][0];
}


signed main() {
#ifndef ONLINE_JUDGE
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
#endif

	string s1, s2;
	cin >> s1 >> s2;
	cout << solve(s1, s2);
	return 0;
}