#include <bits/stdc++.h>
using namespace std;

#define int long long int
#define mod 1000000007
#define MAXN 100005
#define pi pair<int, int>
#define pii pair<int, pi>
#define fir first
#define sec second
#define pb push_back
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
  vector<int> solve()
  {
    vector<pi> ans = run();
    vector<bool> vis(n + m, 0);
    vector<bool> can_remove(n + m, 0);
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
          can_remove[x] = 1;
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
    vis = vector<bool>(n + m, 0);
    for (int i = n; i < n + m; i++)
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
          can_remove[x] = 1;
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
    vector<int> resp;
    for (int i = 0; i < n + m; i++)
    {
      if (can_remove[i])
        resp.pb(i);
    }
    return resp;
  }
};

int dx[] = {-1, 1, 0, 0};
int dy[] = {0, 0, 1, -1};

signed main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  int n;
  cin >> n;
  vector<pi> v(n);
  vector<int> sz(2, 0);
  map<pi, int> mp;
  map<int, pi> rev;
  for (int i = 0; i < n; i++)
  {
    cin >> v[i].fir >> v[i].sec;
    int id = sz[abs(v[i].fir + v[i].sec) % 2]++;
    mp[v[i]] = id;
  }
  for (int i = 0; i < n; i++)
  {
    if (abs(v[i].fir + v[i].sec) % 2)
    {
      mp[v[i]] += sz[0];
    }
    rev[mp[v[i]]] = v[i];
  }
  vector<pi> edges;
  for (auto [i, j] : v)
  {
    if (!(abs(i + j) % 2))
    {
      for (int dir = 0; dir < 4; dir++)
      {
        int x = i + dx[dir];
        int y = j + dy[dir];
        if (mp.find({x, y}) != mp.end())
        {
          edges.pb({mp[{i, j}], mp[{x, y}]});
        }
      }
    }
  }
  hopcroft_karp h(sz[0], sz[1]);
  for (auto [x, y] : edges)
  {
    h.add_edge(x, y);
  }
  vector<int> ans = h.solve();
  cout << ans.size() << endl;
  vector<pi> sorted;
  for (auto const &i : ans)
  {
    sorted.pb(rev[i]);
  }
  sort(sorted.begin(), sorted.end());
  for (auto [x, y] : sorted)
  {
    cout << x << " " << y << endl;
  }
}
// https://codeforces.com/group/TFrGcBYYxs/contest/583964/problem/E
// https://codeforces.com/gym/105053/problem/C
// https://codeforces.com/group/TFrGcBYYxs/contest/584239/problem/B

// dado um grafo bipartido
// basicamente responde o seguinte problema para cada vertice v:
// apos remover v do grafo, o tamanho do max matching continua o mesmo ou diminui em um?