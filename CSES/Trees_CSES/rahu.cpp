
#include<bits/stdc++.h>
using namespace std;

long long f(int num, unordered_map<int, int> &st) {
	long long ans = 0;
	unordered_set<int> qw;
	for (int i = 2; i <= sqrt(num); i++) {
		if (num % i == 0) {
			if (qw.find(i) == qw.end() and st.find(i) != st.end()) {
				ans += st[i];
				qw.insert(i);
			}
			if (qw.find(num / i) == qw.end() and st.find(num / i) != st.end()) {
				ans += st[num / i];
				qw.insert(num / i);
			}
		}
		else continue;
	}
	return ans += st[num];
}



vector<int> encryptionValidity(int iC, int vP, vector<int> keys) {
	sort(keys.begin(), keys.end());
	unordered_map<int, int> st;
	for (int num : keys) st[num]++;

	long long maxi = 0;


	for (int i = 0; i < keys.size(); i++) {
		int curNum = keys[i];
		maxi = max(maxi, f(curNum, st));
	}


	long long strength = maxi * 100000;


	long long second = iC * vP;

	vector<int> ans;

	if (strength <= second) ans.push_back(1);
	else ans.push_back(0);

	ans.push_back(strength);
	return ans;

}

int main() {

	vector<int> keys{2, 4, 8, 2};
	int iC = 1000;
	int vP = 10000;
	vector<int> it = encryptionValidity(iC, vP, keys);
	cout << it[0] << " " << it[1];

}