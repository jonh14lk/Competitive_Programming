#include <bits/stdc++.h>
using namespace std;

#define PI acos(-1)
#define int long long int
#define pb push_back
#define pi pair<int, int>
#define fir first
#define sec second
#define MAXN 502
#define mod 1000000007
#define INF 1e9

struct edge
{
  int to, from, flow, capacity, id;
};

int n, m, a, b, source, destiny;
vector<edge> adj[MAXN];
queue<int> q;
int level[MAXN];
int ptr[MAXN];

void add_edge(int a, int b, int c, int id)
{
  adj[a].pb({b, (int)adj[b].size(), c, c, id});
  adj[b].pb({a, (int)adj[a].size() - 1, 0, 0, id});
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
signed main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  cin >> n >> m;
  for (int i = 0; i < m; i++)
  {
    int a, b, c;
    cin >> a >> b >> c;
    a--, b--;
    add_edge(a, b, c, i);
  }
  source = 0, destiny = n - 1;
  cout << dinic() << endl;
  vector<int> ans(m);
  for (int i = 0; i < n; i++) // fluxo em cada aresta, na ordem da entrada
    for (auto const &j : adj[i])
      if (!j.capacity)
        ans[j.id] = j.flow;
  for (auto const &i : ans)
    cout << i << endl;
  return 0;
}
