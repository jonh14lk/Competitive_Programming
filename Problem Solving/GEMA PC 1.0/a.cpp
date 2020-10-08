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

struct card
{
  int h, p, k;
  vector<int> atk;
};

struct edge
{
  int to, from, flow, capacity;
};

int n, a, b, source, destiny;
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
bool ok1(int f, vector<card> v)
{
  source = 0, destiny = 2 * n + 1;
  for (int i = 0; i <= 2 * n + 1; i++)
    adj[i].clear();
  for (int i = 1; i <= n; i++)
    add_edge(0, i, f * v[i].p);
  for (int i = 1; i <= n; i++)
    for (auto const &j : v[i].atk)
      add_edge(i, j, v[j].h);
  int sum = 0;
  for (int i = n + 1; i <= 2 * n; i++)
    add_edge(i, 2 * n + 1, v[i].h), sum += v[i].h;
  return (dinic() == sum);
}
bool ok2(int f, vector<card> v)
{
  source = 2 * n + 1, destiny = 0;
  for (int i = 0; i <= 2 * n + 1; i++)
    adj[i].clear();
  for (int i = n + 1; i <= 2 * n; i++)
    add_edge(2 * n + 1, i, f * v[i].p);
  for (int i = n + 1; i <= 2 * n; i++)
    for (auto const &j : v[i].atk)
      add_edge(i, j, v[j].h);
  int sum = 0;
  for (int i = 1; i <= n; i++)
    add_edge(i, 0, v[i].h), sum += v[i].h;
  return (dinic() == sum);
}
signed main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  cin >> n;
  vector<card> v(2 * n + 1);
  for (int i = 1; i <= n; i++)
  {
    cin >> v[i].h >> v[i].p >> v[i].k;
    for (int j = 0; j < v[i].k; j++)
    {
      int f;
      cin >> f;
      f++;
      v[i].atk.pb(n + f);
    }
  }
  for (int i = n + 1; i <= 2 * n; i++)
  {
    cin >> v[i].h >> v[i].p >> v[i].k;
    for (int j = 0; j < v[i].k; j++)
    {
      int f;
      cin >> f;
      f++;
      v[i].atk.pb(f);
    }
  }
  int entity = 1, x = 1, i = 0, f = 1000, m;
  while (i < f)
  {
    m = (i + f) >> 1;
    (ok1(m, v)) ? f = m : i = m + 1;
  }
  entity = i;
  i = 0, f = 1000, m;
  while (i < f)
  {
    m = (i + f) >> 1;
    (ok2(m, v)) ? f = m : i = m + 1;
  }
  x = i;
  (entity <= x) ? cout << "Entity wins in " << entity << " turns\n" : cout << "X wins in " << x << " turns\n";
  return 0;
}