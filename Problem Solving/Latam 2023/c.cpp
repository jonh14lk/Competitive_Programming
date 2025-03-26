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
#define pii pair<pi, int>
#define fir first
#define sec second
#define MAXN 100005
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

string s[55];
int color[3026];
vector<int> adj[3026];
int dx[] = {0, 0, 1, -1};
int dy[] = {1, -1, 0, 0};

signed main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  int n, m;
  cin >> n >> m;
  for (int i = 0; i < n; i++)
  {
    cin >> s[i];
  }
  auto get_id = [&](int i, int j)
  {
    return (i * m + j);
  };
  vector<vector<int>> by_color(2);
  vector<int> idd((n * m));
  for (int i = 0; i < n; i++)
  {
    for (int j = 0; j < m; j++)
    {
      if (s[i][j] == '.')
      {
        idd[get_id(i, j)] = by_color[(i + j) % 2].size();
        by_color[(i + j) % 2].pb(get_id(i, j));
        color[get_id(i, j)] = (i + j) % 2;
        for (int d = 0; d < 4; d++)
        {
          int x = i + dx[d];
          int y = j + dy[d];
          if (x >= 0 && x < n && y >= 0 && y < m && s[x][y] == '.')
            adj[get_id(i, j)].pb(get_id(x, y));
        }
      }
    }
  }
  int mx;
  {
    hopcroft_karp h(by_color[0].size(), by_color[1].size());
    for (auto const &x : by_color[color[0]])
    {
      for (auto const &y : adj[x])
        h.add_edge(idd[x], by_color[0].size() + idd[y]);
    }
    mx = h.run().size();
  }
  int ans = 0;
  auto check = [&](int i)
  {
    vector<bool> vis((n * m), 0);
    hopcroft_karp h(by_color[0].size(), by_color[1].size());
    for (auto const &x : by_color[color[0]])
    {
      for (auto const &y : adj[x])
      {
        if (x != i && y != i)
          h.add_edge(idd[x], by_color[0].size() + idd[y]);
      }
    }
    return (h.run().size() == mx);
  };
  for (int i = 0; i < n; i++)
  {
    for (int j = 0; j < m; j++)
    {
      if (s[i][j] == '.')
      {
        int curr_id = get_id(i, j);
        if (check(curr_id))
          ans++;
      }
    }
  }
  cout << ans << endl;
}