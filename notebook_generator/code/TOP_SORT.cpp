vector<int> top_sort(int n, vector<int> *adj, bool &has_cycle) {
  vector<int> indeg(n);
  for (int u = 0; u < n; ++u) {
    for (int v: adj[u]) {
      indeg[v]++;
    }
  }

  queue<int> q;
  for (int u = 0; u < n; ++u) {
    if (!indeg[u]) {
      q.push(u);
    }
  }

  vector<int> order;
  while (!q.empty()) {
    int u = q.front();  q.pop();
    order.push_back(u);
    for (int v: adj[u]) {
      indeg[v]--;
      if (!indeg[v]) {
        q.push(v);
      }
    }
  }
  has_cycle = order.size() < n;
  return order;
}