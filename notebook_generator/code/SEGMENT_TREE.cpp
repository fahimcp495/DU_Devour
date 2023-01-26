## Point Assign & Range Query
## Point Assign & Range Min/Max with frequency
## Point Assign & Range Maximum Sum
struct Node {
  ll sum, mx, pref, suf;
} t[4 * N];
Node combine(Node l, Node r) {
  Node ret;
  ret.pref = max(l.pref, l.sum + r.pref);
  ret.suf = max(l.suf + r.sum, r.suf);
  ret.sum = l.sum + r.sum;
  ret.mx = max({l.mx, l.suf + r.pref, r.mx});
  return ret;
}
void update(int idx, int x, int v = 1, int st = 0, int ed = n - 1) {
  if (st > idx or ed < idx)  return ;
  if (st == ed) {
    t[v].sum = t[v].mx = t[v].pref = t[v].suf = x;
    return ;
  }
  int lc = 2 * v, rc = 2 * v + 1;
  int mid = (st + ed) / 2;
  update(idx, x, lc, st, mid);
  update(idx, x, rc, mid + 1, ed);
  t[v] = combine(t[lc], t[rc]);
}
Node mx_sum(int l, int r, int v = 1, int st = 0, int ed = n - 1) {
  if (st > r or ed < l)  return {0, ll(-1e15), ll(-1e15), ll(-1e15)};
  if (l <= st and ed <= r) return t[v];
  int lc = 2 * v, rc = 2 * v + 1;
  int mid = (st + ed) >> 1;
  Node lret = mx_sum(l, r, lc, st, mid);
  Node rret = mx_sum(l, r, rc, mid + 1, ed);
  Node ret = combine(lret, rret);
  return ret;
}
## Point Assign & Range Composite:
- 0 p c d: f_p : = cx + d
                   - 1 l r x: f_r(f_(r - 1)(...f_l(x))) % mod
struct Node {
  int a, b;
} t[3 * N];
void assign(int i, int ai, int bi, int u = 1, int s = 0, int e = n - 1) {
  if (s > i or e < i)  return ;
  if (s == e) {
    t[u].a = ai;
    t[u].b = bi;
    return ;
  }
  int v = 2 * u, w = 2 * u + 1, m = (s + e) / 2;
  assign(i, ai, bi, v, s, m);
  assign(i, ai, bi, w, m + 1, e);
  t[u].a = 1ll * t[w].a * t[v].a % mod;
  t[u].b = (1ll * t[w].a * t[v].b + t[w].b) % mod;
}
Node query(int l, int r, int u = 1, int s = 0, int e = n - 1) {
  if (l > e or r < s)  return {1, 0};
  if (l <= s and e <= r) return t[u];
  int v = 2 * u, w = 2 * u + 1, m = (s + e) / 2;
  Node lret = query(l, r, v, s, m);
  Node rret = query(l, r, w, m + 1, e);
  Node ret;
  ret.a = 1ll * rret.a * lret.a % mod;
  ret.b = (1ll * rret.a * lret.b + rret.b) % mod;
  return ret;
}
## Range Affine & Range Sum
- 0 l r b c: a[i] : = b * a[i] + c
                      - 1 l r: range sum
