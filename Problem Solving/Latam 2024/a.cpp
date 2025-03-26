#include <bits/stdc++.h>
using namespace std;

// #define int long long int
#define pb push_back
#define MAXN 5005
#define pi pair<int, int>
#define fir first
#define sec second

bool ok[5005][5005];
bool vis[5005][5005];
vector<pair<int, char>> adj[5005];
vector<pair<int, char>> adj2[5005];
pair<pi, char> edges[5005];

signed main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  int n, m;
  cin >> n >> m;
  for (int i = 0; i < m; i++)
  {
    int u, v;
    char c;
    cin >> u >> v >> c;
    u--, v--;
    adj[u].pb({v, c});
    adj2[v].pb({u, c});
    edges[i] = {{u, v}, c};
  }
  queue<pi> q;
  for (auto const &i : edges)
  {
    if (!vis[i.fir.fir][i.fir.sec])
    {
      vis[i.fir.fir][i.fir.sec] = 1;
      q.push({i.fir.fir, i.fir.sec});
    }
  }
  for (int i = 0; i < n; i++)
  {
    if (!vis[i][i])
    {
      vis[i][i] = 1;
      q.push({i, i});
    }
  }
  while (!q.empty())
  {
    auto [a, b] = q.front();
    q.pop();
    for (auto const &i : adj2[a])
    {
      for (auto const &j : adj[b])
      {
        if (i.sec == j.sec && !vis[i.fir][j.fir])
        {
          vis[i.fir][j.fir] = 1;
          q.push({i.fir, j.fir});
        }
      }
    }
  }
  int ans = 0;
  for (int i = 0; i < n; i++)
  {
    for (int j = 0; j < n; j++)
      if (i != j && vis[i][j])
        ans++;
  }
  cout << ans << endl;
  return 0;
}