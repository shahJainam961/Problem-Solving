// baaki
#include<bits/stdc++.h>
using namespace std;

int main() {

#ifndef ONLINE_JUDGE
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
#endif

	int n;
	cin >> n;
	int k;
	cin >> k;
	vector<int> vq(n);
	for (int i = 0; i < n; i++) {
		cin >> vq[i];
	}
	cout << solve(vq, n, k);
	return 0;
}