struct Node {
  int a = 1, b = 0, sum = 0;
} t[3 * N];
void push(int u, int s, int e) {
  int v = 2 * u, w = 2 * u + 1, m = (s + e) / 2;
  t[v].sum = (1ll * t[u].a * t[v].sum + 1ll * (m - s + 1) * t[u].b) % mod;
  t[v].a = 1ll * t[u].a * t[v].a % mod;
  t[v].b = (1ll * t[u].a * t[v].b + t[u].b) % mod;
  t[w].sum = (1ll * t[u].a * t[w].sum + 1ll * (e - m) * t[u].b) % mod;
  t[w].a = 1ll * t[u].a * t[w].a % mod;
  t[w].b = (1ll * t[u].a * t[w].b + t[u].b) % mod;
  t[u].a = 1;
  t[u].b = 0;
}
void update(int l, int r, int a, int b, int u = 1, int s = 0, int e = n - 1) {
  if (l > e or r < s)  return ;
  if (l <= s and e <= r) {
    t[u].sum = (1ll * a * t[u].sum + 1ll * (e - s + 1) * b) % mod;
    t[u].a = 1ll * a * t[u].a % mod;
    t[u].b = (1ll * a * t[u].b + b) % mod;
    return ;
  }
  if (t[u].b != 0)  push(u, s, e);
  int v = 2 * u, w = 2 * u + 1, m = (s + e) / 2;
  update(l, r, a, b, v, s, m);
  update(l, r, a, b, w, m + 1, e);
  t[u].sum = (t[v].sum + t[w].sum) % mod;
}
int rsum(int l, int r, int u = 1, int s = 0, int e = n - 1) {
  if (l > e or r < s)  return 0;
  if (l <= s and e <= r) return t[u].sum;
  if (t[u].b != -1)  push(u, s, e);
  int v = 2 * u, w = 2 * u + 1, m = (s + e) / 2;
  int lret = rsum(l, r, v, s, m);
  int rret = rsum(l, r, w, m + 1, e);
  return (lret + rret) % mod;
}
## Range Most Frequent for sorted array:
struct node {
  int pref, pref_freq, suf, suf_freq, max_freq;
} t[3 * MXN];
node combine(node lc, node rc) {
  node res;
  res.pref = lc.pref;
  res.pref_freq = lc.pref_freq;
  if (lc.pref == rc.pref) {
    res.pref_freq += rc.pref_freq;
  }
  res.suf = rc.suf;
  res.suf_freq = rc.suf_freq;
  if (lc.suf == rc.suf) {
    res.suf_freq += lc.suf_freq;
  }
  res.max_freq = max({lc.max_freq, lc.suf == rc.pref ? lc.suf_freq + rc.pref_freq : 0, + rc.max_freq});
  return res;
}
void build(int v = 1, int st = 0, int ed = n - 1) {
  if (st > ed) return ;
  if (st == ed) {
    t[v] = {a[st], 1, a[st] , 1, 1};
    return ;
  }
  int lc = v << 1;
  int rc = lc ^ 1;
  int m = (st + ed) >> 1;
  build(lc, st, m);
  build(rc, m + 1, ed);
  t[v] = combine(t[lc], t[rc]);
}
node query(int l, int r, int v = 1, int st = 0, int ed = n - 1) {
  if (l > ed or r < st)  return {INT_MIN, 0, INT_MAX, 0, 0};
  if (l <= st and ed <= r) return t[v];
  int lc = v << 1;
  int rc = lc ^ 1;
  int m = (st + ed) >> 1;
  node lans = query(l, r, lc, st, m);
  node rans = query(l, r, rc, m + 1, ed);
  node res = combine(lans, rans);
  return res;
}
## Point Update & kth non zero
## Point Update & first_above
## Point Update & Range Max Prefix Sum
## Remove Point & Point Query
## Range Inversion Count
struct Node {
  int cnt[40];
  ll inv;
  Node(): inv(0) {memupdate(cnt, 0, sizeof(cnt));}
} t[4 * N];
void update(int i, int x, int y, int v = 1, int s = 0, int e = n - 1) {
  if (s > i or e < i)  return ;
  if (s == e) {
    if (x != -1) t[v].cnt[x]--;
    t[v].cnt[y]++;
    t[v].inv = 0;
    return ;
  }
  int lc = 2 * v, rc = 2 * v + 1;
  int m = (s + e) / 2;
  update(i, x, y, lc, s, m);
  update(i, x, y, rc, m + 1, e);
  t[v].inv = t[lc].inv + t[rc].inv;
  int now = 0;
  for (int j = 0; j < 40; ++j) {
    t[v].inv += 1LL * t[lc].cnt[j] * now;
    now += t[rc].cnt[j];
    t[v].cnt[j] = t[lc].cnt[j] + t[rc].cnt[j];
  }
}
Node count_inv(int l, int r, int v = 1, int s = 0, int e = n - 1) {
  if (s > r or e < l)  return Node();
  if (l <= s and e <= r) {
    return t[v];
  }
  int lc = 2 * v, rc = 2 * v + 1;
  int m = (s + e) / 2;
  Node lret = count_inv(l, r, lc, s, m);
  Node rret = count_inv(l, r, rc, m + 1, e);
  Node ret;
  ret.inv = lret.inv + rret.inv;
  int now = 0;
  for (int j = 0; j < 40; ++j) {
    ret.inv += 1LL * lret.cnt[j] * now;
    now += rret.cnt[j];
    ret.cnt[j] = lret.cnt[j] + rret.cnt[j];
  }
  return ret;
}
## Point Update & Range Distinct Elements:
void add(int idx, int i, int x, int v = 1, int s = 0, int e = n - 1) {
  if (s > i or e < i)  return ;
  if (s == e) {
    t[idx][v] += x;
    return ;
  }
  int lc = 2 * v, rc = 2 * v + 1;
  int m = (s + e) / 2;
  add(idx, i, x, lc, s, m);
  add(idx, i, x, rc, m + 1, e);
  t[idx][v] = t[idx][lc] + t[idx][rc];
}
int rsum(int idx, int l, int r, int v = 1, int s = 0, int e = n - 1) {
  if (s > r or e < l)  return 0;
  if (l <= s and e <= r) return t[idx][v];
  int lc = 2 * v, rc = 2 * v + 1;
  int m = (s + e) / 2;
  int lret = rsum(idx, l, r, lc, s, m);
  int rret = rsum(idx, l, r, rc, m + 1, e);
  return lret + rret;
}
## Range Addition & Range Weighted Sum:
struct Node {
  ll sum = 0, wsum = 0, p = 0;
} t[3 * N];
void f(int x, int u, int s, int e) {
  t[u].sum += 1LL * (e - s + 1) * x;
  t[u].wsum += 1LL * (e - s + 1) * (e - s + 2) / 2 * x;
  t[u].p += x;
}
void push(int u, int s, int e) {
  int v = 2 * u, w = 2 * u + 1, m = (s + e) / 2;
  f(t[u].p, v, s, m);
  f(t[u].p, w, m + 1, e);
  t[u].p = 0;
}
void add(int l, int r, int x, int u = 1, int s = 0, int e = n - 1) {
  if (l > e or r < s)  return;
  if (l <= s and e <= r) {
    f(x, u, s, e);
    return;
  }
  push(u, s, e);
  int v = 2 * u, w = 2 * u + 1, m = (s + e) / 2;
  add(l, r, x, v, s, m);
  add(l, r, x, w, m + 1, e);
  t[u].sum = t[v].sum + t[w].sum;
  t[u].wsum = t[v].wsum + (t[w].wsum + (m - s + 1) * t[w].sum);
}
// 1*a[l] + 2*a[l + 1] + 3*a[l+3] + ...
Node rwsum(int l, int r, int u = 1, int s = 0, int e = n - 1) {
  if (l > e or r < s)  return {0, 0, 0};
  if (l <= s and e <= r) return t[u];
  push(u, s, e);
  int v = 2 * u, w = 2 * u + 1, m = (s + e) / 2;
  Node ln = rwsum(l, r, v, s, m);
  Node rn = rwsum(l, r, w, m + 1, e);
  return {ln.sum + rn.sum, ln.wsum + (rn.wsum + max(0, (m - max(l, s) + 1))*rn.sum), 0};
}
## Add Arithmetic Progression on Range & Range Sum Query:
struct Node {
  ll a = 0, d = 0, sum = 0;
} t[3 * N];
ll sum(ll a, ll d, ll n) {
  return n * (2 * a + (n - 1) * d) / 2;
}
void push(int v, int st, int ed) {
  int lc = 2 * v, rc = 2 * v + 1, md = (st + ed) / 2;
  t[lc].a += t[v].a;
  t[lc].d += t[v].d;
  t[lc].sum += sum(t[v].a, t[v].d, md - st + 1);
  t[rc].a += t[v].a + 1LL * (md - st + 1) * t[v].d;
  t[rc].d += t[v].d;
  t[rc].sum += sum(t[v].a + 1LL * (md - st + 1) * t[v].d, t[v].d, ed - md);
  t[v].a = t[v].d = 0;
}
void add(int l, int r, int a, int d, int v = 1, int st = 0, int ed = n - 1) {
  if (l > ed or r < st)  return;
  if (l <= st and ed <= r) {
    t[v].a += a + 1LL * (st - l) * d;
    t[v].d += d;
    t[v].sum += sum(a + 1LL * (st - l) * d, d, (ed - st + 1));
    return;
  }
  int lc = 2 * v, rc = 2 * v + 1, md = (st + ed) / 2;
  if (t[v].d)  push(v, st, ed);
  add(l, r, a, d, lc, st, md);
  add(l, r, a, d, rc, md + 1, ed);
  t[v].sum = t[lc].sum + t[rc].sum;
}
ll rsum(int l, int r, int v = 1, int st = 0, int ed = n - 1) {
  if (l > ed or r < st)  return 0;
  if (l <= st and ed <= r) return t[v].sum;
  int lc = 2 * v, rc = 2 * v + 1, md = (st + ed) / 2;
  if (t[v].d)  push(v, st, ed);
  ll lret = rsum(l, r, lc, st, md);
  ll rret = rsum(l, r, rc, md + 1, ed);
  return lret + rret;
}
## Range Update & Number of Segment with only set value & the total number of set value:
int t[3 * N], t2[3 * N], p[3 * N];
bool lb[3 * N], rb[3 * N]; //lb for left most bit of interval corresponding to this node
void f(int u, int x, int l, int r) {
  t[u] = (r - l + 1) * x;
  t2[u] = x;
  p[u] = x;
  lb[u] = rb[u] = x;
}
void push(int u, int s, int e) {
  int v = 2 * u, w = 2 * u + 1, m = (s + e) / 2;
  f(v, p[u], s, m);
  f(w, p[u], m + 1, e);
  p[u] = -1;
}
void assign(int l, int r, bool x, int u = 1, int s = 0, int e = N - 1) {
  if (l > e or r < s)  return ;
  if (l <= s and e <= r) {
    f(u, x, s, e);
    return ;
  }
  int v = 2 * u, w = 2 * u + 1, m = (s + e) / 2;
  if (p[u] != -1)  push(u, s, e);
  assign(l, r, x, v, s, m);
  assign(l, r, x, w, m + 1, e);
  t[u] = t[v] + t[w];
  t2[u] = t2[v] + t2[w];
  lb[u] = lb[v];
  rb[u] = rb[w];
  if (rb[v] == 1 and lb[w] == 1)  t2[u]--;
}
Update: assign(l, r, 0 / 1);
Query: t[1]: = total number of set bit, t2[1]: = total  number of segment with only set value

