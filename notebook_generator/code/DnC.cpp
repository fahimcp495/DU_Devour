- Divide an array into k parts
- Minimize the sum of squre of each subarray

ll pref[N], dp[N][N];
void compute(int l, int r, int j, int kl, int kr) {
  if (l > r)  return ;
  int m = (l + r) / 2;
  array<ll, 2> best = {LLONG_MAX, -1};
  for (int k = kl; k <= min(m - 1, kr); ++k) {
    best = min(best, {dp[k][j - 1] + (pref[m] - pref[k]) * (pref[m] - pref[k]), k});
  }
  dp[m][j] = best[0];
  compute(l, m - 1, j, kl, best[1]);
  compute(m + 1, r, j, best[1], kr);
}
for (int i = 0; i < N; ++i) {
  for (int j = 0; j < N; ++j) {
    dp[i][j] = 1e17;
  }
}
dp[0][0] = 0;
for (int j = 1; j <= k; ++j) {
  compute(1, n, j, 0, n - 1);
}
cout << dp[n][k] << "\n";
