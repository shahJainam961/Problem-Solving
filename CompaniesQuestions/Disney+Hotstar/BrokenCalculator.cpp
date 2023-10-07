/*Given a broken calculator, and a number. Have to tell minimum number of buttons you have to press to print the given number on the screen.

In the broken calculator,only multiply(*) and equal(=) operation and some digits are working.
Given:
N: Number you have to print on the screen. N<=1e6
Array[10]: [0, 1, 0, 1....0.], An 10 length array representing, the digit on the calculator is working or not for [0, 9]. 1 means working and 0 means not working.

Output: Minimum number of buttons you have to press to print the number or print Impossible if not possible.

Example1:

N = 12
ar = [0, 1, 1, 0, 0, 1, 0, 0, 0, 0]
So only 1, 2, 5 digits are working in the calculator. We can type 12 using the buttons so ans will be 2.

Example2:

N = 60
ar = [0, 1, 1, 0, 0, 1, 0, 0, 0, 0]
So only 1, 2, 5 digits are working in the calculator.

2*2*15=60 : 7 press
12*5=60: 5 press
so ans will be 5.
*/


#include<bits/stdc++.h>
#define int long long
using namespace std;

int getMinMoves(string curNumber, string n, vector<int> &validDigits, int up) {
	if (curNumber == n) return 1;
	int ans = INT_MAX;
	string newNumber = "";
	for (int i = 1; i < (1 << up); i++) {
		int cnts = __builtin_popcount(i);
		if (cnts <= up) {
			// for newNumber
			ans = max(ans, cnts + f())
		}
	}

}

int solve(vector<int> &active, int n) {
	string curNumber = "";
	string str = to_string(n);
	vector<int> validDigits;
	for (int i = 0; i < 10; i++) if (active[i]) validDigits.push_back(i);
	return getMinMoves(curNumber, str, validDigits, str.size());
}


signed main() {

#ifndef ONLINE_JUDGE
	freopen("/home/murphy/Desktop/input.txt", "r", stdin);
	freopen("/home/murphy/Desktop/output.txt", "w", stdout);
#endif

	vector<int> active(10);
	for (int &bin : active) cin >> bin;
	int n;
	cin >> n;
	cout << solve(active, n);
}


/*

def : downpath(node) : simple path niche ketlo max
	rec: downpath(node) : max(downpath(childi)) + val[node]
	base: downpath(node) = val[node] ; node=leaf node



	def : f(node, 0) = max answer for the subtree rooted at node when node is not in path
		  f(node, 1) = max answer for the subtree rooted at node when node is in path

	ans : max(f(root, 0), f(root, 1))

	rec : f(node, 0) = max(f(childi, 1)) ; i=>1to k
		  f(node, 1) = val[node] + downpath(child1) + downpath(child2)

	base: f(leaf, 0) = 0;
		  f(leaf, 1) = val[leaf]
*/

void calcDownpaths(int node, int parent, vector<int> &downpaths, vector<int> &val) {
	downpaths[node] += val[node];

	for (int child : adj[node]) {
		if (child == parent) continue;
		calcDownpaths(child, node, downpaths, val);
	}
	int maxi = 0;
	for (int child : adj[node]) {
		maxi = max(maxi, downpaths[child]);
	}
	downpaths[node] += maxi;
	return;
}

int dp[100001][2];

/**
 * def : f(node, 0) = max answer for the subtree rooted at node when node is not in path
		  f(node, 1) = max answer for the subtree rooted at node when node is in path

	ans : max(f(root, 0), f(root, 1))

	rec : f(node, 0) = max(f(childi, 1)) ; i=>1to k
		  f(node, 1) = val[node] + downpath(child1) + downpath(child2)

	base: f(leaf, 0) = 0;
		  f(leaf, 1) = val[leaf]
 * */


void f(int node, int parent, vector<int> &downpaths, vector<int> adj[], vector<int> &val) {

	bool isLeaf = true;
	for (int child : adj[node]) {
		if (child == parent) continue;
		f(child, node, downpaths, adj, val);
		isLeaf = false;
	}

	if (isLeaf) {
		dp[node][0] = 0;
		dp[node][1] = val[node];
		return;
	}

	for (int child : adj[node]) {
		if (child == parent) continue;
		dp[node][0] = max(dp[node][0], dp[child][1]);
	}
	vector<int> childSum;
	for (int child : adj[node]) {
		if (child == parent) continue;
		childSum.push_back(downpaths[child]);
	} sort(childSum.v.begin(), v.end())

	dp[node][1] += val[node];
	if (childSum.size() > 0) dp[node][1] += childSum[0];
	if (childSum.size() > 1) dp[node][1] += childSum[1];
}

void solve(int n, vector<int> adj[], vector<int> &val) {

	// downpaths
	vector<int> downpaths(n);
	calcDownpaths(1, 0, downpaths, adj, val);
	f(1, 0)
	return max(dp[1][0], dp[1][1]);

}

// n-ary -->