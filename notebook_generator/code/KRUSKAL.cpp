vector<Edge> mst(){
 vector<Edge> res;
 int cnt=0;
 sort(ed.begin(), ed.end());
 DSU dsu(n);
 for(Edge e: ed){
   if(!dsu.same_set(e.u, e.v)){
     res.push_back(e);
     dsu.unite(e.u,e.v);
     if(++cnt >= n-1)  break;
   }
 }
 return res;
}