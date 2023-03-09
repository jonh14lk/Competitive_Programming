#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace std;
using namespace __gnu_pbds;

template <class T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

#define int long long int
#define endl '\n'
#define pb push_back
#define pi pair<int, int>
#define pii pair<int, pi>
#define fir first
#define sec second
#define MAXN 500001
#define mod 1000000007
#define INF 1e9

struct edge
{
  int to, from, flow, capacity;
};
struct dinic
{
  int n, src, sink;
  vector<vector<edge>> adj;
  vector<int> level;
  vector<int> ptr;

  dinic(int sz)
  {
    n = sz;
    adj.resize(n);
    level.resize(n);
    ptr.resize(n);
  }
  void add_edge(int a, int b, int c)
  {
    adj[a].pb({b, (int)adj[b].size(), c, c});
    adj[b].pb({a, (int)adj[a].size() - 1, 0, 0});
  }
  bool bfs()
  {
    level.assign(n, -1);
    level[src] = 0;
    queue<int> q;
    q.push(src);
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
    return level[sink] != -1;
  }
  int dfs(int u, int flow)
  {
    if (u == sink || flow == 0)
      return flow;
    for (int &p = ptr[u]; p < adj[u].size(); p++)
    {
      edge &at = adj[u][p];
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
  int run()
  {
    int max_flow = 0;
    while (bfs())
    {
      ptr.assign(n, 0);
      while (1)
      {
        int flow = dfs(src, INF);
        if (flow == 0)
          break;
        max_flow += flow;
      }
    }
    return max_flow;
  }
  vector<pii> cut_edges() // arestas do corte minimo
  {
    bfs();
    vector<pii> ans;
    for (int i = 0; i < n; i++)
    {
      for (auto const &j : adj[i])
      {
        if (level[i] != -1 && level[j.to] == -1 && j.capacity > 0)
          ans.pb({j.capacity, {i, j.to}});
      }
    }
    return ans;
  }
};

int dx[] = {1, -1, 0, 0};
int dy[] = {0, 0, 1, -1};

signed main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  int h, w;
  cin >> h >> w;
  vector<string> v(h);
  for (int i = 0; i < h; i++)
  {
    cin >> v[i];
  }
  vector<pi> s[2];
  int cnt = 0;
  for (int i = 0; i < h; i++)
  {
    for (int j = 0; j < w; j++)
    {
      if (v[i][j] != '1')
        s[(i + j) % 2].pb({i, j});
      else if (v[i][j] == '2')
        cnt++;
    }
  }
  for (int i = 0; i < 2; i++)
  {
    sort(s[i].begin(), s[i].end());
  }
  int sz = s[0].size() + s[1].size() + 4;
  int src = s[0].size() + s[1].size();
  int src1 = s[0].size() + s[1].size() + 1;
  int sink = s[0].size() + s[1].size() + 2;
  int sink1 = s[0].size() + s[1].size() + 3;
  dinic d(sz);
  auto add_edge = [&](int a, int b, int r) // a quantidade de fluxo na aresta tem que ser <= r
  {
    d.add_edge(a, b, r);
  };
  auto add_edge2 = [&](int a, int b, int l, int r) // a quantidade de fluxo na aresta tem que estar em [l, r]
  {
    d.add_edge(a, b, r - l);
    d.add_edge(src1, b, l);
    d.add_edge(a, sink1, l);
  };
  for (int x = 0; x < s[0].size(); x++)
  {
    int i = s[0][x].fir, j = s[0][x].sec;
    if (v[i][j] == '2')
      add_edge2(src, x, 1, 1);
    else
      add_edge(src, x, 1);
  }
  for (int x = 0; x < s[1].size(); x++)
  {
    int i = s[1][x].fir, j = s[1][x].sec;
    if (v[i][j] == '2')
      add_edge2(s[0].size() + x, sink, 1, 1);
    else
      add_edge(s[0].size() + x, sink, 1);
  }
  for (int x = 0; x < s[0].size(); x++)
  {
    for (int d = 0; d < 4; d++)
    {
      pi curr = {s[0][x].fir + dx[d], s[0][x].sec + dy[d]};
      if (binary_search(s[1].begin(), s[1].end(), curr))
      {
        int y = lower_bound(s[1].begin(), s[1].end(), curr) - s[1].begin();
        add_edge(x, s[0].size() + y, 1);
      }
    }
  }
  // preciso tentar passar o fluxo desses 4 jeitos, e na ordem
  d.src = src1, d.sink = sink1;
  int i = d.run();
  d.src = src1, d.sink = sink;
  int j = d.run();
  d.src = src, d.sink = sink1;
  int k = d.run();
  d.src = src, d.sink = sink;
  int l = d.run();
  bool ok = 1;
  // pra poder checar se existe um jeito de passar fluxo
  // que satisfaz todas as constraints
  for (int i = 0; i < sz; i++)
  {
    for (auto const &j : d.adj[i])
    {
      if (i == src1 || j.to == sink1)
        ok &= (j.flow == 0);
    }
  }
  // e pra uma aresta com a restricao de [l, r]
  // se eu olhar quanto de fluxo foi passado na aresta com capacidade r - l que foi criada pra ela
  // ai tenho que foi passado l + (essa quantidade)
  (ok) ? cout << "Yes\n" : cout << "No\n";
  return 0;
}
// problema exemplo
// https://atcoder.jp/contests/abc285/tasks/abc285_g

// as celulas com 1 eu posso ignorar
// agr pras celulas com 2, eu preciso achar um matching dela com alguem
// so considerando os 2 e as ?

// entao a missao vira achar um matching (nao necessariamente maximo)
// mas que englobe todos os 2
// pode ter 2 de um lado e pode ter 2 do outro

// e se eu pudesse adicionar a seguinte constraint para algumas arestas:
// a quantidade de fluxo passada naquela aresta tem que ser entre [l, r]
// Maximum flow problem with minimum capacities
// ai da pra dale em resolver
