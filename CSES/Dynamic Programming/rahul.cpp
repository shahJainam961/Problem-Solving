#include<bits/stdc++.h>
using namespace std;


#include <iostream>
#include <vector>
#include <algorithm>

int maxReward(int k, std::vector<int> reward1, std::vector<int> reward2) {
	int n = reward1.size();
	if (n == 0) {
		return 0;
	}
	if (k == 0) {
		int totalReward = 0;
		for (int r : reward2) {
			totalReward += r;
		}
		return totalReward;
	}

	std::vector<int> arr_diff(n);
	for (int i = 0; i < n; ++i) {
		arr_diff[i] = reward1[i] - reward2[i];
	}

	std::vector<int> arr_index(n);
	for (int i = 0; i < n; ++i) {
		arr_index[i] = i;
	}

	std::sort(arr_index.begin(), arr_index.end(),
	[&arr_diff](int a, int b) {
		return arr_diff[a] < arr_diff[b];
	});

	int sum = 0;
	for (int i = 0; i < n; ++i) {
		if (i < n - k) {
			sum += reward2[arr_index[i]];
		} else {
			sum += reward1[arr_index[i]];
		}
	}

	return sum;
}

int main() {
	// Example usage
	int k = 2;
	std::vector<int> reward1 = {5, 4, 3, 2, 1};
	std::vector<int> reward2 = {1, 2, 3, 4, 5};

	int result = maxReward(k, reward1, reward2);
	std::cout << "Maximum Reward: " << result << std::endl;

	return 0;
}


// int main() {

// #ifndef ONLINE_JUDGE
// 	freopen("input.txt", "r", stdin);
// 	freopen("output.txt", "w", stdout);
// #endif

// 	return 0;

// }

sum++;

sum = (sum + 1) % mod;

(((dp[0] * (src == target)) % mod) + ((dp[1]*sum) % mod)) % mod