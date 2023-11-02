#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace std;
using namespace __gnu_pbds;

#define lli long long int
#define endl '\n'
#define pb push_back
#define pi pair<int, int>
#define pii pair<pi, pi>
#define fir first
#define sec second
#define MAXN 100006
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

rmq rr;
string s;
vector<int> v, pref, lim, valid;

// contar substrings balanceadas de parenteses
// e nao começam nem terminam com +
lli solve(int l, int r)
{
  if (l > r)
  {
    return 0;
  }
  if (l == r)
  {
    return (s[l] >= 'a' && s[l] <= 'z');
  }

  int mid = (l + r) >> 1;
  lli ans = solve(l, mid) + solve(mid + 1, r);

  int ini_a = lower_bound(valid.begin(), valid.end(), l) - valid.begin();
  int ini_b = lower_bound(valid.begin(), valid.end(), mid + 1) - valid.begin();

  vector<pi> qries(ini_b - ini_a);
  int pos = 0;

  while (ini_a < valid.size() && valid[ini_a] <= mid)
  {
    qries[pos] = {lim[valid[ini_a]], pref[valid[ini_a]]};
    ini_a++;
    pos++;
  }

  sort(qries.begin(), qries.end());
  gp_hash_table<int, int> cnt;
  int ptr = 0;

  while (ini_b < valid.size() && valid[ini_b] <= r)
  {
    while (ptr < qries.size() && qries[ptr].fir < valid[ini_b])
    {
      if (cnt.find(qries[ptr].sec) != cnt.end())
        ans += cnt[qries[ptr].sec];
      ptr++;
    }

    cnt[pref[valid[ini_b] + 1]]++;
    ini_b++;
  }

  while (ptr < qries.size())
  {
    if (cnt.find(qries[ptr].sec) != cnt.end())
      ans += cnt[qries[ptr].sec];
    ptr++;
  }

  return ans;
}
signed main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  cin >> s;
  for (auto &i : s)
  {
    if (i >= 'a' && i <= 'z')
      i = 'a';
    else if (i == '(' || i == ')')
      continue;
    else
      i = '+';
  }
  int n = s.size();
  set<string> bad;
  bad.insert("()");
  bad.insert("(+");
  bad.insert("+)");
  bad.insert("++");
  bad.insert(")(");
  bad.insert(")a");
  bad.insert("a(");
  vector<pi> guys;
  {
    int i = 0;
    while (i < n)
    {
      int j = i;
      while (j + 1 < n && !bad.count(s.substr(j, 2)))
      {
        j++;
      }
      guys.pb({i, j});
      i = j + 1;
    }
  }

  v = vector<int>(n);
  lim = vector<int>(n);
  pref = vector<int>(n + 1, 0);
  for (int i = 0; i < n; i++)
  {
    if (s[i] == '(')
      v[i] = 1;
    else if (s[i] == ')')
      v[i] = -1;
    else
      v[i] = 0;
    pref[i + 1] = pref[i] + v[i];
  }

  rr = rmq(pref, false);

  auto check = [&](int a, int b)
  {
    int mn = rr.query(a + 1, b + 1);
    return (pref[a] <= mn);
  };

  for (int i = 0; i < n; i++)
  {
    int lo = i, hi = n - 1;
    while (lo < hi)
    {
      int mid = (lo + hi + 1) >> 1;
      (check(i, mid)) ? lo = mid : hi = mid - 1;
    }
    lim[i] = lo;
  }

  for (int i = 0; i < n; i++)
  {
    if (s[i] != '+')
      valid.pb(i);
  }

  lli ans = 0;
  for (auto &[l, r] : guys)
  {
    ans += solve(l, r);
  }
  cout << ans << endl;
}