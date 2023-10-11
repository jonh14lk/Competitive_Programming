#include <bits/stdc++.h>
using namespace std;

#define int long long int
#define endl '\n'
#define pb push_back
#define pi pair<int, int>
#define pii pair<int, pi>
#define fir first
#define sec second
#define MAXN 305
#define mod 998244353

const int inf = 1e18;
vector<pii> adj[305];

signed main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  int n, m;
  cin >> n >> m;
  for (int i = 0; i < m; i++)
  {
    int a, b, c;
    cin >> a >> b >> c;
    a--, b--;
    adj[a].pb({b, {i, c}});
    adj[b].pb({a, {i, c}});
  }
  vector<int> ans(m, inf);
  for (int iniv = 0; iniv < n; iniv++)
  {
    for (int b = 0; b < 9; b++)
    {
      for (int bitval = 0; bitval < 2; bitval++)
      {
        vector<bool> out(m, 0);
        for (auto const &v : adj[iniv])
        {
          if (((v.fir & (1 << b)) ? 1 : 0) == bitval)
            out[v.sec.fir] = 1;
        }
        vector<int> d(n, inf);
        vector<bool> vis(n, 0);
        d[iniv] = 0;
        while (1)
        {
          int v = -1;
          for (int j = 0; j < n; j++)
          {
            if (vis[j])
              continue;
            if (v == -1 || d[v] > d[j])
              v = j;
          }
          if (v == -1)
          {
            break;
          }
          vis[v] = 1;
          for (auto const &i : adj[v])
          {
            if (v == iniv && out[i.sec.fir])
              continue;
            if (d[i.fir] > d[v] + i.sec.sec)
              d[i.fir] = d[v] + i.sec.sec;
          }
        }
        for (auto const &v : adj[iniv])
        {
          if (out[v.sec.fir])
            ans[v.sec.fir] = min(ans[v.sec.fir], d[v.fir]);
        }
      }
    }
  }
  for (int i = 0; i < m; i++)
  {
    if (ans[i] == inf)
      ans[i] = -1;
    cout << ans[i] << endl;
  }
  return 0;
}