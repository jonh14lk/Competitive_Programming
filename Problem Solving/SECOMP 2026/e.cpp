
#include <bits/stdc++.h>
using namespace std;

#define int long long int
#define inf 1e18

struct aresta
{
  int to, cost;
};

int n, m;
vector<aresta> graph[100005];
int dist[100005];
bool visited[100005];

int read_date()
{
  int a, b;
  char c;
  cin >> a >> c >> b;
  return a * 60 + b;
}
int dijkstra()
{
  for (int i = 0; i < n; i++)
  {
    dist[i] = inf;
  }
  multiset<pair<int, int>> s;
  s.insert({0, 0});
  dist[0] = 0;
  while (!s.empty())
  {
    int vertex = (*s.begin()).second;
    s.erase(s.begin());
    if (visited[vertex])
    {
      continue;
    }
    visited[vertex] = true;
    for (auto [to, cost] : graph[vertex])
    {
      if (dist[to] > dist[vertex] + cost)
      {
        dist[to] = dist[vertex] + cost;
        s.insert({dist[to], to});
      }
    }
  }
  return dist[n - 1];
}
signed main()
{
  int start = read_date();
  int end = read_date();
  cin >> n >> m;
  for (int i = 0; i < m; i++)
  {
    int u, v, t;
    cin >> u >> v >> t;
    u--, v--;
    graph[u].push_back({v, t});
    graph[v].push_back({u, t});
  }
  int min_dist = dijkstra();
  if (min_dist <= (end - start))
  {
    cout << "SIM\n";
  }
  else
  {
    cout << "NAO\n";
  }
}