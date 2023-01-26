## Max prefix query with insertion only
a1 < a2 < a3 < ... < and b1 < b2 < b3 < ... < bn
// query
auto it = dp.lower_bound(a);
if (it != dp.begin()) {
  mx = max(now, prev(it)->second);
}
// insert
it = dp.upper_bound(a);
if (it != dp.begin() and prev(it)->second >= b) {
  continue;
}
it = dp.insert(it, {a, b});
it->second = b;
while (next(it) != dp.end() and next(it)->second <= b) {
  dp.erase(next(it));
}