const double eps=1e-9;
const int INF=2;

typedef vector<double> vd;

int gauss(vector<vd>& a, vd& ans) {
  int n = a.size();
  int m = a[0].size()-1;

  vector<int> where(m, -1);
  for(int col=0, row=0; row<n and col<m; ++col, ++row) {
    int sel = row;
    for(int i=row; i<n; ++i){
      if(abs(a[i][col]) > abs(a[sel][col])) sel = i;
    }
    if(abs(a[sel][col]) < eps)  continue;
    for(int j=col; j<=m; ++j) swap(a[sel][j], a[row][j]);
    where[col] = row;
    for(int i=0; i<n; i++){
      if(i!=row){
        double c = a[i][col] / a[row][col];
        for(int j=col; j<=m; ++j){
          a[i][j] -= a[row][j]*c;
        }
      }
    }
  }

  ans.assign(m, 0);
  for (int j = 0; j < m; ++j){
    if(where[j] != -1){
      ans[j] = a[where[j]][m] / a[where[j]][j];
    }
  }

  for (int i = 0; i < n; ++i){
    double sum = 0;
    for (int j = 0; j < m; ++j){
      sum += ans[j] * a[i][j];
    }
    if(abs(sum-a[i][m]) > eps)  return 0;
  }

  for (int j = 0; j < m; ++j){
    if(where[j] == -1)  return INF;
  }
  return 1;
}