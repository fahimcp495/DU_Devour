vector<int> nsel(vector<int> &a) {
  int n = a.size();
  vector<int> nsel(n);
  stack<int> st;
  st.push(-1);
  for (int i = 0; i < n; ++i) {
    while (st.top() != -1 and a[st.top()] >= a[i]) {
      st.pop();
    }
    nsel[i] = st.top();
    st.push(i);
  }
  return nsel;
}