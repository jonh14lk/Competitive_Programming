#include <bits/stdc++.h>
using namespace std;

#define int long long int
#define MAXN 200005
#define pi pair<int, int>
#define pii pair<pi, int>
#define pb push_back
#define fir first
#define sec second

const int inf = 1e18;

int ans, qt;
vector<int> adj[MAXN];
int v[MAXN];

pi dfs(int s, int p, int dep)
{
  pi best = {inf, 0};
  if (v[s] == 1)
  {
    best = {dep, 1};
  }
  for (auto const &i : adj[s])
  {
    if (i != p)
    {
      pi at = dfs(i, s, dep + 1);
      int dist = at.fir + best.fir - (2 * dep);
      if (dist < ans)
      {
        ans = dist;
        qt = 0;
      }
      if (dist == ans)
      {
        qt += (at.sec * best.sec);
      }
      if (at.fir < best.fir)
      {
        best = at;
      }
      else if (at.fir == best.fir)
      {
        best.sec += at.sec;
      }
    }
  }
  return best;
}
signed main()
{
  ios::sync_with_stdio(0);
  cin.tie(0);
  int n;
  cin >> n;
  for (int i = 0; i < n; i++)
  {
    cin >> v[i];
  }
  for (int i = 1; i < n; i++)
  {
    int u, v;
    cin >> u >> v;
    u--, v--;
    adj[u].pb(v);
    adj[v].pb(u);
  }
  ans = inf;
  dfs(0, -1, 0);
  cout << ans << " " << qt << endl;
}
