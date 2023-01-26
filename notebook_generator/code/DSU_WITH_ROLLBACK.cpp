struct DSU {
  int comps;
  vector<int> par, rnk;
  stack<array<int, 4>> ops;

  DSU(){}
  DSU(int n): comps(n), par(n), rnk(n) {
    iota(par.begin(), par.end(), 0);
  }

  int find(int u) {
    return (par[u] == u)? u: find(par[u]);
  }

  bool unite(int u, int v) {
    u = find(u), v = find(v);
    if (u == v)  return false;

    if (rnk[u] > rnk[v])  swap(u, v);
    ops.push({u, rnk[u], v, rnk[v]});
    par[u] = v;
    if (rnk[u] == rnk[v])  rnk[v]++;
    return true;
  }

  void rollback() {
    if (ops.empty())  return ;
    auto [u, rnku, v, rnkv] = ops.top();  ops.pop();
    par[u] = u, rnk[u] = rnku;
    par[v] = v, rnk[v] = rnkv;
    comps++;
  }
};