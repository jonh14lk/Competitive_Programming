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
  int dest, back, f, c, id;
};
struct push_relabel
{
  int n;
  vector<vector<edge>> g;
  vector<int> ec;
  vector<edge *> cur;
  vector<vector<int>> hs;
  vector<int> H;
  push_relabel(int sz) : g(sz), ec(sz), cur(sz), hs(2 * sz), H(sz) { n = sz; }
  void add_edge(int s, int t, int cap, int rcap, int id)
  {
    if (s == t)
      return;
    g[s].pb({t, (int)g[t].size(), 0, cap, id});
    g[t].pb({s, (int)g[s].size() - 1, 0, rcap, -1});
  }
  void add_flow(edge &e, int f)
  {
    edge &back = g[e.dest][e.back];
    if (!ec[e.dest] && f)
      hs[H[e.dest]].push_back(e.dest);
    e.f += f;
    e.c -= f;
    ec[e.dest] += f;
    back.f -= f;
    back.c += f;
    ec[back.dest] -= f;
  }
  int calc(int s, int t)
  {
    int v = g.size();
    H[s] = v;
    ec[t] = 1;
    vector<int> co(2 * v);
    co[0] = v - 1;
    for (int i = 0; i < v; i++)
      cur[i] = g[i].data();
    for (edge &e : g[s])
      add_flow(e, e.c);
    for (int hi = 0;;)
    {
      while (hs[hi].empty())
        if (!hi--)
          return -ec[s];
      int u = hs[hi].back();
      hs[hi].pop_back();
      while (ec[u] > 0)
      {
        if (cur[u] == g[u].data() + g[u].size())
        {
          H[u] = INF;
          for (edge &e : g[u])
            if (e.c && H[u] > H[e.dest] + 1)
              H[u] = H[e.dest] + 1, cur[u] = &e;
          if (++co[H[u]], !--co[hi] && hi < v)
            for (int i = 0; i < v; i++)
              if (hi < H[i] && H[i] < v)
                --co[H[i]], H[i] = v + 1;
          hi = H[u];
        }
        else if (cur[u]->c && H[u] == H[cur[u]->dest] + 1)
          add_flow(*cur[u], min(ec[u], cur[u]->c));
        else
          ++cur[u];
      }
    }
  }
  vector<int> flow_edges(int m) // fluxo em cada aresta
  {
    vector<int> ans(m);
    for (int i = 0; i < n; i++)
    {
      for (auto const &j : g[i])
      {
        if (j.id != -1)
          ans[j.id] = j.f;
      }
    }
    return ans;
  }
};
struct flow_with_demands
{
  push_relabel pr;
  vector<int> in, out;
  int n;

  flow_with_demands(int sz) : n(sz), pr(sz + 2), in(sz), out(sz) {}
  void add_edge(int u, int v, int cap, int dem, int id)
  {
    pr.add_edge(u, v, cap - dem, 0, id);
    out[u] += dem, in[v] += dem;
  }
  int run(int s, int t)
  {
    pr.add_edge(t, s, INF, 0, -1);
    for (int i = 0; i < n; i++)
    {
      pr.add_edge(n, i, in[i], 0, -1);
      pr.add_edge(i, n + 1, out[i], 0, -1);
    }
    return pr.calc(n, n + 1);
  }
  bool check() // todas as constraints foram satisfeitas?
  {
    for (auto const &i : pr.g[n])
    {
      if (i.c > 0)
        return 0;
    }
    return 1;
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
  for (int i = 0; i < h; i++)
  {
    for (int j = 0; j < w; j++)
    {
      if (v[i][j] != '1')
        s[(i + j) % 2].pb({i, j});
    }
  }
  for (int i = 0; i < 2; i++)
  {
    sort(s[i].begin(), s[i].end());
  }
  flow_with_demands mf(s[0].size() + s[1].size() + 2);
  int src = s[0].size() + s[1].size();
  int sink = s[0].size() + s[1].size() + 1;
  for (int x = 0; x < s[0].size(); x++)
  {
    int i = s[0][x].fir, j = s[0][x].sec;
    if (v[i][j] == '2')
      mf.add_edge(src, x, 1, 1, -1);
    else
      mf.add_edge(src, x, 1, 0, -1);
  }
  for (int x = 0; x < s[1].size(); x++)
  {
    int i = s[1][x].fir, j = s[1][x].sec;
    if (v[i][j] == '2')
      mf.add_edge(s[0].size() + x, sink, 1, 1, -1);
    else
      mf.add_edge(s[0].size() + x, sink, 1, 0, -1);
  }
  for (int x = 0; x < s[0].size(); x++)
  {
    for (int d = 0; d < 4; d++)
    {
      pi curr = {s[0][x].fir + dx[d], s[0][x].sec + dy[d]};
      if (binary_search(s[1].begin(), s[1].end(), curr))
      {
        int y = lower_bound(s[1].begin(), s[1].end(), curr) - s[1].begin();
        mf.add_edge(x, s[0].size() + y, 1, 0, -1);
      }
    }
  }
  mf.run(src, sink);
  // existe um jeito de passar fluxo que satisfaz todas as constraints?
  (mf.check()) ? cout << "Yes\n" : cout << "No\n";
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
// Maximum flow problem with minimum capacities, tambem conhecido como flow with demands
// ai da pra dale em resolver

// https://cp-algorithms.com/graph/flow_with_demands.html