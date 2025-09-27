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
#define pii pair<pi, int>
#define fir first
#define sec second
#define MAXN 100005
#define mod 998244353

struct rmq
{
  vector<int> v;
  bool is_max;
  int n;
  static const int b = 30;
  vector<int> mask, t;

  int op(int x, int y)
  {
    if (is_max)
      return v[x] >= v[y] ? x : y;
    return v[x] <= v[y] ? x : y;
  }
  int msb(int x) { return __builtin_clz(1) - __builtin_clz(x); }
  int small(int r, int sz = b) { return r - msb(mask[r] & ((1 << sz) - 1)); }
  rmq() {}
  rmq(vector<int> &v_, bool flag) : v(v_), n(v.size()), mask(n), t(n), is_max(flag)
  {
    for (int i = 0, at = 0; i < n; mask[i++] = at |= 1)
    {
      at = (at << 1) & ((1 << b) - 1);
      while (at and op(i - msb(at & -at), i) == i)
        at ^= at & -at;
    }
    for (int i = 0; i < n / b; i++)
      t[i] = small(b * i + b - 1);
    for (int j = 1; (1 << j) <= n / b; j++)
      for (int i = 0; i + (1 << j) <= n / b; i++)
        t[n / b * j + i] = op(t[n / b * (j - 1) + i], t[n / b * (j - 1) + i + (1 << (j - 1))]);
  }
  int qry(int l, int r)
  {
    if (r - l + 1 <= b)
      return small(r, r - l + 1);
    int x = l / b + 1, y = r / b - 1;
    if (x > y)
      return op(small(l + b - 1), small(r));
    int j = msb(y - x + 1);
    int ans = op(small(l + b - 1), op(t[n / b * j + x], t[n / b * j + y - (1 << j) + 1]));
    return op(ans, small(r));
  }
  int query(int l, int r) { return v[qry(l, r)]; }
};
signed main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  int n, k;
  cin >> n >> k;
  vector<int> v(n);
  vector<int> v2(n);
  for (int i = 0; i < n; i++)
  {
    cin >> v[i];
    v2[i] = v[i] + i;
  }
  rmq rm(v, 0);
  rmq rm2(v2, 0);
  int ans = 0;
  for (int r = 0; r < n; r++) // incrementa k em r, k - 1 em r - 1 ...
  {
    int l = max(0ll, r - k + 1);
    int mn = 1e18;
    if (l > 0)
    {
      mn = min(mn, rm.query(0, l - 1));
    }
    mn = min(mn, rm2.query(l, r) + k - r);
    if (r + 1 < n)
    {
      mn = min(mn, rm.query(r + 1, n - 1));
    }
    ans = max(ans, mn);
  }
  cout << ans << endl;
  return 0;
}