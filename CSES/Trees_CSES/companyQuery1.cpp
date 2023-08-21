/*

A company has n
 employees, who form a tree hierarchy where each employee has a boss, except for the general director.

Your task is to process q
 queries of the form: who is employee x
's boss k
 levels higher up in the hierarchy?

Input

The first input line has two integers n
 and q
: the number of employees and queries. The employees are numbered 1,2,…,n
, and employee 1
 is the general director.

The next line has n−1
 integers e2,e3,…,en
: for each employee 2,3,…,n
 their boss.

Finally, there are q
 lines describing the queries. Each line has two integers x
 and k
: who is employee x
's boss k
 levels higher up?

Output

Print the answer for each query. If such a boss does not exist, print −1
.

Constraints
1≤n,q≤2⋅105

1≤ei≤i−1

1≤x≤n

1≤k≤n

Example

Input:
5 3
1 1 3 3
4 1
4 2
4 3

Output:
3
1
-1


*/


#include<bits/stdc++.h>
using namespace std;

int up[200001][20];
vector<int> adj[200001];

void binaryLifting(int node, int parent) {
	up[node][0] = parent;
	for (int i = 1; i < 20; i++) {
		if (up[node][i - 1] != -1)
			up[node][i] = up[up[node][i - 1]][i - 1];
		else up[node][i] = -1;
	}

	for (int child : adj[node]) {
		if (child != parent)
			binaryLifting(child, node);
	}
}

int getAns(int node, int jumps) {
	if (node == -1 || jumps == 0)  return node;
	for (int i = 31; i >= 0; i--) {
		if ((jumps & (1 << i)) != 0) {
			return getAns(up[node][i], jumps ^ (1 << i));
		}
	}
	return -1;
}

int main() {
	int n;
	int q;
	cin >> n >> q;

	int ele;
	for (int i = 2; i <= n; i++) {
		cin >> ele;
		adj[i].push_back(ele);
		adj[ele].push_back(i);
	}
	binaryLifting(1, -1);
	for (int i = 0; i < q; i++) {
		int node;
		int jumps;
		cin >> node >> jumps;
		cout << getAns(node, jumps) << endl;
	}
	return 0;
}