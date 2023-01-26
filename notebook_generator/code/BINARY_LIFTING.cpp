void dfs(int u, int p){
  d[u]=d[p]+1;
  tin[u] = t++;
  par[u][0]=p;
  for (int i = 1; i < LGN; ++i){
    par[u][i] = par[par[u][i-1]][i-1];
  }
  for(int& v: tr[u])
    if(v!=p)  dfs(v,u);
  tout[u] = t++;
}
 
bool is_anc(int u, int v){
  return tin[u]<=tin[v] and tout[u]>=tout[v];
}
 
int lca(int u, int v){
  if(is_anc(u, v))  return u;
  if(is_anc(v, u))  return v;
  for(int i=LGN-1; i>=0; i--){
    if(!is_anc(par[u][i], v)) u=par[u][i];
  }
  return par[u][0];
}
 
int dist(int u, int v){
  int w = lca(u, v);
  return d[u]-d[w]+d[v]-d[w];
}