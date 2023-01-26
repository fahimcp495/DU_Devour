## 2D BIT
int n;
int ft[N][N];

void add(int x, int y, int val){
 x++, y++;
 int idx = x;
 while (idx<=n){
   int idy = y;
   while (idy<=n){
     ft[idx][idy] += val;
     idy += idy & -idy;
   }
   idx += idx & -idx;
 }
}

int csum(int x, int y){
 x++, y++;
 int ret = 0;
 int idx = x;
 while (idx > 0){
   int idy = y;
   while (idy > 0){
     ret += ft[idx][idy];
     idy -= idy & -idy;
   }
   idx -= idx & -idx;
 }
 return ret;
}

int rsum(int x1, int y1, int x2, int y2) {
 return csum(x2, y2)-csum(x1-1, y2)-csum(x2, y1-1)+csum(x1-1, y1-1);
}