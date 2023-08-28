#include <bits/stdc++.h>
using namespace std;

#define lli long long int
#define endl '\n'
#define pb push_back
#define pi pair<int, int>
#define pii pair<int, pi>
#define fir first
#define sec second
#define MAXN 200005
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
  int n;
  cin >> n;
  vector<int> v(n);
  for (int i = 0; i < n; i++)
    cin >> v[i];
  rmq r_min(v, 0);
  rmq r_max(v, 1);
  lli ans = 0;
  {
    vector<pi> q;
    q.pb({0, n - 1});
    while (!q.empty())
    {
      int l = q.back().fir;
      int r = q.back().sec;
      int max_pos = r_max.qry(l, r);
      q.pop_back();
      lli qt = (max_pos - l + 1) * 1ll * (r - max_pos + 1);
      ans += (v[max_pos] * 1ll * qt);
      if (max_pos > l)
        q.pb({l, max_pos - 1});
      if (max_pos < r)
        q.pb({max_pos + 1, r});
    }
  }
  {
    vector<pi> q;
    q.pb({0, n - 1});
    while (!q.empty())
    {
      int l = q.back().fir;
      int r = q.back().sec;
      int min_pos = r_min.qry(l, r);
      q.pop_back();
      lli qt = (min_pos - l + 1) * 1ll * (r - min_pos + 1);
      ans -= (v[min_pos] * 1ll * qt);
      if (min_pos > l)
        q.pb({l, min_pos - 1});
      if (min_pos < r)
        q.pb({min_pos + 1, r});
    }
  }
  cout << ans << endl;
  return 0;
}
// https://github.com/brunomaletta/Biblioteca/blob/master/Codigo/Estruturas/rmq.cpp
// O(n) pra buildar, query O(1)
// qry(l, r) -> retorna o indice do menor elemento no range [l, r]
// query(l, r) -> retorna o menor elemento no range [l, r]

// problema exemplo: https://codeforces.com/contest/817/problem/D