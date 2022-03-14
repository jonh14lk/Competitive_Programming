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
#define pii pair<pi, int>
#define fir first
#define sec second
#define MAXN 100005
//#define mod 998244353

int n, m;
int b[11][101];
bool vis[11][101];
int ord[11][101];
int pos[11];

namespace crt
{
  vector<pi> eq;

  __int128 gcd(__int128 a, __int128 b, __int128 &x, __int128 &y)
  {
    if (b == 0)
    {
      x = 1, y = 0;
      return a;
    }
    __int128 x1, y1, d = gcd(b, a % b, x1, y1);
    x = y1, y = x1 - y1 * (a / b);
    return d;
  }
  pi crt()
  {
    __int128 a1 = eq[0].fir, m1 = eq[0].sec;
    a1 %= m1;
    for (int i = 1; i < eq.size(); i++)
    {
      __int128 a2 = eq[i].fir, m2 = eq[i].sec;
      __int128 g = __gcd(m1, m2);
      if (a1 % g != a2 % g)
        return {-1, -1};
      __int128 p, q;
      gcd(m1 / g, m2 / g, p, q);
      __int128 mod = m1 / g * m2;
      __int128 x = (a1 * (m2 / g) % mod * q % mod + a2 * (m1 / g) % mod * p % mod) % mod;
      a1 = x;
      if (a1 < 0)
        a1 += mod;
      m1 = mod;
    }
    return {a1, m1};
  }
}
signed main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  cin >> n >> m;
  for (int i = 0; i < n; i++)
  {
    cin >> pos[i];
    pos[i]--;
    for (int j = 0; j < m; j++)
    {
      cin >> b[i][j];
      b[i][j]--;
    }
  }
  for (int _ = 0; _ < 200; _++)
  {
    int x = pos[0];
    for (int i = 1; i < n; i++)
    {
      if (pos[i] != x)
      {
        x = -1;
        break;
      }
    }
    if (x != -1)
    {
      cout << x + 1 << " " << _ << endl;
      return 0;
    }
    for (int i = 0; i < n; i++)
    {
      pos[i] = b[i][pos[i]];
    }
  }
  // achar ciclos
  // fazer crt
  vector<vector<int>> c(n);
  for (int i = 0; i < n; i++)
  {
    int k = 0;
    while (!vis[i][pos[i]])
    {
      vis[i][pos[i]] = 1;
      ord[i][pos[i]] = k;
      c[i].pb(pos[i]);
      pos[i] = b[i][pos[i]];
      k++;
    }
  }
  pi ans = {-1, -1};
  for (int i = 0; i < m; i++)
  {
    bool can = 1;
    for (int j = 0; j < n; j++)
    {
      if (!vis[j][i])
      {
        can = 0;
        break;
      }
    }
    if (!can)
      continue;
    // crt
    // do tipo
    // x mod c[j].size() = ord[j][i]
    crt::eq.clear();
    for (int j = 0; j < n; j++)
    {
      crt::eq.pb({ord[j][i], c[j].size()});
    }
    pi curr = {crt::crt().fir, i + 1};
    if (curr.fir != -1)
    {
      if (ans.fir == -1)
        ans = curr;
      else
        ans = min(ans, curr);
    }
  }
  if (ans.fir == -1)
    cout << "*\n";
  else
    cout << ans.sec << " " << 200 + ans.fir << endl;
  return 0;
}