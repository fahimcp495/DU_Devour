int n, a[N], lg[N], st[N][K];
for (int i = 2; i < N; ++i) {
  lg[i] = lg[i / 2] + 1;
}
void build() {
  for (int k = 0; k < K ; ++k) {
    for (int i = 0; i + (1 << k) <= n; ++i) {
      if (k == 0)  st[i][k] = a[i];
      else  st[i][k] = min(st[i][k - 1], st[i + (1 << (k - 1))][k - 1]);
    }
  }
}
int rmq (int l, int r) {
  int k = lg[r - l + 1];
  return min(st[l][k], st[r - (1 << k) + 1][k]);
}