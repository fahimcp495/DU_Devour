const int N = 1e5+10;
struct vertex
{
  int len, link, no_of_suf_pal;
  map<char, int> next;
}pt[N];
int sz, at, cnt[N];
char s[N];

void pt_init(){
  for (int i = 0; i < N; ++i){
    pt[i].next.clear();
  }
  memset(cnt, 0, sizeof(cnt));
  pt[0].len = -1, pt[0].link = 0, pt[0].no_of_suf_pal = 0;
  pt[1].len = 0, pt[1].link = 0, pt[1].no_of_suf_pal = 0;
  sz = at = 1;
}

void pt_extend(int si){   //string index
  while (s[si - pt[at].len - 1] != s[si]) at = pt[at].link;
  int x = pt[at].link, c = s[si]-'a';
  while (s[si - pt[x].len - 1] != s[si])  x = pt[x].link;
  if(!pt[at].next.count(c)){
    pt[at].next[c] = ++sz;
    pt[sz].len = pt[at].len + 2;
    // cnt[pt[at].len+2]++;   //for  finding number of distinct palindrome of lenght k
    pt[sz].link = (pt[sz].len == 1)? 1 : pt[x].next[c];
    // pt[sz].no_of_suf_pal = 1 + pt[pt[sz].link].no_of_suf_pal;  //for finding number of palindrome which last position is si
  }
  // cnt[pt[at].len + 2]++; //for  finding number of palindrome of lenght k
  at = pt[at].next[c];
}

int num_of_pal(int ai){   //distinct palindrome, array index
  int ret = pt[at].ans;
  for(auto x : pt[ai].next)
    ret += num_of_pal(x.second);
  return ret;
}

int main(){
  scanf("%s", s);
  pt_init();
  for (int i = 0; s[i]; ++i){
    pt_extend(i);
  }
  int ans = num_of_pal(0) + num_of_pal(1) - 2;
  printf("%d\n", ans);
  return 0;
}