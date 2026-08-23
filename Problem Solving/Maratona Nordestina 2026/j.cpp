#include <bits/stdc++.h>
using namespace std;

#define int long long int
#define pb push_back
#define pi pair<int, int>
#define pii pair<pi, int>
#define fir first
#define sec second
#define MAXN 200005
#define mod 1000000007

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
  int n, q;
  cin >> n >> q;
  vector<int> v(n);
  for (int i = 0; i < n; i++)
    cin >> v[i];
  rmq rm(v, 1);
  while (q--)
  {
    int l, r;
    cin >> l >> r;
    l--, r--;
    int mx = rm.query(l, r);
    (mx == v[l] || mx == v[r] || (r - l) % 2) ? cout << "Adilson\n" : cout << "Reginaldo\n";
  }
  return 0;
}