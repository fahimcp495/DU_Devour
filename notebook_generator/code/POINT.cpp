# point in convex poly: O(logn)
struct pt {
    double x, y;
    pt() {}
    pt(double x, double y) : x(x) , y(y) {}
    pt(const pt &p) : x(p.x) , y(p.y) {}
    pt operator + (const pt &p) const { return pt( x+p.x , y+p.y ); }
    pt operator - (const pt &p) const { return pt( x-p.x , y-p.y ); }
    pt operator * (double c) const { return pt( x*c , y*c ); }
};
inline double dot(pt u, pt v) { return u.x*v.x + u.y*v.y; }
inline double cross(pt u, pt v) {return u.x*v.y - u.y*v.x;}
inline double triArea2(pt a,pt b,pt c) { return cross(b-a,c-a); }
inline bool inDisk(pt a, pt b, pt p) { return dot(a-p, b-p) <= 0; }
inline bool onSegment(pt a, pt b, pt p) { return triArea2(a,b,p) == 0 && inDisk(a,b,p); }
// points of the polygon has to be in ccw order
// if strict, returns false when a is on the boundary
inline bool insideConvexPoly(pt* C, int nc, pt  p, bool strict) {
    int st = 1, en = nc - 1, mid;
    while(en - st > 1) {
        mid = (st + en)>>1;
        if(triArea2(C[0], C[mid], p) < 0) en = mid;
        else st = mid;
    }
    if(strict) {
        if(st==1) if(onSegment(C[0],C[st],p)) return false;
        if(en==nc-1) if(onSegment(C[0],C[en],p)) return false;
        if(onSegment(C[st],C[en],p)) return false;
    }
    if(triArea2(C[0], C[st], p) < 0) return false;
    if(triArea2(C[st], C[en], p) < 0) return false;
    if(triArea2(C[en], C[0], p) < 0) return false;
    return true;
}

# check point in polygon: O(n)
struct pt {
    double x, y;
    pt() {}
    pt(double x, double y) : x(x) , y(y) {}
    pt(const pt &p) : x(p.x) , y(p.y) {}

    pt operator + (const pt &p) const { return pt( x+p.x , y+p.y ); }
    pt operator - (const pt &p) const { return pt( x-p.x , y-p.y ); }
    pt operator * (double c) const { return pt( x*c , y*c ); }
};
inline double dot(pt u, pt v) { return u.x*v.x + u.y*v.y; }
inline double cross(pt u, pt v) {return u.x*v.y - u.y*v.x;}
inline double triArea2(pt a,pt b,pt c) { return cross(b-a,c-a); }
inline bool inDisk(pt a, pt b, pt p) { return dot(a-p, b-p) <= 0; }
inline bool onSegment(pt a, pt b, pt p) { return triArea2(a,b,p) == 0 && inDisk(a,b,p); }
// check if segment pq crosses ray from point a
inline bool crossesRay(pt a, pt p, pt q) {
    int mul = (q.y>=a.y) - (p.y>=a.y);
    return (mul * triArea2(a,p,q)) > 0;
}
// if strict, returns false when a is on the boundary
inline bool insidePoly(pt *P, int np, pt a, bool strict = true) {
    int numCrossings = 0;
    for (int i = 0; i < np; i++) {
        if (onSegment(P[i], P[(i+1)%np], a)) return !strict;
        numCrossings += crossesRay(a, P[i], P[(i+1)%np]);
    }
    return (numCrossings & 1); // inside if odd number of crossings
}

# Polar sort:
inline bool up (point p) {
  return p.y > 0 or (p.y == 0 and p.x >= 0);
}
sort(v.begin(), v.end(), [] (point a, point b) {
  return up(a) == up(b) ? a.x * b.y > a.y * b.x : up(a) < up(b);
});

# Convex Hull
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