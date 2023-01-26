struct state {
  int len, link, cnt_tmp = 0, cnt = 0;
  map<char, int> next;
};

const int MAXLEN = 100000;
state st[2*MAXLEN];
int dp[2*MAXLEN];
int sz, last;

void sa_init() {
  st[0].len = 0;
  st[0].link = - 1;
  sz++;
  last = 0;
  memset(dp, -1, sizeof(dp));
}

void sa_extend(char c) {
  int cur = sz++;
  st[cur].len = st[last].len + 1;
  int p = last;
  while (p != -1 && !st[p].next.count(c)) {
    st[p].next[c] = cur;
    p = st[p].link;
  }
  if (p == -1) {
    st[cur].link = 0;
  } else {
    int q = st[p].next[c];
    if (st[p].len + 1 == st[q].len) {
      st[cur].link = q;
    } else {
      int clone = sz++;
      st[clone].len = st[p].len + 1;
      st[clone].next = st[q].next;
      st[clone].link = st[q].link;
      while (p != -1 && st[p].next[c] == q) {
        st[p].next[c] = clone;
        p = st[p].link;
      }
      st[q].link = st[cur].link = clone;
    }
  }
  last = cur;
}

## Count Occurence
int occurence(string p){
  int at = 0;
  for (int i = 0; p[i]; ++i){
    if(st[at].next.count(p[i]) == 0){
      return 0;
    }
    else{
        at = st[at].next[p[i]];
    }
  }
  return st[at].cnt_tmp;
}

vector<int> used;

void dfs(int x){
  used[x]=1;
  for(auto it:st[x].next) {
    if(!used[it.second]) dfs(it.second);
    if(it.first=='#') st[x].cnt_tmp++;
    else st[x].cnt_tmp+=st[it.second].cnt_tmp;
    st[x].cnt+=st[it.second].cnt;
  }
  st[x].cnt+=st[x].cnt_tmp;
}

## number of distinct substring O(n)
long long disub(int at){
  if(dp[at] != -1)
    return 0;
  dp[at] = 0;
  long long ret = 0;
  for(auto x : st[at].next)
    ret += disub(x.second);
  if(at != 0)
    ret += (st[at].len - st[st[at].link].len);
  return ret;
}

## longest common substring: O(|T|)
int lcs (string S, string T) {
  sa_init();
  for (int i = 0; i < S.size(); i++)
    sa_extend(S[i]);

  int v = 0, l = 0, best = 0, bestpos = 0;
  for (int i = 0; i < T.size(); i++) {
    while (v && !st[v].next.count(T[i])) {
      v = st[v].link ;
      l = st[v].len ;
    }
    if (st[v].next.count(T[i])) {
      v = st [v].next[T[i]];
      l++;
    }
    if (l > best) {
      best = l;
      bestpos = i;
    }
  }
  return best;
}

## Distinct Substring
long long disub(int at){
  long long ret = 1;
  for(auto x : st[at].next){
      ret += disub(x.second);
  }
  return ret-1;
}

int main(){
  int T, caseno = 0;
  scanf("%d", &T);
  while(T--){
    int q;    cin >> q;
    sa_init();
    string s;   cin >> s;
    cout << s << endl;
    s += "#";
    for (int i = 0; s[i]; ++i){
      sa_extend(s[i]);
    }
    used.assign(sz,0);
    dfs(0);    
    printf("Case %d:\n", ++caseno);
    while (q--){
      string p;    cin >> p;
      int ans = occurence(p);
      cout << ans << endl;
    }
  }
  return 0;
}
1. Finding Pattern
2. Frequency of each stat
3. First Occurrence
4. Last Occurrence
5. All Occurrenc
6. Longest Repeated substring:
7. Count number of different substring
8. Total length of different substring
9. k-th smallest distinct substring
10. K-th smallest substring
11. Smallest Cyclic Shift
12. Find borders
13. Find Periods:
14. Longest Common Substring