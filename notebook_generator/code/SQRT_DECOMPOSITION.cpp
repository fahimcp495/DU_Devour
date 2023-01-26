const int SZ2 = 2e5, SZ = sqrt(SZ2+.0)+1, N = SZ*SZ;
int n, a[N], b[SZ];
void build() {
  for (int i = 0; i < SZ; ++i){
    b[i] = INT_MAX;
  }
  for (int i = 0; i < n; ++i){
    b[i/SZ] = min(b[i/SZ], a[i]);
  }
}
int rmq(int l, int r) {
  int lb = l/SZ, rb = r/SZ;
  int ret = INT_MAX;
  if(lb==rb) {
    for (int i = l; i <= r; ++i){
      ret = min(ret, a[i]);
    }
  } else {
    for (int i = l; i < (lb+1)*SZ; ++i){
      ret = min(ret, a[i]);
    }
    for (int i = lb+1; i < rb; ++i){
      ret = min(ret, b[i]);
    }
    for (int i = rb*SZ; i <= r; ++i){
      ret = min(ret, a[i]);
    }
  }
  return ret;
}