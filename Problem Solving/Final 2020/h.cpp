#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace std;
using namespace __gnu_pbds;

template <class T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

#define int long long int
#define pb push_back
#define pi pair<int, int>
#define pii pair<int, pi>
#define fir first
#define sec second
#define MAXN 10005
#define mod 1000000007
#define INF 1e9

namespace max_flow
{
  struct edge
  {
    int to, from, flow, capacity, id;
  };

  int n, m, a, b, source, destiny;
  vector<edge> adj[MAXN];
  queue<int> q;
  int level[MAXN];
  int ptr[MAXN];

  void add_edge(int a, int b, int c)
  {
    adj[a].pb({b, (int)adj[b].size(), c, c});
    adj[b].pb({a, (int)adj[a].size() - 1, 0, 0});
  }
  bool bfs()
  {
    memset(level, -1, sizeof(level));
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
  int dinic()
  {
    int max_flow = 0;
    while (bfs())
    {
      memset(ptr, 0, sizeof(ptr));
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
}
signed main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  int n;
  cin >> n;
  max_flow::source = 0, max_flow::destiny = 1;
  for (int i = 1; i <= n; i++)
  {
    string s;
    cin >> s;
    int v = (i == 1) ? 0 : i;
    if (s != "*")
    {
      int k = stoi(s);
      for (int j = 0; j < k; j++)
      {
        int x;
        cin >> x;
        max_flow::add_edge(v, x, 1);
      }
    }
    else
    {
      int x;
      cin >> x;
      max_flow::add_edge(v, x, INF);
    }
  }
  int ans = max_flow::dinic();
  (ans == INF) ? cout << "*\n" : cout << ans + 1 << endl;
  return 0;
}