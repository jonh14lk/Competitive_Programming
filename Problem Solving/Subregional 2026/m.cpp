#include <bits/stdc++.h>
using namespace std;

#define int long long int
#define pb push_back
#define pi pair<int, int>
#define pii pair<int, pi>
#define fir first
#define sec second
#define MAXN 100005
#define mod 1000000007

struct edge
{
  int nxt, f, w;
};

int dist[MAXN][11];
bool vis[MAXN][11];

signed main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  int n, m, k;
  cin >> n >> m >> k;
  vector<vector<edge>> adj(n);
  for (int i = 0; i < m; i++)
  {
    int u, v, f, w;
    cin >> u >> v >> f >> w;
    u--, v--;
    adj[u].pb({v, f, w});
    adj[v].pb({u, f, w});
  }
  for (int i = 0; i < n; i++)
  {
    for (int j = 0; j <= k; j++)
      dist[i][j] = 1e18;
  }
  priority_queue<pii, vector<pii>, greater<pii>> pq;
  pq.push({0, {0, 0}});
  dist[0][0] = 0;
  while (!pq.empty())
  {
    auto [i, j] = pq.top().sec;
    pq.pop();
    if (vis[i][j])
      continue;
    vis[i][j] = 1;
    for (auto const &e : adj[i])
    {
      if (dist[e.nxt][j] > dist[i][j] + e.f)
      {
        dist[e.nxt][j] = dist[i][j] + e.f;
        pq.push({dist[e.nxt][j], {e.nxt, j}});
      }
      if ((j + 1) <= k && e.w != -1 && dist[e.nxt][j + 1] > dist[i][j] + e.w)
      {
        dist[e.nxt][j + 1] = dist[i][j] + e.w;
        pq.push({dist[e.nxt][j + 1], {e.nxt, j + 1}});
      }
    }
  }
  int ans = 1e18;
  for (int j = 0; j <= k; j++)
    ans = min(ans, dist[n - 1][j]);
  cout << ans << endl;
  return 0;
}