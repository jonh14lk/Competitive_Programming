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
#define MAXN 1005
#define mod 1000000007
#define INF 1e9

struct hopcroft_karp
{
  vector<int> match;
  vector<int> dist;
  vector<vector<int>> adj;
  int n, m, t;

  hopcroft_karp(int a, int b)
  {
    n = a, m = b;
    t = n + m + 1;
    match.assign(t, n + m);
    dist.assign(t, 0);
    adj.assign(t, vector<int>{});
  }
  void add_edge(int u, int v)
  {
    adj[u].pb(v);
    adj[v].pb(u);
  }
  bool bfs()
  {
    queue<int> q;
    for (int u = 0; u < n; u++)
    {
      if (match[u] == n + m)
        dist[u] = 0, q.push(u);
      else
        dist[u] = INF;
    }
    dist[n + m] = INF;
    while (!q.empty())
    {
      int u = q.front();
      q.pop();
      if (dist[u] < dist[n + m])
      {
        for (auto const &v : adj[u])
        {
          if (dist[match[v]] == INF)
          {
            dist[match[v]] = dist[u] + 1;
            q.push(match[v]);
          }
        }
      }
    }
    return dist[n + m] < INF;
  }
  bool dfs(int u)
  {
    if (u < n + m)
    {
      for (auto const &v : adj[u])
      {
        if (dist[match[v]] == dist[u] + 1 && dfs(match[v]))
        {
          match[v] = u;
          match[u] = v;
          return true;
        }
      }
      dist[u] = INF;
      return false;
    }
    return true;
  }
  int run()
  {
    int cnt = 0;
    while (bfs())
    {
      for (int u = 0; u < n; u++)
        if (match[u] == n + m && dfs(u))
          cnt++;
    }
    return cnt;
  }
};

int d[101];
int d2[101];
bool vis[101][101][101][101];
bool dp[101][101][101][101];
vector<int> adj[101];
vector<int> adj2[101];

bool dfs(int u, int v, int pu, int pv)
{
  if (vis[u][v][pu][pv])
    return dp[u][v][pu][pv];
  vector<pi> uu, vv;
  for (auto const &i : adj[u])
  {
    if (i != pu)
      uu.pb({d[i], i});
  }
  for (auto const &i : adj2[v])
  {
    if (i != pv)
      vv.pb({d2[i], i});
  }
  int szu = uu.size(), szv = vv.size();
  hopcroft_karp h(szu, szv);
  for (int i = 0; i < szu; i++)
  {
    for (int j = 0; j < szv; j++)
    {
      if (dfs(uu[i].sec, vv[j].sec, u, v))
        h.add_edge(i, szu + j);
    }
  }
  vis[u][v][pu][pv] = 1;
  return dp[u][v][pu][pv] = (h.run() == szv);
}
signed main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  int n;
  cin >> n;
  for (int i = 1; i < n; i++)
  {
    int a, b;
    cin >> a >> b;
    a--, b--;
    adj[a].pb(b);
    adj[b].pb(a);
    d[a]++;
    d[b]++;
  }
  int m;
  cin >> m;
  for (int i = 1; i < m; i++)
  {
    int a, b;
    cin >> a >> b;
    a--, b--;
    adj2[a].pb(b);
    adj2[b].pb(a);
    d2[a]++;
    d2[b]++;
  }
  bool ok = 0;
  for (int i = 0; i < n; i++)
  {
    for (int j = 0; j < m; j++)
      ok |= dfs(i, j, 100, 100);
  }
  (ok) ? cout << "Y\n" : cout << "N\n";
}
// beautiful problem