#include <bits/stdc++.h>
using namespace std;

#define int long long int
#define pb push_back
#define pi pair<int, int>
#define pii pair<int, pi>
#define fir first
#define sec second
#define MAXN 100005
#define mod 1000000007

const int inf = 1e18;

struct edge
{
  int u, l, r, x, k;
};
struct item
{
  int l, r, mn, mn_id;
};
struct line
{
  mutable int m, b, p;
  bool operator<(const line &o) const
  {
    if (m != o.m)
      return m < o.m;
    return b < o.b;
  }
  bool operator<(const int x) const { return p < x; }
  int eval(int x) const { return m * x + b; }
  int inter(const line &o) const
  {
    int x = b - o.b, y = o.m - m;
    return (x / y) - ((x ^ y) < 0 && x % y);
  }
};
struct cht
{
  multiset<line, less<>> l;
  void add(int m, int b)
  {
    m *= -1;
    b *= -1;
    auto y = l.insert({m, b, inf});
    auto z = next(y);
    if (z != l.end() && y->m == z->m)
    {
      l.erase(y);
      return;
    }
    if (y != l.begin())
    {
      auto x = prev(y);
      if (x->m == y->m)
        x = l.erase(x);
    }
    while (1)
    {
      if (z == l.end())
      {
        y->p = inf;
        break;
      }
      y->p = y->inter(*z);
      if (y->p < z->p)
        break;
      else
        z = l.erase(z);
    }
    if (y == l.begin())
      return;
    z = y;
    auto x = --y;
    while (1)
    {
      int ninter = x->inter(*z);
      if (ninter <= x->p)
        x->p = ninter;
      else
      {
        l.erase(z);
        break;
      }
      if (x == l.begin())
        break;
      y = x;
      x--;
      if (x->p < y->p)
        break;
      else
        l.erase(y);
    }
  }
  int get(int x)
  {
    if (l.empty() || x == -1)
      return inf;
    return l.lower_bound(x)->eval(x) * -1;
  }
};

item seg[4 * MAXN];
cht ch[4 * MAXN];

void build(int l, int r, int i)
{
  if (l == r)
  {
    seg[i] = {l, l, inf, l};
    return;
  }
  int mid = (l + r) >> 1;
  build(l, mid, i << 1);
  build(mid + 1, r, (i << 1) | 1);
  seg[i].l = min(seg[i << 1].l, seg[(i << 1) | 1].l);
  seg[i].r = max(seg[i << 1].r, seg[(i << 1) | 1].r);
  if (seg[i << 1].mn < seg[(i << 1) | 1].mn)
    seg[i].mn = seg[i << 1].mn, seg[i].mn_id = seg[i << 1].mn_id;
  else
    seg[i].mn = seg[(i << 1) | 1].mn, seg[i].mn_id = seg[(i << 1) | 1].mn_id;
}
void upd_best(int i)
{
  if (seg[i].l == inf)
    return;
  pi curr = {ch[i].get(seg[i].l), seg[i].l};
  curr = min(curr, {ch[i].get(seg[i].r), seg[i].r});
  if (curr.fir < seg[i].mn)
  {
    seg[i].mn = curr.fir;
    seg[i].mn_id = curr.sec;
  }
}
void disable(int i, int l, int r, int q)
{
  if (l == r)
  {
    seg[i] = {inf, -1, inf, -1};
    return;
  }
  int mid = (l + r) >> 1;
  if (q <= mid)
    disable(i << 1, l, mid, q);
  else
    disable((i << 1) | 1, mid + 1, r, q);
  seg[i].l = min(seg[i << 1].l, seg[(i << 1) | 1].l);
  seg[i].r = max(seg[i << 1].r, seg[(i << 1) | 1].r);
  if (seg[i << 1].mn < seg[(i << 1) | 1].mn)
    seg[i].mn = seg[i << 1].mn, seg[i].mn_id = seg[i << 1].mn_id;
  else
    seg[i].mn = seg[(i << 1) | 1].mn, seg[i].mn_id = seg[(i << 1) | 1].mn_id;
  upd_best(i);
}
void add_line(int i, int l, int r, int ql, int qr, int x, int y)
{
  if (l > r || l > qr || r < ql)
    return;
  if (l >= ql && r <= qr)
  {
    ch[i].add(x, y);
    upd_best(i);
    return;
  }
  int mid = (l + r) >> 1;
  add_line(i << 1, l, mid, ql, qr, x, y);
  add_line((i << 1) | 1, mid + 1, r, ql, qr, x, y);
  seg[i].l = min(seg[i << 1].l, seg[(i << 1) | 1].l);
  seg[i].r = max(seg[i << 1].r, seg[(i << 1) | 1].r);
  if (seg[i << 1].mn < seg[(i << 1) | 1].mn)
    seg[i].mn = seg[i << 1].mn, seg[i].mn_id = seg[i << 1].mn_id;
  else
    seg[i].mn = seg[(i << 1) | 1].mn, seg[i].mn_id = seg[(i << 1) | 1].mn_id;
  upd_best(i);
}
signed main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  int n, m, a, b;
  cin >> n >> m >> a >> b;
  a--, b--;
  vector<edge> edges(m);
  vector<vector<int>> adj(n);
  for (int i = 0; i < m; i++)
  {
    int u, l, r, x, k;
    cin >> u >> l >> r >> x >> k;
    u--, l--, r--;
    edges[i] = {u, l, r, x, k};
    adj[u].pb(i);
  }
  vector<int> dist(n, inf);
  build(0, n - 1, 1);
  add_line(1, 0, n - 1, 0, 0, 0, 0);
  while (1)
  {
    int x = seg[1].mn_id;
    if (x == -1 || x == inf)
      break;
    dist[x] = seg[1].mn;
    disable(1, 0, n - 1, x);
    for (auto const &i : adj[x])
      add_line(1, 0, n - 1, edges[i].l, edges[i].r, edges[i].k, dist[x] + edges[i].x - (edges[i].l * edges[i].k));
  }
  if (dist[a] == inf || dist[b] == inf)
    cout << "-1\n";
  else
    cout << dist[a] + dist[b] << endl;
  return 0;
}
// quero uma estrutura de dados que faz o seguinte:
// mantem pontos 0, 1, ..., n - 1
// inicialmente para cada um desses pontos a[i] = inf, a[0] = 0

// adiciona uma reta no range [l, r], ou seja algo como: a[i] = min(a[i], x * i + y)
// (x e y os caras da reta que tou adicionando)

// desativa um ponto, posso pensar em so setar a[i] = inf

// considerando apenas pontos ativos, qual o menor eval de algum dos pontos ativos com alguma reta dele?
// da pra se pensar so em achar o min(a[i])

// se eu tenho essa estrutura numa complexidade ok, resolvo o problema
// pq dai eh so fazer o dijkstra trocando a priority queue por essa estutura

// eh algo que pode se parecer com uma segtree
// mas o update eh problematico
// se eu souber performar o update de maneira eficiente, gg