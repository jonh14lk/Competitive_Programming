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
#define MAXN 3006
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
  vector<pi> run()
  {
    int cnt = 0;
    while (bfs())
      for (int u = 0; u < n; u++)
        if (match[u] == n + m && dfs(u))
          cnt++;
    vector<pi> ans;
    for (int v = n; v < n + m; v++)
      if (match[v] < n + m)
        ans.pb({match[v], v});
    return ans;
  }
};

int n;
vector<int> adj[MAXN];
vector<int> g[MAXN];
int repr[MAXN][2];
bool vis_edge[MAXN][MAXN];
int id[MAXN][MAXN];

struct dsu
{
  int tot;
  vector<int> parent;
  vector<int> sz;

  dsu() {}
  dsu(int n)
  {
    parent.resize(n);
    sz.resize(n);
    tot = n;
    for (int i = 0; i < n; i++)
    {
      parent[i] = i;
      sz[i] = 1;
    }
  }
  int find_set(int i)
  {
    return parent[i] = (parent[i] == i) ? i : find_set(parent[i]);
  }
  void make_set(int x, int y)
  {
    x = find_set(x), y = find_set(y);
    if (x != y)
    {
      if (sz[x] > sz[y])
        swap(x, y);
      parent[x] = y;
      sz[y] += sz[x];
      tot--;
    }
  }
};

signed main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  cin >> n;
  vector<string> s(n);
  for (int i = 0; i < n; i++)
  {
    cin >> s[i];
    repr[i][0] = i;
    repr[i][1] = n + i;
    for (int j = 0; j < n; j++)
    {
      if (s[i][j] == '1')
        adj[i].pb(j);
    }
    s[i][i] = '1';
  }
  dsu d(2 * n);
  int clique_id = 0;
  for (int i = 0; i < n; i++)
  {
    while (1)
    {
      if (!adj[i].size())
      {
        break;
      }
      int x = -1;
      for (auto const &j : adj[i])
      {
        if (!vis_edge[i][j])
        {
          x = j;
          break;
        }
      }
      if (x == -1)
      {
        break;
      }
      vector<int> on_clique;
      for (int j = 0; j < n; j++)
      {
        if (s[i][j] == '1' && s[x][j] == '1')
        {
          on_clique.pb(j);
        }
      }
      for (auto const &j : on_clique)
      {
        for (auto const &k : on_clique)
        {
          vis_edge[j][k] = 1;
          if (j != k)
            id[j][k] = clique_id;
        }
      }
      clique_id++;
    }
  }
  // montar um grafo de cliques e fazer um coloring com duas cores
  for (int i = 0; i < n; i++)
  {
    set<int> s;
    for (auto const &j : adj[i])
    {
      s.insert(id[i][j]);
    }
    if (s.size() == 2)
    {
      int a = (*s.begin());
      int b = (*s.rbegin());
      g[a].pb(b);
      g[b].pb(a);
    }
  }
  vector<int> c(clique_id, -1);
  queue<int> q;
  for (int st = 0; st < clique_id; st++)
  {
    if (c[st] == -1)
    {
      q.push(st);
      c[st] = 0;
      while (!q.empty())
      {
        int v = q.front();
        q.pop();
        for (int u : g[v])
        {
          if (c[u] == -1)
          {
            c[u] = c[v] ^ 1;
            q.push(u);
          }
        }
      }
    }
  }
  vector<bool> has(clique_id, 0);
  for (int i = 0; i < n; i++)
  {
    set<int> s;
    for (auto const &j : adj[i])
    {
      s.insert(id[i][j]);
    }
    for (auto const &cc : s)
    {
      if (!has[cc])
      {
        has[cc] = 1;
        for (auto const &j : adj[i])
        {
          if (id[i][j] == cc)
          {
            d.make_set(repr[i][c[cc]], repr[j][c[cc]]);
          }
        }
      }
    }
  }
  // checa se o grafo bipartido q eu achei tem como line graph o grafo do input
  for (int i = 0; i < n; i++)
  {
    for (int j = 0; j < n; j++)
    {
      if (i != j)
      {
        if (s[i][j] == '1')
        {
          assert(d.find_set(repr[i][0]) == d.find_set(repr[j][0]) ||
                 d.find_set(repr[i][1]) == d.find_set(repr[j][0]) ||
                 d.find_set(repr[i][0]) == d.find_set(repr[j][1]) ||
                 d.find_set(repr[i][1]) == d.find_set(repr[j][1]));
        }
        else
        {
          assert(d.find_set(repr[i][0]) != d.find_set(repr[j][0]) &&
                 d.find_set(repr[i][1]) != d.find_set(repr[j][0]) &&
                 d.find_set(repr[i][0]) != d.find_set(repr[j][1]) &&
                 d.find_set(repr[i][1]) != d.find_set(repr[j][1]));
        }
      }
    }
  }
  hopcroft_karp h(n, n);
  for (int i = 0; i < n; i++)
  {
    h.add_edge(d.find_set(repr[i][0]), d.find_set(repr[i][1]));
  }
  cout << h.run().size() << endl;
  return 0;
}
// da pra ver como um grafo que é um line graph de um grafo bipartido
// que eh um grafo que cada edge do grafo original vira um vertice no novo grafo
// e tem uma aresta entre dois vertices se no grafo original, as arestas compartilham um vertice

// o grafo bipartido eh tipo:
// de um lado temos os vertices que representam as cores de text
// e do outro lado os vertices que representam as cores de background
// tem um edge (i, j) se tem um modelo com a cor i de text e a cor j de background

// pensando em converter o grafo bipartido
// tenho que achar as cliques
// achando as cliques, da pra buildar