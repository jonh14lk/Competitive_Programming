#include <bits/stdc++.h>
using namespace std;

#define int long long int
#define pb push_back
#define pi pair<int, int>
#define pii pair<int, pi>
#define fir first
#define sec second
#define MAXN 200005
#define mod 998244353

struct euler_tour
{
  int n, m, odd;
  vector<vector<pi>> adj;
  vector<int> path;
  vector<bool> vis;

  euler_tour(int _n, vector<pi> &edges) // recebe um grafo undirected, numero de vertices e as arestas
  {
    n = _n;
    m = edges.size();
    path.clear();
    adj.resize(n);
    vis.assign(m, false);
    for (int i = 0; i < m; i++)
    {
      adj[edges[i].fir].pb({edges[i].sec, i});
      adj[edges[i].sec].pb({edges[i].fir, i});
    }
    odd = 0;
    for (int i = 0; i < n; i++)
    {
      odd += (adj[i].size() % 2);
    }
  }
  void dfs(int s)
  {
    while (adj[s].size() > 0)
    {
      auto v = adj[s].back();
      adj[s].pop_back();
      if (!vis[v.sec])
      {
        vis[v.sec] = 1;
        dfs(v.fir);
      }
    }
    path.pb(s);
  }
  pair<bool, vector<int>> find_cycle(int source) // ve se tem caminho ciclo começando em source e terminando nele mesmo
  {
    if (odd != 0)
      return {false, {}};
    dfs(source);
    if (path.size() != (m + 1) || path[0] != source || path.back() != source)
      return {false, {}};
    return {true, path};
  }
  pair<bool, vector<int>> find_path(int source, int dest) // ve se tem caminho euleriano de source ate dest
  {
    if (odd != 2)
      return {false, {}};
    if (adj[source].size() % 2 == 0 || adj[dest].size() % 2 == 0)
      return {false, {}};
    dfs(source);
    reverse(path.begin(), path.end());
    if (path.size() != (m + 1) || path[0] != source || path.back() != dest)
      return {false, {}};
    return {true, path};
  }
  pair<bool, vector<int>> find_euler(int source, int dest)
  {
    if (source == dest)
      return find_cycle(source);
    return find_path(source, dest);
  }
};
signed main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  int n, m;
  cin >> n >> m;
  vector<pi> edges(m);
  for (int i = 0; i < m; i++)
  {
    int a, b;
    cin >> a >> b;
    a--, b--;
    edges[i] = {a, b};
  }
  euler_tour et(n, edges);
  auto [exists, path] = et.find_euler(0, 0);
  if (exists)
  {
    for (auto const &i : path)
      cout << i + 1 << " ";
    cout << endl;
  }
  else
  {
    cout << "IMPOSSIBLE\n";
  }
  return 0;
}
// caminho euleriano em um grafo
// passa por todas as arestas apenas uma unica vez e percorre todas elas
// condição de existencia:
// todos os vértices possuem grau par (ciclo euleriano) começa e acaba no mesmo vértice
// ou
// apenas 2 vértices possuem grau impar, todos os outros possuem grau par ou == 0.
// começa num vertice de grau impar e termina num vértice de grau impar nesse caso.

// testado em:
// https://cses.fi/problemset/task/1691/
// https://codeforces.com/gym/106178/problem/A
