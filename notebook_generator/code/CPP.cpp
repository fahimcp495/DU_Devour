## Ordered Set
#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;
typedef tree<int,null_type,less<int>,rb_tree_tag,
tree_order_statistics_node_update> oset;

oset ost;
ost.order_of_key(495): // return 0-based index of lower_bound
ost.find_by_order(5): // return iterator of 0-based index value
ost.erase(); ost.size(), ost.insert(2), st.lower_bound(x);

## unordered_map
struct chash{
  size_t operator()(const pair<int,int>&x)const{
    return hash<long long>()(((long long)x.first)^(((long long)x.second)<<32));
  }
};
unordered_map<pair<int, int>, int, chash> maf;
maf.reserve(max_len);
maf.max_load_factor(0.25);

## gp_hash_table:
#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;

struct chash{
  int operator()(ii p) const {
    return p.first*31 + p.second;
  }
};
gp_hash_table<ii, int, chash> cnt;