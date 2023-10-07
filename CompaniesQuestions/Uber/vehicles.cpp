#include<bits/stdc++.h>


using namespace std;

pair<int, int> f(int ind, int remainingP, vector<int> &seats) {
	if (remainingP == 0) return {0, 0};
	if (ind == seats.size()) return {1e9, 1e9};
	else if (seats[ind] >= remainingP) return {1, seats[ind] - remainingP};

	pair<int, int> p1 = f(ind + 1, remainingP, seats);
	pair<int, int> p2 = f(ind, remainingP - seats[ind], seats);

	p2.first++;

	if (p1.second == p2.second) return p1.first < p2.first ? p1 : p2;
	return p1.second < p2.second ? p1 : p2;
}

int solve(vector<int> &seats, int n, int p) {
	pair<int, int> p1 = f(0, p, seats);
	return p1.first;
}

int main() {

#ifndef ONLINE_JUDGE
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
#endif

	int n;
	cin >> n;
	int p;
	cin >> p;

	vector<int> seats(n);
	for (int i = 0; i < n; i++) {
		cin >> seats[i];
	}
	sort(seats.begin(), seats.end());
	cout << solve(seats, n, p);
	return 0;
}
