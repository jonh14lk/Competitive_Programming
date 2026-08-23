#include <bits/stdc++.h>
using namespace std;

#define pb push_back
#define pi pair<int, int>
#define pii pair<int, pi>
#define fir first
#define sec second
#define MAXN 1000005
#define mod 998244353

struct pass
{
  int l, r;
  long long a;
};

const int INF = 1e9;

struct mcmf
{
  struct edge
  {
    int to, rev, flow, cap;
    bool res;
    long long cost;
    edge() : to(0), rev(0), flow(0), cap(0), cost(0), res(false) {}
    edge(int to_, int rev_, int flow_, int cap_, long long cost_, bool res_)
        : to(to_), rev(rev_), flow(flow_), cap(cap_), res(res_), cost(cost_) {}
  };

  vector<vector<edge>> g;
  vector<int> par_idx, par;
  long long inf;
  vector<long long> dist;

  mcmf(int n) : g(n), par_idx(n), par(n), inf(numeric_limits<long long>::max() / 3) {}

  void add_edge(int u, int v, int w, long long cost)
  { // de u pra v com cap w e custo cost
    edge a = edge(v, g[v].size(), 0, w, cost, false);
    edge b = edge(u, g[u].size(), 0, 0, -cost, true);

    g[u].push_back(a);
    g[v].push_back(b);
  }

  vector<long long> initial_potentials(int s)
  { // O(N+M) pq é DAG
    dist = vector<long long>(g.size(), inf);
    dist[s] = 0;

    for (int i = 0; i < g[s].size(); i++)
    {
      auto [to, rev, flow, cap, res, cost] = g[s][i];
      if (flow < cap)
        dist[to] = min(dist[to], dist[s] + cost);
    }

    for (int v = 0; v < g.size(); v++)
    {
      for (int i = 0; i < g[v].size(); i++)
      {
        auto [to, rev, flow, cap, res, cost] = g[v][i];
        if (flow < cap and to > v and dist[v] + cost < dist[to])
          dist[to] = dist[v] + cost;
      }
    }
    return dist;
  }
  bool dijkstra(int s, int t, vector<long long> &pot)
  {
    priority_queue<pair<long long, int>, vector<pair<long long, int>>, greater<>> q;
    dist = vector<long long>(g.size(), inf);
    dist[s] = 0;
    q.emplace(0, s);
    while (q.size())
    {
      auto [d, v] = q.top();
      q.pop();
      if (dist[v] < d)
        continue;
      for (int i = 0; i < g[v].size(); i++)
      {
        auto [to, rev, flow, cap, res, cost] = g[v][i];
        cost += pot[v] - pot[to];
        if (flow < cap and dist[v] + cost < dist[to])
        {
          dist[to] = dist[v] + cost;
          q.emplace(dist[to], to);
          par_idx[to] = i, par[to] = v;
        }
      }
    }
    return dist[t] < inf;
  }

  pair<int, long long> min_cost_flow(int s, int t, int flow = INF)
  {
    vector<long long> pot(g.size(), 0);
    pot = initial_potentials(s);

    int f = 0;
    long long ret = 0;
    while (f < flow and dijkstra(s, t, pot))
    {
      for (int i = 0; i < g.size(); i++)
        if (dist[i] < inf)
          pot[i] += dist[i];

      int mn_flow = flow - f, u = t;
      while (u != s)
      {
        mn_flow = min(mn_flow,
                      g[par[u]][par_idx[u]].cap - g[par[u]][par_idx[u]].flow);
        u = par[u];
      }

      ret += pot[t] * mn_flow;

      u = t;
      while (u != s)
      {
        g[par[u]][par_idx[u]].flow += mn_flow;
        g[u][g[par[u]][par_idx[u]].rev].flow -= mn_flow;
        u = par[u];
      }

      f += mn_flow;
    }

    return make_pair(f, ret);
  }

  // Opcional: retorna as arestas originais por onde passa flow = cap
  vector<pair<int, int>> recover()
  {
    vector<pair<int, int>> used;
    for (int i = 0; i < g.size(); i++)
      for (edge e : g[i])
        if (e.flow == e.cap && !e.res)
          used.push_back({i, e.to});
    return used;
  }
};
signed main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  int n, m, c;
  cin >> n >> m >> c;
  mcmf mcf(m + 2);
  mcf.add_edge(m, 0, c, 0);
  mcf.add_edge(m - 1, m + 1, c, 0);
  for (int i = 0; (i + 1) < m; i++)
  {
    mcf.add_edge(i, i + 1, c, 0);
  }
  vector<pass> v(n);
  for (int i = 0; i < n; i++)
  {
    cin >> v[i].l >> v[i].r >> v[i].a;
    v[i].l--, v[i].r--;
    mcf.add_edge(v[i].l, v[i].r, 1, -v[i].a);
  }
  cout << -mcf.min_cost_flow(m, m + 1).sec << endl;
  return 0;
}