#include <bits/stdc++.h>
using namespace std;

bool match(char a, char b) {
  return a == b || (a == 'a' && b == 'o') || (a == 't' && b == 'l')
    || (a == 'o' && b == 'a') || (b == 't' && a == 'l');
}

int edit_distance(string& draw, string& lot) {
  int n = draw.size();
  int m = lot.size();

  // dp[i][j][0] is the minimum edit distance to transform draw[0..i-1] to lot[0..j-1] using only deletion and substitution
  // dp[i][j][1] is the minimum edit distance to transform draw[0..i-1] to lot[0..j-1] using deletion, substitution, and insertion

  int dp[n + 1][m + 1][2];

  for (int i = 0; i <= n; i++) {
    dp[i][m][0] = dp[i][m][1] = 0;
  }

  for (int i = 0; i < m; i++) {
    dp[n][i][0] = dp[n][i][1] = 1e9;
  }

  dp[n][m - 1][0] = 0;

  for (int i = n - 1; i >= 0; i--) {
    for (int j = m - 1; j >= 0; j--) {
      dp[i][j][0] = dp[i][j + 1][1];
      dp[i][j][1] = 1e9;

      dp[i][j][1] = min(dp[i][j][1], dp[i + 1][j][1] + (int)(j > 0));
      dp[i][j][0] = min(dp[i][j][0], dp[i + 1][j][0] + (int)(j > 0));

      if (match(draw[i], lot[j])) {
        dp[i][j][0] = min(dp[i][j][0], dp[i + 1][j + 1][0]);
        dp[i][j][1] = min(dp[i][j][1], dp[i + 1][j + 1][1]);
      }
    }
  }

  return dp[0][0][0];
}

int main() {
  int n, k;
  cin >> n;

  // lots is a vector of strings
  vector<string> lots(n);
  for (int i = 0; i < n; i++) {
    cin >> lots[i];
  }

  // draw is a string
  string draw;
  cin >> draw;

  // k is an integer
  cin >> k;

  int ans = 0;
  for (auto& lot : lots) {
    if (edit_distance(draw, lot) <= k) {
      ans++;
    }
  }

  cout << ans << endl;

  return 0;
}

