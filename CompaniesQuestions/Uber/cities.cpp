#include<bits/stdc++.h>
using namespace std;




int solve(vector<int> &arr, int n) {
	int mini = arr[0];
	for (int num : arr) mini = min(mini, num); s

	f(0, arr, mini);
}

int main() {

#ifndef ONLINE_JUDGE
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
#endif

	int n;
	cin >> n;

	vector<int> arr(n);
	for (int i = 0; i < n; i++) {
		cin >> arr[i];
	}
	cout << solve(arr, n);
	return 0;
}
