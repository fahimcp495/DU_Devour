// Divide an array into n parts.
// Cost of each division is subarray sum
// Minimize the  cost

ll dp[n][n], opt[n][n];

for (int i = 0; i < n; ++i) {
  for (int j = 0; j < n; ++j) {
    dp[i][j] = LLONG_MAX;
  }
  opt[i][i] = i;
  dp[i][i] = 0;
}

for (int i = n - 2; i >= 0; --i) {
  for (int j = i + 1; j < n; ++j) {
    for (int k = opt[i][j - 1]; k <= min(j - 1ll, opt[i + 1][j]); ++k) {
      if (dp[i][j] >= dp[i][k] + dp[k + 1][j] + (pref[j + 1] - pref[i])) {
        dp[i][j] = dp[i][k] + dp[k + 1][j] + (pref[j + 1] - pref[i]);
        opt[i][j] = k;
      }
    }
  }
}

cout << dp[0][n - 1] << "\n";