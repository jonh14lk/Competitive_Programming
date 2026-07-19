#include <bits/stdc++.h>
using namespace std;

#define pb push_back
#define pi pair<int, int>
#define pii pair<int, pi>
#define fir first
#define sec second
#define MAXN 1000005
#define mod 998244353

// https://github.com/brunomaletta/Biblioteca/blob/master/Codigo/Grafos/minCostMaxFlow.cpp
// O(nm + f * m log n)
// no qual f eh o fluxo maximo
// se for um dag, da pra substituir o SPFA por uma DP pra nao pagar O(nm) no comeco
// ja q so eh preciso achar os valores dos caminhos mais curtos saindo da source
// cuidado pra nao ter ciclo negativo

const int INF = 1e9;

struct mcmf
{
  struct edge
  {
    int to, rev, flow, cap;
    bool res;
    int cost;
    edge() : to(0), rev(0), flow(0), cap(0), cost(0), res(false) {}
    edge(int to_, int rev_, int flow_, int cap_, int cost_, bool res_)
        : to(to_), rev(rev_), flow(flow_), cap(cap_), res(res_), cost(cost_) {}
  };

  vector<vector<edge>> g;
  vector<int> par_idx, par;
  int inf;
  vector<int> dist;

  mcmf(int n) : g(n), par_idx(n), par(n), inf(numeric_limits<int>::max() / 3) {}

  void add_edge(int u, int v, int w, int cost)
  { // de u pra v com cap w e custo cost
    edge a = edge(v, g[v].size(), 0, w, cost, false);
    edge b = edge(u, g[u].size(), 0, 0, -cost, true);

    g[u].push_back(a);
    g[v].push_back(b);
  }

  vector<int> spfa(int s)
  {
    // nao precisa se nao tiver custo negativo
    // serve apenas pra calcular os potenciais inicialmente
    deque<int> q;
    vector<bool> is_inside(g.size(), 0);
    dist = vector<int>(g.size(), inf);

    dist[s] = 0;
    q.push_back(s);
    is_inside[s] = true;

    while (!q.empty())
    {
      int v = q.front();
      q.pop_front();
      is_inside[v] = false;

      for (int i = 0; i < g[v].size(); i++)
      {
        auto [to, rev, flow, cap, res, cost] = g[v][i];
        if (flow < cap and dist[v] + cost < dist[to])
        {
          dist[to] = dist[v] + cost;

          if (is_inside[to])
            continue;
          if (!q.empty() and dist[to] > dist[q.front()])
            q.push_back(to);
          else
            q.push_front(to);
          is_inside[to] = true;
        }
      }
    }
    return dist;
  }
  bool dijkstra(int s, int t, vector<int> &pot)
  {
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> q;
    dist = vector<int>(g.size(), inf);
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

  pair<int, int> min_cost_flow(int s, int t, int flow = INF)
  {
    vector<int> pot(g.size(), 0);
    pot = spfa(s); // mudar algoritmo de caminho minimo aqui

    int f = 0;
    int ret = 0;
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