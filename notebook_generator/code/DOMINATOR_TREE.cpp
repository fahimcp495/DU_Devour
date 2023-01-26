const int N = 2e5+5;

vector <int> g[N], rg[N], dtree[N], bucket[N];
int sdom[N], par[N], dom[N], dsu[N], lab[N], arr[N], rev[N], dpar[N], n, ts, src;

void init(int _n, int s) {
  ts = 0, n = _n, src = s;
  for (int i = 1; i <= n; ++i) {
    g[i].clear(), rg[i].clear(), dtree[i].clear(), bucket[i].clear();
    sdom[i]=par[i]=dom[i]=dsu[i]=lab[i]=arr[i]=rev[i]=dpar[i]=0;
  }
}
void dfs(int u) {
   ts++; arr[u] = ts; rev[ts] = u;
   lab[ts] = sdom[ts] = dsu[ts] = ts;
   for(int &v : g[u]) {
      if(!arr[v]) { dfs(v); par[arr[v]] = arr[u]; }
      rg[arr[v]].push_back(arr[u]);
   }
}
inline int root(int u, int x = 0) {
   if(u == dsu[u]) return x ? -1 : u;
   int v = root(dsu[u], x + 1);
   if(v < 0) return u;
   if(sdom[lab[dsu[u]]] < sdom[lab[u]]) lab[u] = lab[dsu[u]];
   dsu[u] = v; return x ? v : lab[u];
}
void build() {
   dfs(src);
   for(int i=n; i; i--) {
      for(int j : rg[i]) sdom[i] = min(sdom[i],sdom[root(j)]);
      if(i > 1) bucket[sdom[i]].push_back(i);
      for(int w : bucket[i]) {
         int v = root(w);
         if(sdom[v] == sdom[w]) dom[w] = sdom[w];
         else dom[w] = v;
      } if(i > 1) dsu[i] = par[i];
   }
   for(int i=2; i<=n; i++) {
      int &dm = dom[i];
      if(dm ^ sdom[i]) dm = dom[dm];
      dtree[rev[i]].push_back(rev[dm]);
      dtree[rev[dm]].push_back(rev[i]);
      dpar[rev[i]] = rev[dm];
   }
}