#include <bits/stdc++.h>
using namespace std;

#define int long long int
#define pb push_back
#define pi pair<int, int>
#define pii pair<pi, int>
#define fir first
#define sec second
#define MAXN 3001
#define INF 1e9

struct edge
{
  int to, from, flow, capacity, id;
};

int n, m, k, source, destiny;
vector<edge> adj[MAXN];
vector<pii> ar;
queue<int> q;
int level[MAXN];
int v[MAXN];
int ptr[MAXN];

void add_edge(int a, int b, int c)
{
  adj[a].pb({b, (int)adj[b].size(), c, c, 0});
  adj[b].pb({a, (int)adj[a].size() - 1, 0, 0, 0});
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
bool ok(int cc)
{
  int acc = 0;
  for (int i = 0; i <= n + m + 1; i++)
    adj[i].clear();
  for (int i = m + 1; i <= n + m; i++)
    acc += v[i], add_edge(i, destiny, v[i]);
  for (int i = 1; i <= m; i++)
    add_edge(source, i, v[i]);
  for (int i = 0; i < k; i++)
  {
    int a = ar[i].fir.fir, b = ar[i].fir.sec, c = ar[i].sec;
    if (c <= cc)
      add_edge(a, b, v[b]);
  }
  return dinic() == acc;
}
signed main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  cin >> n >> m >> k;
  source = 0, destiny = n + m + 1;
  for (int i = m + 1; i <= n + m; i++)
    cin >> v[i];
  for (int i = 1; i <= m; i++)
    cin >> v[i];
  for (int i = 0; i < k; i++)
  {
    int a, b, c;
    cin >> a >> b >> c;
    a += m;
    ar.pb({{b, a}, c});
  }
  int i = 0, f = INT_MAX, mid;
  while (i < f)
  {
    mid = (i + f) / 2;
    (ok(mid)) ? f = mid : i = mid + 1;
  }
  (i == INT_MAX) ? cout << -1 << endl : cout << i << endl;
  return 0;
}