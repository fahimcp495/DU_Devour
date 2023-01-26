struct pt {
  int x, y;
};
ll cross(pt a, pt b, pt c) {  //ab*ac
  return 1ll*(b.x-a.x)*(c.y-a.y) - 1ll*(c.x-a.x)*(b.y-a.y);
}
vector<pt> convexHull(vector<pt>& p) {
  sort(p.begin(), p.end(), [&] (pt a, pt b) {
    return (a.x==b.x? a.y<b.y: a.x<b.x);
  });
  int n = p.size(), m = 0;
  vector<pt> hull(2*n);
  for (int i = 0; i < n; ++i){
    while (m>=2 and cross(hull[m-2], hull[m-1], p[i]) < 0)  --m;
    hull[m++] = p[i];
  }
  for (int i = n-2, l = m; i >= 0; --i) {
    while(m>=l+1 and cross(hull[m-2], hull[m-1], p[i]) < 0)  --m;
    hull[m++] = p[i];
  }
  hull.resize(m-1);
  return hull;
}