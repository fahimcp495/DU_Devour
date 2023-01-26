vector<int> adj[N];
int t = 0;
vector<int> tin(N, -1), lo(N);
vector<array<int, 2>> ab;
void dfs (int u, int p) {
  tin[u] = lo[u] = t++;
  for (int v: adj[u]) {
    if (v != p) {
      if (tin[v] != -1) {
        lo[u] = min(lo[u], tin[v]);
      }
      else {
        dfs(v, u);
        if (tin[u] < lo[v]) {
          ab.push_back({u, v});
        }
        lo[u] = min(lo[u], lo[v]);
      }
    }
  }
}
dfs(0, -1);