typedef vector<int>::iterator itr;
const int N=1e6+7;
struct WT {
  int sigma=0;
  vector<int> a;
  vector<vector<int>> c;
  vector<vector<ll>> pref;
  set<int> st;
  map<int, int> maf;
  int rmaf[N];
  WT(vector<int> a):a(a){
    for(int& x: a){
      st.insert(x);
    }
    for(int x: st){
      maf[x]=sigma, rmaf[sigma++]=x;
    }
    sigma=st.size();
    c.resize(2*sigma),  pref.resize(2*sigma);
    build(a.begin(), a.end(), 0, sigma-1, 1);
  }

  void build(itr st, itr ed, int lo, int hi, int v){
    if(lo==hi) return;
    int mid = (lo+hi)/2;
    c[v].reserve(ed-st+1), pref[v].reserve(ed-st+1);
    c[v].push_back(0),  pref[v].push_back(0);
    for(itr it=st; it!=ed; ++it){
      c[v].push_back(c[v].back()+(maf[*it]<=mid));
      pref[v].push_back(pref[v].back()+(maf[*it]<=mid)*(*it));
    }
    itr m = stable_partition(st, ed, [=](int x){return maf[x]<=mid;});
    build(st, m, lo, mid, 2*v);
    build(m, ed, mid+1, hi, 2*v+1);
  }

  int count(int k, int idx){
    idx++;
    if(idx <1 or !maf.count(k)) return 0;
    k=maf[k];
    int v=1, lo=0, hi=sigma-1;
    while(lo<hi){
      int mid=(lo+hi)/2;
      int inlft=c[v][idx];
      if(k<=mid){
        idx=inlft, hi=mid, v=2*v;
      } else {
        idx-=inlft, lo=mid+1, v=2*v+1;
      }
    }
    return idx;
  }

  int count(int k, int l, int r){
    return count(k,r)-count(k,l-1);
  }

  int kth(int k, int l, int r){
    r++;
    int v=1, lo=0, hi=sigma-1, mid, inlftl, inlftr;
    while(lo<hi){
      mid = (lo+hi)/2;
      inlftl = c[v][l];
      inlftr = c[v][r];
      if(k<=inlftr-inlftl){
        l=inlftl, r=inlftr;
        hi=mid, v=2*v;
      } else {
        k -= inlftr-inlftl, l-=inlftl, r-=inlftr;
        lo=mid+1, v=2*v+1;
      }
    }
    return rmaf[lo];
  }

  int lte(int k, int l, int r){
    if(!maf.count(k)) return 0;
    k=maf[k];
    r++;
    int v=1, lo=0, hi=sigma-1, ret=0;
    while(lo<hi){
      int mid=(lo+hi)/2;
      int inlftl=c[v][l];
      int inlftr=c[v][r];
      if(k<=mid){
        l=inlftl, r=inlftr;
        hi=mid, v=2*v;
      } else {
        ret += inlftr-inlftl, l-=inlftl, r-=inlftr;
        lo=mid+1, v=2*v+1;
      }
    }
    ret += r-l;
    return ret;
  }

  ll sumlte(int k, int l, int r){
    auto it = st.upper_bound(k);
    if(it==st.begin())  return 0;
    it--;
    k = maf[*it];
    r++;
    int v=1, lo=0, hi=sigma-1;
    ll ret=0;
    while(lo<hi){
      int mid=(lo+hi)/2;
      int inlftl=c[v][l];
      int inlftr=c[v][r];
      if(k<=mid){
        l=inlftl, r=inlftr;
        hi=mid, v=2*v;
      } else {
        ret += pref[v][r]-pref[v][l], l-=inlftl, r-=inlftr;
        lo=mid+1, v=2*v+1;
      }
    }
    ret += (r-l)*rmaf[lo];
    return ret;
  }

  void clear(){
    a.clear();
    for (int i = 0; i < c.size(); ++i){
      c[i].clear();
    }
    for (int i = 0; i < pref.size(); ++i){
      pref.clear();
    }
    st.clear();  maf.clear();
  }
};