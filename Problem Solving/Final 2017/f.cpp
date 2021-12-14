#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace std;
using namespace __gnu_pbds;

template <class T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

#define int long long int
#define endl '\n'
#define pb push_back
#define pi pair<int, int>
#define pii pair<int, pi>
#define fir first
#define sec second
#define MAXN 100005
#define mod 1000000007

struct segtree
{
  int n;
  vector<int> seg;

  int neutral()
  {
    return 0;
  }
  int merge(int a, int b)
  {
    return max(a, b);
  }
  segtree(int sz)
  {
    n = 1;
    while (n < sz)
      n <<= 1;
    seg.assign(n << 1, neutral());
  }
  void upd(int i, int value)
  {
    i += n;
    seg[i] = max(seg[i], value);
    for (i >>= 1; i; i >>= 1)
      seg[i] = merge(seg[i << 1], seg[(i << 1) | 1]);
  }
  int qry(int l, int r)
  {
    int ansl = neutral(), ansr = neutral();
    for (l += n, r += n + 1; l < r; l >>= 1, r >>= 1)
    {
      if (l & 1)
        ansl = merge(ansl, seg[l++]);
      if (r & 1)
        ansr = merge(seg[--r], ansr);
    }
    return merge(ansl, ansr);
  }
};
signed main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  int n;
  cin >> n;
  map<pi, int> mp;
  for (int i = 0; i < n; i++)
  {
    int a, b, c;
    cin >> a >> b >> c;
    mp[{a, b}] += c;
  }
  vector<pi> v;
  ordered_set<int> values;
  for (auto const &i : mp)
  {
    v.pb(i.fir);
    values.insert(i.fir.sec);
  }
  sort(v.begin(), v.end());
  n = v.size();
  int m = values.size();
  segtree dp(m);
  for (int i = 0; i < n;)
  {
    int j = i;
    vector<int> to_put;
    while (j < n && v[j].fir == v[i].fir)
    {
      int x = values.order_of_key(v[j].sec);
      to_put.pb(dp.qry(0, x - 1) + mp[v[j]]);
      j++;
    }
    for (int k = i, l = 0; k < j; k++, l++)
    {
      int x = values.order_of_key(v[k].sec);
      dp.upd(x, to_put[l]);
    }
    i = j;
  }
  cout << dp.qry(0, m - 1) << endl;
  return 0;
}