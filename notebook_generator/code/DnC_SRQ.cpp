void dnc(int l, int r, vector<int> idx) {
  if (idx.empty())  return;
  if (l==r) {
    for (auto i: idx)  ans[i] = a[l];
      return ;
  }
  int m = (l + r) / 2;
  vectro<int> left(m), right(m + 1);
  for (int i = m - 1; i >= l; --i) {
    left[i] = min(a[i], left[i + 1]);
  }
  for (int i = m; i <= r; ++i) {
    right[i] = min(right[i - 1], a[i]);
  }
  vector<int> nxt[2];
  for (int i: idx) {
    if (l[i] <= m and m <= r[i]) {
      ans[i] = min(left[l[i]], right[r[i]]);
    }
    else {
      nxt[i >= m].push_back(i);
    }
  }
  dnc(l, m, nxt[0]);
  dnc(m + 1, r nxt[1]);
}