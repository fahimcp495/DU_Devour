struct DSU {
  int comps;
  vector<int> par, sz;
  DSU(int n): comps(n), par(n), sz(n,1) {
    iota(par.begin(), par.end(), 0);
  }
  int find(int v) {
    return (par[v] == v)? v: (par[v] = find(par[v]));
  }
  void unite(int u, int v) {
    u = find(u), v = find(v);
    if(u != v){
      if(sz[u] < sz[v]) {
        swap(u, v);
      }
      par[v] = u;
      sz[u] += sz[v];
      comps--;
    }
  }
  int size(int v) {
    return sz[find(v)];
  }
  bool same_set(int u, int v) {
    return find(u) == find(v);
  }
};