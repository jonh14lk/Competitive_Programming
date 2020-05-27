#include <bits/stdc++.h>
using namespace std;

#define PI acos(-1)
#define int long long int
#define pb push_back
#define mp make_pair
#define pi pair<int, int>
#define fir first
#define sec second
#define MAXN 100001
#define MAXL 101
#define mod 998244353
#define INF 1000000001

struct edge
{
  int to, from, flow, capacity;
};

int n, m, source, destiny;
vector<edge> adj[MAXN];
queue<int> q;
int level[MAXN];
int ptr[MAXN];

void add_edge(int a, int b, int c)
{
  adj[a].pb({b, adj[b].size(), c, c});     //forward edge : c flow and c capacity
  adj[b].pb({a, adj[a].size() - 1, 0, 0}); //back edge : 0 flow and 0 capacity
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
  for (int p = ptr[u]; p < adj[u].size(); p++)
  {
    edge at = adj[u][p];
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
  int maxFlow = 0;
  while (bfs())
  {
    memset(ptr, 0, sizeof(ptr));
    while (1)
    {
      int flow = dfs(source, INF);
      if (flow == 0)
        break;
      maxFlow += flow;
    }
  }
  return maxFlow;
}
signed main()
{
  cin >> n >> m;
  for (int i = 0; i < n; i++)
  {
    int a, b, c;
    cin >> a >> b >> c;
    add_edge(a, b, c);
  }
  source = 0, destiny = n - 1;
  cout << dinic() << endl;
  return 0;
}
