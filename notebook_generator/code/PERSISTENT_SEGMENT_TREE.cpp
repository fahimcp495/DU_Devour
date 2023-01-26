## Point Addition & Range Sum:
struct node {
  ll sum;
  node *l, *r;
  node(ll s = 0, node *l = NULL, node *r = NULL): sum(s), l(l), r(r) {}
};
node* add(node *u, int i, int x, int s, int e) {
  if (s == e) return new node(u->sum + x);
  if (!u->l)  u->l = new node(), u->r = new node();
  node *nu = new node(u->sum, u->l, u->r);
  int m = (s + e) / 2;
  if (i <= m)  nu->l = add(nu->l, i, x, s, m);
  else nu->r = add(nu->r, i, x, m + 1, e);
  nu->sum = nu->l->sum + nu->r->sum;
  return nu;
}
ll rsum(node *u, int l, int r, int s, int e) {
  if (!u)  return 0;
  if (s > r or e < l)  return 0;
  if (l <= s and e <= r)  return u->sum;
  int m = (s + e) / 2;
  return rsum(u->l, l, r, s, m) + rsum(u->r, l, r, m + 1, e);
}
vector<node*> root(VER);
root[0] = new node();  // initialization
int ver = 1;
root[k] = add(root[k], i, x, 0, sz - 1);;  // Assign a[i] = x in version k
root[ver++] = root[k];  // Create a new version from kth version
cout << rsum(root[k], l, r, 0, sz - 1) << "\n";  // Range sum of version k

## count numbers > k in a range
root[0] = new node();
for (int i = 0; i < n; ++i) {
  root[i + 1] = add(root[i], a[i], 1);
}
while (q--) {
  int l, r, k;  cin >> l >> r >> k;  l--, r--;
  int ans = rsum(root[r + 1], k, E - 1) - rsum(root[l], k, E - 1);
  cout << ans << "\n";
}

## kth number in a range: O(logn)
int kth(node *ul, node *ur, int k, int s = 0, int e = E - 1) {
  if (s == e)  return s;
  int m = (s + e) / 2;
  int cnt_left = ur->left->sum - ul->left->sum;
  if (cnt_left >= k)  return kth(ul->left, ur->left, k, s, m);
  else  return kth(ul->right, ur->right, k - cnt_left, m + 1, e);
}

root[0] = new node();
for (int i = 0; i < n; ++i) {
  root[i + 1] = add(root[i], a[i + ], 1);
}
while (q--) {
  int l, r, k;  cin >> l >> r >> k;  l--, r--;
  int x = kth(root[l], root[r + 1], k);
}