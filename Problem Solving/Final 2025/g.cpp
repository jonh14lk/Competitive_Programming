#include <bits/stdc++.h>
using namespace std;

#define int long long int
#define pb push_back
#define pi pair<int, int>
#define pii pair<int, pi>
#define fir first
#define sec second
#define MAXN 300005
#define mod 998244353

signed main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  int n, m, p, k;
  cin >> n >> m >> p >> k;
  vector<vector<int>> c(n, vector<int>(m));
  for (int i = 0; i < n; i++)
  {
    for (int j = 0; j < m; j++)
      cin >> c[i][j];
  }
  vector<vector<int>> r(n, vector<int>(m));
  for (int i = 0; i < n; i++)
  {
    for (int j = 0; j < m; j++)
      cin >> r[i][j];
  }
  vector<pair<pi, pi>> edges(p);
  for (int i = 0; i < p; i++)
  {
    int x1, y1, x2, y2;
    cin >> x1 >> y1 >> x2 >> y2;
    x1--, y1--, x2--, y2--;
    if (x1 > x2 || y1 > y2)
    {
      swap(x1, x2);
      swap(y1, y2);
    }
    edges[i] = {{x1, y1}, {x2, y2}};
  }
  sort(edges.begin(), edges.end());
  // regioes com 0 <= i <= n - 2, 0 <= j <= m - 2
  // regiao (i, j) pega os vertices (i, j) (i + 1, j), (i, j + 1), (i + 1, j + 1)
  int tot = (n - 1) * (m - 1) + 2;
  int src = (n - 1) * (m - 1);
  int sink = (n - 1) * (m - 1) + 1;
  auto id = [&](int i, int j) -> int
  {
    if (i >= (n - 1) || j < 0)
      return src;
    if (i < 0 || j >= (m - 1))
      return sink;
    return (i * (m - 1)) + j;
  };
  vector<vector<pii>> adj(tot);
  auto add_edge = [&](int a, int b, int c, int d, int e, int f)
  {
    adj[id(a, b)].pb({id(c, d), {e, f}});
    adj[id(c, d)].pb({id(a, b), {e, f}});
  };
  for (int i = 0; i < (n - 1); i++)
  {
    for (int j = 0; j < (m - 1); j++)
    {
      if (!binary_search(edges.begin(), edges.end(), make_pair(pi(i, j + 1), pi(i + 1, j + 1))))
        add_edge(i, j, i, j + 1, -1, -1);
      if (!binary_search(edges.begin(), edges.end(), make_pair(pi(i, j), pi(i + 1, j))))
        add_edge(i, j, i, j - 1, -1, -1);
      if (!binary_search(edges.begin(), edges.end(), make_pair(pi(i, j), pi(i, j + 1))))
        add_edge(i, j, i - 1, j, -1, -1);
      if (!binary_search(edges.begin(), edges.end(), make_pair(pi(i + 1, j), pi(i + 1, j + 1))))
        add_edge(i, j, i + 1, j, -1, -1);
    }
  }
  adj[src].pb({sink, {0, 0}});
  adj[src].pb({sink, {n - 1, m - 1}});
  for (int i = 0; i < (n - 1); i++)
  {
    for (int j = 0; j < (m - 1); j++)
    {
      add_edge(i, j, i - 1, j, i, j + 1);
      add_edge(i, j, i - 1, j + 1, i, j + 1);
      add_edge(i, j, i, j + 1, i, j + 1);
      add_edge(i, j, i, j + 1, i + 1, j + 1);
      add_edge(i, j, i + 1, j + 1, i + 1, j + 1);
      add_edge(i, j, i + 1, j, i + 1, j + 1);
      add_edge(i, j, i, j - 1, i + 1, j);
      add_edge(i, j, i + 1, j - 1, i + 1, j);
      add_edge(i, j, i + 1, j, i + 1, j);
      add_edge(i, j, i, j - 1, i, j);
      add_edge(i, j, i - 1, j - 1, i, j);
      add_edge(i, j, i - 1, j, i, j);
    }
  }
  for (int i = 0; i < tot; i++)
  {
    sort(adj[i].begin(), adj[i].end());
    adj[i].erase(unique(adj[i].begin(), adj[i].end()), adj[i].end());
  }
  auto cost = [&](int i, int j, int t) -> int
  {
    return (i == -1) ? 0 : c[i][j] + t * r[i][j];
  };
  auto f = [&](int tt)
  {
    vector<int> dist(tot, 1e18);
    vector<bool> vis(tot, 0);
    priority_queue<pi, vector<pi>, greater<pi>> pq;
    dist[src] = 0;
    pq.push({0, src});
    while (!pq.empty())
    {
      int x = pq.top().sec;
      pq.pop();
      if (vis[x])
        continue;
      vis[x] = 1;
      for (auto [i, j] : adj[x])
      {
        int c = cost(j.fir, j.sec, tt);
        if (dist[i] > dist[x] + c)
        {
          dist[i] = dist[x] + c;
          pq.push({dist[i], i});
        }
      }
    }
    return dist[sink];
  };
  int lo = 0, hi = k;
  while (lo < hi)
  {
    int mid = (lo + hi) >> 1;
    (f(mid) < f(mid + 1)) ? lo = mid + 1 : hi = mid;
  }
  cout << f(lo) << endl;
  return 0;
}