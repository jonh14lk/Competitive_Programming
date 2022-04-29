#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace std;
using namespace __gnu_pbds;

template <class T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

#define int long long int
#define endl '\n'
#define pbc push_back
#define pi pair<int, int>
#define pii pair<int, pi>
#define fir first
#define sec second
#define MAXN 3000001
#define mod 1000000007

struct modint
{
  int val;
  modint(int v = 0) { val = v % mod; }
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

modint f[MAXN];

void fat()
{
  f[0] = 1;
  for (int i = 1; i < MAXN; i++)
    f[i] = f[i - 1] * i;
}
modint ncr(int n, int k)
{
  modint d = f[k] * f[n - k];
  modint ans = f[n] / d;
  return ans;
}
void adapt(int &n, int &g, int &i, int &e)
{
  int tot = 2 * n;
  int dif = (g + i + e) - tot;
  i -= min(i, max(0ll, dif));
  dif = (g + i + e) - tot;
  e -= min(e, max(0ll, dif));
  dif = (g + i + e) - tot;
  g -= min(g, max(0ll, dif));
}
signed main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  int n, g, i, e;
  cin >> n >> g >> i >> e;
  adapt(n, g, i, e);
  if (n == 0)
  {
    cout << 0 << endl;
    return 0;
  }
  if (g >= 2 * n)
  {
    cout << g << endl;
    return 0;
  }
  fat();
  int lim = min(n, g / 2);
  modint ev = 0;
  modint tot = ncr(2 * n, g);
  double evv = 0.0;
  for (int a = 0; a <= lim; a++) // a pares com as duas cadeiras ocupadas por easygoing
  {
    int b = g - (2 * a); // b pares com apenas uma cadeira ocupada
    int c = n - (a + b); // c pares com nenhuma cadeira ocupada
    if (b < 0 || c < 0 || (a + b + c) != n)
      continue;
    // quantas maneiras tenho de escolher os a pares
    // depois quantas maneiras tenho de escolher os b pares
    modint waysa = ncr(n, a);
    modint waysb = ncr(n - a, b) * modint(modint(2).pow(b)); // pode sentar de um lado ou de outro
    modint ways = waysa * waysb;
    modint prob = ways / tot;
    // agora qual vai ser a happiness dessa configuracao
    int h = g;
    if (e <= b)
    {
      h += e;
      int rem = b - e;
      if (c >= i)
      {
        h += i;
      }
      else
      {
        h += c;
        int delta = i - c;
        delta -= rem;
        h -= max(0ll, min(c, delta));
      }
    }
    else
    {
      int dif = e - b;
      int rem = dif % 2;
      h += e;
      c -= ((dif / 2) + rem);
      if (rem)
      {
        h--;
        if (c >= i)
        {
          h += i;
        }
        else
        {
          h += c;
          int delta = i - c;
          delta -= rem;
          h -= max(0ll, min(c, delta));
          h++;
        }
      }
      else
      {
        if (c >= i)
        {
          h += i;
        }
        else
        {
          h += c;
          int delta = i - c;
          delta -= rem;
          h -= max(0ll, min(c, delta));
        }
      }
    }
    ev += (prob * h);
  }
  cout << ev.val << endl;
  return 0;
}