#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace std;
using namespace __gnu_pbds;

template <class T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

#define int long long int
#define pb push_back
#define pi pair<int, int>
#define pii pair<int, pi>
#define fir first
#define sec second
#define MAXN 100005
#define mod 1000000007

struct sparse_table
{
  bool is;
  vector<vector<int>> st;
  vector<int> log;

  void build(vector<int> &v, bool is_min)
  {
    is = is_min;
    int n = v.size();
    log.resize(MAXN);
    st.resize(MAXN, vector<int>(25));
    log[1] = 0;
    for (int i = 2; i < MAXN; i++)
      log[i] = log[i >> 1] + 1;
    for (int i = 0; i < n; i++)
      st[i][0] = v[i];
    for (int j = 1; j < 25; j++)
    {
      for (int i = 0; i + (1 << j) <= n; i++)
      {
        if (is)
          st[i][j] = min(st[i][j - 1], st[i + (1 << (j - 1))][j - 1]);
        else
          st[i][j] = max(st[i][j - 1], st[i + (1 << (j - 1))][j - 1]);
      }
    }
  }
  int query(int l, int r)
  {
    int j = log[r - l + 1];
    if (is)
      return min(st[l][j], st[r - (1 << j) + 1][j]);
    return max(st[l][j], st[r - (1 << j) + 1][j]);
  }
};
vector<int> find_left(vector<int> &v)
{
  int n = v.size();
  stack<pi> s;
  vector<int> ans(n);
  for (int i = 0; i < n; i++)
  {
    if (v[i] != -1)
    {
      while (!s.empty() && s.top().fir >= v[i])
        s.pop();
      ans[i] = (!s.empty()) ? s.top().sec : 0;
      s.push({v[i], i});
      continue;
    }
    ans[i] = 0;
  }
  return ans;
}
vector<int> find_right(vector<int> &v)
{
  int n = v.size();
  stack<pi> s;
  vector<int> ans(n);
  for (int i = n - 1; i >= 0; i--)
  {
    if (v[i] != -1)
    {
      while (!s.empty() && s.top().fir >= v[i])
        s.pop();
      ans[i] = (!s.empty()) ? s.top().sec : n - 1;
      s.push({v[i], i});
      continue;
    }
    ans[i] = n - 1;
  }
  return ans;
}
signed main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  int n;
  cin >> n;
  vector<int> v(n);
  deque<int> vals;
  for (int i = 0; i < n; i++)
    cin >> v[i];
  vector<int> l = find_left(v);
  vector<int> r = find_right(v);
  sparse_table minr, maxl;
  minr.build(r, true);
  maxl.build(l, false);
  for (int sz = 3; sz <= n; sz++)
  {
    bool can = true;
    int l = 0, r = sz - 1;
    while (l < n)
    {
      if (r - l + 1 < 3)
        can = false;
      int mr = minr.query(l, r);
      int ml = maxl.query(l, r);
      if (ml + 1 > mr - 1)
        can = false;
      l = r + 1;
      r = min(l + sz - 1, n - 1);
    }
    if (can)
    {
      cout << "Y\n";
      exit(0);
    }
  }
  cout << "N\n";
  return 0;
}