## Make All Elements <= k and Make all elements >= k on range & Point Query:
               const int I = 1e9 + 9;
int t[3 * N], pa[3 * N], pr[3 * N], ar[3 * N]; //pa for propagate adding, pr for propagate remove, ar for check last on is adding(1) or remove(0)
void fg(int x, int u) {   //function for make_greater
  t[u] = max(t[u], x);
  pa[u] = max(pa[u], x);
  pr[u] = max(pr[u], x);
  ar[u] = 1;
}
void fl(int x, int u) {   //function for make_less
  t[u] = min(t[u], x);
  pr[u] = min(pr[u], x);
  pa[u] = min(pa[u], x);
  ar[u] = 0;
}
void push(int u) {
  int v = 2 * u, w = 2 * u + 1;
  if (ar[u] == 0) {
    if (pa[u] != -1) {
      fg(pa[u], v); fg(pa[u], w);
    }
    if (pr[u] != I) {
      fl(pr[u], v); fl(pr[u], w);
    }
  } else {
    if (pr[u] != I) {
      fl(pr[u], v); fl(pr[u], w);
    }
    if (pa[u] != -1) {
      fg(pa[u], v); fg(pa[u], w);
    }
  }
  pa[u] = -1; pr[u] = I;
}
void make_greater(int l, int r, int x, int u = 1, int s = 0, int e = N - 1) {
  if (l > e or r < s)  return;
  if (l <= s and e <= r) {
    fg(x, u);
    return ;
  }
  push(u);
  int v = 2 * u, w = 2 * u + 1, m = (s + e) / 2;
  make_greater(l, r, x, v, s, m);
  make_greater(l, r, x, w, m + 1, e);
}
void make_less(int l, int r, int x, int u = 1, int s = 0, int e = N - 1) {
  if (l > e or r < s)  return;
  if (l <= s and e <= r) {
    fl(x, u);
    return;
  }
  push(u);
  int v = 2 * u, w = 2 * u + 1, m = (s + e) / 2;
  make_less(l, r, x, v, s, m);
  make_less(l, r, x, w, m + 1, e);
}
int at(int i, int u = 1, int s = 0, int e = N - 1) {
  if (s == e)  return t[u];
  push(u);
  int v = 2 * u, w = 2 * u + 1, m = (s + e) / 2;
  if (i <= m)  return at(i, v, s, m);
  else  return at(i, w, m + 1, e);
}
## Range Addition and Range Assign and Range sum
int n;
ll t[3 * N], p[3 * N], p2[3 * N]; //t for sum, p for assign & p2. for add
void pull(int v) {
  t[v] = t[2 * v] + t[2 * v + 1];
}
void push(int v, int st, int ed) {
  int lc = 2 * v, rc = 2 * v + 1, md = (st + ed) / 2;
  if (p[v] != -1) {
    t[lc] = p[v] * (md - st + 1);
    t[rc] = p[v] * (ed - md);
    p[lc] = p[rc] = p[v];
    p2[lc] = p2[rc] = 0;
    p[v] = -1;
  }
  if (p2[v]) {
    t[lc] += p2[v] * (md - st + 1);
    t[rc] += p2[v] * (ed - md);
    p2[lc] += p2[v];
    p2[rc] += p2[v];
    p2[v] = 0;
  }
}
void assign(int l, int r, int x, int v = 1, int st = 0, int ed = n - 1) {
  if (l > ed or r < st)  return;
  if (l <= st and ed <= r) {
    t[v] = 1LL * (ed - st + 1) * x;
    p[v] = x;
    p2[v] = 0;
    return;
  }
  int lc = 2 * v, rc = 2 * v + 1, md = (st + ed) / 2;
  push(v, st, ed);
  assign(l, r, x, lc, st, md);
  assign(l, r, x, rc, md + 1, ed);
  pull(v);
}
void add(int l, int r, int x, int v = 1, int st = 0, int ed = n - 1) {
  if (l > ed or r < st)  return;
  if (l <= st and ed <= r) {
    t[v] += 1LL * (ed - st + 1) * x;
    p2[v] += x;
    return ;
  }
  push(v, st, ed);
  int lc = 2 * v, rc = 2 * v + 1, md = (st + ed) / 2;
  add(l, r, x, lc, st, md);
  add(l, r, x, rc, md + 1, ed);
  pull(v);
}
ll rsum(int l, int r, int v = 1, int st = 0, int ed = n - 1) {
  if (l > ed or r < st)  return 0;
  if (l <= st and ed <= r) return t[v];
  push(v, st, ed);
  int lc = 2 * v, rc = 2 * v + 1, md = (st + ed) / 2;
  ll lret = rsum(l, r, lc, st, md);
  ll rret = rsum(l, r, rc, md + 1, ed);
  return lret + rret;
}
