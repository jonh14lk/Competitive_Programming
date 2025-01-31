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
#define MAXN 300005
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
signed main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  int n;
  cin >> n;
  vector<pi> v(n);
  vector<int> x_vals, y_vals;
  for (int i = 0; i < n; i++)
  {
    cin >> v[i].fir >> v[i].sec;
    x_vals.pb(v[i].fir);
    y_vals.pb(v[i].sec);
  }
  sort(x_vals.begin(), x_vals.end());
  sort(y_vals.begin(), y_vals.end());
  x_vals.erase(unique(x_vals.begin(), x_vals.end()), x_vals.end());
  y_vals.erase(unique(y_vals.begin(), y_vals.end()), y_vals.end());
  int xx = x_vals.size();
  int yy = y_vals.size();
  vector<int> cntx(xx, 0);
  vector<int> cnty(yy, 0);
  for (int i = 0; i < n; i++)
  {
    v[i].fir = lower_bound(x_vals.begin(), x_vals.end(), v[i].fir) - x_vals.begin();
    v[i].sec = lower_bound(y_vals.begin(), y_vals.end(), v[i].sec) - y_vals.begin();
    cntx[v[i].fir]++;
    cnty[v[i].sec]++;
  }
  flow_with_demands mf(xx + yy + 2);
  int src = xx + yy;
  int sink = xx + yy + 1;
  int edge_id = 0;
  for (int i = 0; i < xx; i++)
  {
    int half = cntx[i] / 2;
    int can_pass = cntx[i] - half;
    mf.add_edge(src, i, can_pass, half, edge_id++);
  }
  for (int i = 0; i < yy; i++)
  {
    int half = cnty[i] / 2;
    int can_pass = cnty[i] - half;
    mf.add_edge(xx + i, sink, can_pass, half, edge_id++);
  }
  vector<int> middle_edges(n);
  for (int i = 0; i < n; i++)
  {
    middle_edges[i] = edge_id;
    mf.add_edge(v[i].fir, xx + v[i].sec, 1, 0, edge_id++);
  }
  mf.run(src, sink);
  assert(mf.check());
  vector<int> flow_edges = mf.pr.flow_edges(edge_id);
  for (int i = 0; i < n; i++)
  {
    if (flow_edges[middle_edges[i]])
      cout << "L";
    else
      cout << "F";
  }
  cout << endl;
}
// https://codeforces.com/group/TFrGcBYYxs/contest/584448/problem/D
// questao de flow com demands da summer school
// grafo bipartido com n = 10ˆ5
// e esse push relabel do kactl passa, incrivel kkkkkkkkkkkk
// https://github.com/kth-competitive-programming/kactl/blob/main/content/graph/PushRelabel.h
// obrigado kactl