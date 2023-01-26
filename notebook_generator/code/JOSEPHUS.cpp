## k = 2
if n = 2^p + e; (p large as possible, e >= 0)
then survivor = 2 * e + 1;
for (int i = 1; i <= n; i++) {
  int x = k * i;  // k = 2
  while (x > n) x = (k * (x - n) - 1) / (k - 1);
  cout << x << " ";
}
int kth(int n, int k, int f = 0) {
  if (n == 1) {
    assert(k == 1);
    return 1;
  }
  if (f == 0) {
    if (2 * k <= n) {
      return 2 * k;
    }
    else {
      f = n & 1;
      k -= n / 2;
      n -= n / 2;
      return 2 * kth(n, k, f) - 1;
    }
  }
  else {
    if (2 * k - 1 <= n) {
      return 2 * k - 1;
    }
    else {
      f = n & 1 ^ 1;
      k -= (n + 1) / 2;
      n -= (n + 1) / 2;
      return 2 * kth(n, k, f);
    }
  }
}

## k != 2
oset s;
for (int i = 1; i <= n; i++) s.insert(i);
for (int sz = n, ord = 0; sz > 0; --sz) {
  ord = (ord + k) % sz;
  auto it = s.find_by_order(ord);
  cout << *it << ' ';
  s.erase(it);
}
