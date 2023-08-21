// You are in a book shop which sells n
//  different books. You know the price and number of pages of each book.

// You have decided that the total price of your purchases will be at most x
// . What is the maximum number of pages you can buy? You can buy each book at most once.

// Input

// The first input line contains two integers n
//  and x
// : the number of books and the maximum total price.

// The next line contains n
//  integers h1,h2,…,hn
// : the price of each book.

// The last line contains n
//  integers s1,s2,…,sn
// : the number of pages of each book.

// Output

// Print one integer: the maximum number of pages.

// Constraints
// 1≤n≤1000

// 1≤x≤105

// 1≤hi,si≤1000

// Example

// Input:
// 4 10
// 4 8 5 3
// 5 12 8 1

// Output:
// 13

// Explanation: You can buy books 1 and 3. Their price is 4+5=9
//  and the number of pages is 5+8=13
// .


/*

	Approach:

		priceOfBook Array
		pagesOfBook Array
		n books are there (0 -> n-1)

		def : f(ind, cost) = total pages u can get from books avilable from 0 to ind and having cost money
		ans : f(n-1, x)
		rec : f(ind, cost) = max(f(ind-1, cost), pages[ind] + f(ind-1, cost-price[ind]));
		bas : f(0, cost) = price[0]<=cost?pages[0]:0


*/
#include<bits/stdc++.h>
#define ll long long
using namespace std;

int f(int ind, int cost, vector<int> &price, vector<int> &pages) {
	if (ind == 0) return price[0] <= cost ? pages[0] : 0;

	int ans = 0;
	ans = max(ans, f(ind - 1, cost, price, pages));
	if (cost >= price[ind]) ans = max(ans, pages[ind] + f(ind - 1, cost - price[ind], price, pages));
	return ans;
}

int solve(int n, int x, vector<int> &price, vector<int> &pages) {
	vector<int> prev(x + 1, 0), cur(x + 1, 0);

	for (int ind = 0; ind < n; ind++) {
		for (int cost = 0; cost <= x; cost++) {
			if (ind == 0) cur[cost] = price[0] <= cost ? pages[0] : 0;
			else {
				int ans = 0;
				ans = max(ans, prev[cost]);
				if (cost >= price[ind]) ans = max(ans, pages[ind] + prev[cost - price[ind]]);
				cur[cost] = ans;
			}
		}
		prev = cur;
	}

	return prev[x];
}

int main() {
#ifndef ONLINE_JUDGE
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
#endif
	int n, x;
	cin >> n >> x;

	vector<int> price(n);
	vector<int> pages(n);

	for (int &num : price) cin >> num;
	for (int &num : pages) cin >> num;

	cout << solve(n, x, price, pages);
	return 0;
}