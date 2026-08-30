#include <bits/stdc++.h>
using namespace std;

#define int long long int
#define pb push_back
#define pi pair<int, int>
#define pii pair<int, pi>
#define fir first
#define sec second
#define MAXN 1001
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
  vector<int> mvc() // minimum vertex cover
  {
    vector<pi> ans = run();
    vector<bool> vis(n + m, 0);
    for (int i = 0; i < n; i++)
    {
      if (match[i] == n + m)
      {
        queue<int> q;
        q.push(i);
        while (!q.empty())
        {
          int x = q.front();
          q.pop();
          vis[x] = 1;
          for (auto const &y : adj[x])
          {
            if (!vis[y])
            {
              vis[y] = 1;
              q.push(match[y]);
            }
          }
        }
      }
    }
    vector<int> vc;
    for (int i = 0; i < n; i++)
    {
      if (!vis[i])
        vc.pb(i);
    }
    for (int i = n; i < n + m; i++)
    {
      if (vis[i])
        vc.pb(i);
    }
    return vc;
  }
  vector<pi> mec() // minimum edge cover
  {
    vector<pi> ans = run();
    for (int i = 0; i < n + m; i++)
    {
      if (match[i] == n + m && adj[i].size() > 0)
      {
        if (i < n)
          ans.pb({i, adj[i][0]});
        else
          ans.pb({adj[i][0], i});
      }
    }
    return ans;
  }
};
signed main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  int n, m, m2;
  cin >> n >> m >> m2;
  if (m != m2)
  {
    cout << "-1\n";
    return 0;
  }
  set<pi> s, t;
  vector<pi> aux;
  for (int i = 0; i < m; i++)
  {
    int u, v;
    cin >> u >> v;
    if (u > v)
      swap(u, v);
    aux.pb({u, v});
  }
  for (int i = 0; i < m; i++)
  {
    int u, v;
    cin >> u >> v;
    if (u > v)
      swap(u, v);
    t.insert({u, v});
  }
  for (auto [u, v] : aux)
  {
    if (t.find({u, v}) != t.end())
      t.erase({u, v});
    else
      s.insert({u, v});
  }
  vector<pi> a(s.begin(), s.end());
  vector<pi> b(t.begin(), t.end());
  assert(a.size() == b.size());
  hopcroft_karp h(a.size(), b.size());
  for (int i = 0; i < a.size(); i++)
  {
    for (int j = 0; j < b.size(); j++)
    {
      if (a[i].fir == b[j].fir || a[i].sec == b[j].fir || a[i].fir == b[j].sec || a[i].sec == b[j].sec)
        h.add_edge(i, a.size() + j);
    }
  }
  int matching = h.run().size(); // arestas que dao matching signfica que compartilham um endpoint, so preciso trocar um endpoint
  // as demais vou ter q trocar os dois endpoints, entao vou gastar 2 operacoes
  int ans = 2 * (a.size() - matching);
  ans += matching;
  cout << ans << endl;
  return 0;
}
