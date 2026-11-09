#include <bits/stdc++.h>
using namespace std;

#define int long long int
#define MAXN 200007
#define pi pair<int, int>
#define pii pair<int, pi>
#define pb push_back
#define fir first
#define sec second
#define left fir
#define right sec.fir
#define color sec.sec

const int inf = 2e9;
vector<int> adj[MAXN];

namespace lca
{
  int l, timer;
  vector<int> tin, tout, depth;
  vector<vector<int>> up;

  void dfs(int v, int p)
  {
    tin[v] = ++timer;
    up[v][0] = p;
    for (int i = 1; i <= l; i++)
      up[v][i] = up[up[v][i - 1]][i - 1];
    for (auto const &u : adj[v])
    {
      if (p == u)
        continue;
      depth[u] = depth[v] + 1;
      dfs(u, v);
    }
    tout[v] = ++timer;
  }
  bool is_ancestor(int u, int v)
  {
    return tin[u] <= tin[v] && tout[u] >= tout[v];
  }
  int binary_lifting(int u, int v)
  {
    if (is_ancestor(u, v))
      return u;
    if (is_ancestor(v, u))
      return v;
    for (int i = l; i >= 0; --i)
      if (!is_ancestor(up[u][i], v))
        u = up[u][i];
    return up[u][0];
  }
  void init(int n)
  {
    tin.resize(n);
    tout.resize(n);
    depth.resize(n);
    timer = 0;
    l = ceil(log2(n));
    up.assign(n, vector<int>(l + 1));
    dfs(0, 0);
  }
  int dist(int s, int v)
  {
    int at = binary_lifting(s, v);
    return (depth[s] + depth[v] - 2 * depth[at]);
  }
}
struct color_upd
{
  set<pii> ranges;
  vector<pii> erased;

  color_upd()
  {
    ranges.insert({-inf, {inf, inf}});
  }
  int get(int i)
  {
    auto it = ranges.upper_bound({i, {1e18, 1e18}});
    if (it == ranges.begin())
      return -1;
    it--;
    return (*(it)).color;
  }
  void del(int l, int r)
  {
    erased.clear();
    auto it = ranges.upper_bound({l, {0, 0}});
    if (it != ranges.begin())
    {
      it--;
    }
    while (it != ranges.end())
    {
      if ((*(it)).left > r)
        break;
      else if ((*(it)).right >= l)
        erased.push_back(*it);
      it++;
    }
    if (erased.size() > 0)
    {
      int sz = erased.size();
      auto it = ranges.lower_bound(erased[0]);
      auto it2 = ranges.lower_bound(erased[sz - 1]);
      pii ini = *it, fim = *it2;
      it2++;
      ranges.erase(it, it2);
      pii upd1 = {ini.left, {l - 1, ini.color}};
      pii upd2 = {r + 1, {fim.right, fim.color}};
      erased[0].left = max(erased[0].left, l);
      erased[sz - 1].right = min(erased[sz - 1].right, r);
      if (upd1.left <= upd1.right)
        ranges.insert(upd1);
      if (upd2.left <= upd2.right)
        ranges.insert(upd2);
    }
  }
  void upd(int a, int b, int c)
  {
    del(a, b);
    ranges.insert({a, {b, c}});
  }
};
struct rect
{
  int x1, y1, x2, y2, id;
};
struct qry
{
  int x, y, r;
};
struct event
{
  // type: 0 -> adicao de retangulo, 1 -> query de ponto, 2 -> remocao de retangulo
  int x, y, id, type;
};
bool cmp(event &a, event &b)
{
  if (a.x != b.x)
    return a.x < b.x;
  if (a.y != b.y)
    return a.y < b.y;
  return a.type < b.type;
}
signed main()
{
  ios::sync_with_stdio(0);
  cin.tie(0);
  int n;
  cin >> n;
  vector<rect> v(n);
  vector<event> e;
  for (int i = 0; i < n; i++)
  {
    cin >> v[i].x1 >> v[i].y1 >> v[i].x2 >> v[i].y2;
    v[i].id = i + 1;
    e.pb({v[i].x1, v[i].y1, i, 0});
    e.pb({v[i].x2, v[i].y2, i, 2});
  }
  int q;
  cin >> q;
  for (int i = 0; i < q; i++)
  {
    int x, y, r;
    cin >> x >> y >> r;
    e.pb({x - r, y - r, i, 1});
    e.pb({x - r, y + r, i, 1});
    e.pb({x + r, y - r, i, 1});
    e.pb({x + r, y + r, i, 1});
  }
  sort(e.begin(), e.end(), cmp);
  color_upd c;
  vector<vector<int>> qry_vertices(q);
  vector<int> par(n + 1, -1);
  for (auto const &i : e)
  {
    if (i.type == 0)
    {
      par[i.id] = c.get(v[i.id].y1);
      c.upd(v[i.id].y1, v[i.id].y2, i.id);
    }
    else if (i.type == 1)
    {
      qry_vertices[i.id].pb(c.get(i.y) + 1);
    }
    else
    {
      c.upd(v[i.id].y1, v[i.id].y2, par[i.id]);
    }
  }
  for (int i = 0; i < n; i++)
  {
    if (par[i] == inf)
    {
      adj[0].pb(i + 1);
      adj[i + 1].pb(0);
    }
    else
    {
      adj[par[i] + 1].pb(i + 1);
      adj[i + 1].pb(par[i] + 1);
    }
  }
  lca::init(n + 1);
  for (int i = 0; i < q; i++)
  {
    int l = -1;
    for (auto const &j : qry_vertices[i])
    {
      if (j >= inf)
      {
        l = 0;
        break;
      }
      if (l == -1)
      {
        l = j;
      }
      else
      {
        l = lca::binary_lifting(l, j);
      }
    }
    (l == 0) ? cout << "*\n" : cout << l << endl;
  }
}
// como montar a arvore de intervalos?
// uma vez que temos a arvore precisamos achar o retangulo de menor area
// que cobre o vertice da query
// a resposta de uma query eh o lca dos 4 caras
