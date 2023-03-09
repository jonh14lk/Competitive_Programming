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

struct modint
{
  int val;
  modint(int v = 0) { val = ((v % mod) + mod) % mod; }
  int pow(int y)
  {
    modint x = val;
    modint z = 1;
    while (y)
    {
      if (y & 1)
        z *= x;
      x *= x;
      y >>= 1;
    }
    return z.val;
  }
  int inv() { return pow(mod - 2); }
  void operator=(int o) { val = o % mod; }
  void operator=(modint o) { val = o.val % mod; }
  void operator+=(modint o) { *this = *this + o; }
  void operator-=(modint o) { *this = *this - o; }
  void operator*=(modint o) { *this = *this * o; }
  void operator/=(modint o) { *this = *this / o; }
  bool operator==(modint o) { return val == o.val; }
  bool operator!=(modint o) { return val != o.val; }
  int operator*(modint o) { return ((val * o.val) % mod); }
  int operator/(modint o) { return (val * o.inv()) % mod; }
  int operator+(modint o) { return (val + o.val) % mod; }
  int operator-(modint o) { return (val - o.val + mod) % mod; }
};

// berlekamp massey (muito roubado)
// mas precisa que o mod seja primo (para poder achar inverso)
// dado os n primeiros termos de uma recorrencia linear
// a[0], a[1], a[2], ..., a[n - 1]
// ele acha a reccorrencia linear mais curta que da matching com os n primeiros valores
vector<modint> berlekamp_massey(vector<modint> x)
{
  vector<modint> ls, cur;
  int lf, ld;
  for (int i = 0; i < x.size(); i++)
  {
    modint t = 0;
    for (int j = 0; j < cur.size(); j++)
    {
      t += (x[i - j - 1] * cur[j]);
    }
    if (modint(t - x[i]).val == 0)
      continue;
    if (cur.empty())
    {
      cur.resize(i + 1);
      lf = i;
      ld = (t - x[i]) % mod;
      continue;
    }
    modint k = -(x[i] - t);
    k *= modint(ld).inv();
    vector<modint> c(i - lf - 1);
    c.pb(k);
    for (auto const &j : ls)
    {
      modint curr = modint(j.val * -1) * k;
      c.pb(curr);
    }
    if (c.size() < cur.size())
      c.resize(cur.size());
    for (int j = 0; j < cur.size(); j++)
    {
      c[j] = c[j] + cur[j];
    }
    if (i - lf + ls.size() >= cur.size())
    {
      tie(ls, lf, ld) = make_tuple(cur, i, t - x[i]);
    }
    cur = c;
  }
  return cur;
}
modint get_nth(vector<modint> rec, vector<modint> dp, int n)
{
  int m = rec.size();
  vector<modint> s(m), t(m);
  s[0] = 1;
  if (m != 1)
    t[1] = 1;
  else
    t[0] = rec[0];
  auto mul = [&rec](vector<modint> v, vector<modint> w)
  {
    vector<modint> ans(2 * v.size());
    for (int j = 0; j < v.size(); j++)
    {
      for (int k = 0; k < v.size(); k++)
        ans[j + k] += v[j] * w[k];
    }
    for (int j = 2 * v.size() - 1; j >= v.size(); j--)
    {
      for (int k = 1; k <= v.size(); k++)
        ans[j - k] += ans[j] * rec[k - 1];
    }
    ans.resize(v.size());
    return ans;
  };
  while (n)
  {
    if (n & 1)
      s = mul(s, t);
    t = mul(t, t);
    n >>= 1;
  }
  modint ret = 0;
  for (int i = 0; i < m; i++)
    ret += s[i] * dp[i];
  return ret;
}
modint guess_nth_term(vector<modint> x, int n)
{
  if (n < x.size())
    return x[n];
  vector<modint> coef = berlekamp_massey(x); // coeficientes da recorrencia
  /*for (auto const &i : coef)
    cout << i.val << " ";
  cout << endl;*/
  if (coef.empty())
    return 0;
  return get_nth(coef, x, n);
}
signed main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  vector<modint> vals;
  vals.pb(0);
  vals.pb(1);
  for (int i = 2; i <= 200; i++)
    vals.pb(vals[vals.size() - 1] + vals[vals.size() - 2]);
  int n;
  cin >> n;
  cout << guess_nth_term(vals, n).val << endl;
  return 0;
}
// exemplo fibonacci
