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
#define MAXN 500001
#define mod 1000000007

const int INF = 1e9;
const int INFC = 5 * 1e6;

struct edge
{
  int to, from, flow, capacity;
};
struct dinic
{
  int source, destiny;
  vector<vector<edge>> adj;
  queue<int> q;
  vector<int> level;
  vector<int> ptr;

  dinic(int n)
  {
    adj.resize(n);
    level.resize(n);
    ptr.resize(n);
  }
  void add_edge(int a, int b, int c)
  {
    adj[a].pb({b, (int)adj[b].size(), c, c});
    adj[b].pb({a, (int)adj[a].size() - 1, 0, 0});
  }
  bool bfs()
  {
    fill(level.begin(), level.end(), -1);
    level[source] = 0;
    q.push(source);
    while (!q.empty())
    {
      int u = q.front();
      q.pop();
      for (auto at : adj[u])
      {
        if (at.flow && level[at.to] == -1)
        {
          q.push(at.to);
          level[at.to] = level[u] + 1;
        }
      }
    }
    return level[destiny] != -1;
  }
  int dfs(int u, int flow)
  {
    if (u == destiny || flow == 0)
      return flow;
    for (int &p = ptr[u]; p < adj[u].size(); p++)
    {
      edge &at = adj[u][p];
      if (at.flow && level[u] == level[at.to] - 1)
      {
        int kappa = dfs(at.to, min(flow, at.flow));
        at.flow -= kappa;
        adj[at.to][at.from].flow += kappa;
        if (kappa != 0)
          return kappa;
      }
    }
    return 0;
  }
  int max_flow()
  {
    int max_flow = 0;
    while (bfs())
    {
      fill(ptr.begin(), ptr.end(), 0);
      while (1)
      {
        int flow = dfs(source, INF);
        if (flow == 0)
          break;
        max_flow += flow;
      }
    }
    return max_flow;
  }
};
signed main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  int n, m, k, c;
  cin >> n >> m >> k >> c;
  int v[n][m];
  for (int i = 0; i < n; i++)
  {
    for (int j = 0; j < m; j++)
      cin >> v[i][j];
  }
  int sz = (m * n) + 2;
  dinic d(sz);
  d.source = (n * m), d.destiny = (n * m) + 1;
  for (int i = 0; i < n; i++)
  {
    int last = d.source;
    for (int j = 0; j < m; j++)
    {
      int cost = INFC - v[i][j];
      int u = (i * m) + j;
      d.add_edge(last, u, cost);
      last = u;
    }
    d.add_edge(last, d.destiny, INF);
  }
  for (int i = 0; i < k; i++)
  {
    int a, b;
    cin >> a >> b;
    a--, b--;
    for (int j = 0; j < m; j++)
    {
      int u = (a * m) + j;
      int v = (b * m) + j;
      d.add_edge(u, v, c);
      d.add_edge(v, u, c);
    }
  }
  int mx = INFC * n;
  int ans = mx - d.max_flow();
  cout << ans << endl;
  return 0;
}
