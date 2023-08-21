#include <iostream>
#include <vector>
 
using namespace std;
 
const int MAX_N = 300005;
 
int bridgec;
vector<int> adj [MAX_N];
int lvl [MAX_N];
int dp [MAX_N];
 
void visit (int vertex) {
  dp[vertex] = 0;
  for (int nxt : adj[vertex]) {
    if (lvl[nxt] == 0) { /* edge to child */
      lvl[nxt] = lvl[vertex] + 1;
      visit(nxt);
      dp[vertex] += dp[nxt];
    } else if (lvl[nxt] < lvl[vertex]) { /* edge upwards */
      dp[vertex]++;
    } else if (lvl[nxt] > lvl[vertex]) { /* edge downwards */
      dp[vertex]--;
    }
  }
 
  /* the parent edge isn't a back-edge, subtract 1 to compensate */
  dp[vertex]--;
 
  if (lvl[vertex] > 1 && dp[vertex] == 0) {
    bridgec++;
  }
}
 
int main () {
  /* problem statement: given a connected graph. calculate the number of bridges. */
  ios::sync_with_stdio(false);
 
  int vertexc, edgec;
  cin >> vertexc >> edgec;
 
  for (int i = 0; i < edgec; i++) {
    int u, v;
    cin >> u >> v;
 
    adj[u].push_back(v);
    adj[v].push_back(u);
  }
 
  lvl[1] = 1;
  visit(1);
 
  cout << bridgec << endl;
}