struct AC{
  const int A = 26;
  vector<vector<int>> nxt, idx;
  vector<int> lnk, out_lnk, ans;
  AC(){newNode();}
  int newNode(){
    nxt.eb(A, 0), idx.eb(0);
    lnk.eb(0),  out_lnk.eb(0),  ans.eb(0);
    return nxt.size()-1;
  }
  void clear(){
    nxt.clear(), idx.clear();
    lnk.clear(), out_lnk.clear(), ans.clear();
    newNode();
  }
  // O(|p|)
  void add(string p, int i){
    int v=0;
    for(char c: p){
      if(!nxt[v][c-'a'])  nxt[v][c-'a'] = newNode();
      v = nxt[v][c-'a'];
    }
    idx[v].eb(i);
  }
  // O(|p1+p2+p3+..|)
  void build(){
    queue<int> q; q.push(0);
    while (!q.empty()){
      int u=q.front();  q.pop();
      for (int i = 0; i < A; ++i){
        int v = nxt[u][i];
        if(!v)  nxt[u][i] = nxt[lnk[u]][i];
        else {
          lnk[v] = u? nxt[lnk[u]][i]: 0;
          out_lnk[v] = idx[lnk[v]].empty()? out_lnk[lnk[v]]: lnk[v];
          q.push(v);
        }
      }
    }
  }
  // O(|T|+match)
  void trav(string T){
    int v=0;
    for(char c: T){
      if(!nxt[v][c-'a'])  v = lnk[v];
      if(nxt[v][c-'a']) v=nxt[v][c-'a'];
      for(auto& i: idx[v]){
        ans[i]++;
      }
      int x = out_lnk[v];
      while(x){
        for(auto& i: idx[x]){
          ans[i]++;
        }
        x = out_lnk[x];
      }
    }
  }
};
//AC ac;  ac.add(pi, i);  ac.build();  ac.trav(T);