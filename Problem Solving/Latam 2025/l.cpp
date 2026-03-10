#include <bits/stdc++.h>
using namespace std;

#define int long long int
#define pb push_back
#define pi pair<int, int>
#define pii pair<pi, int>
#define pd pair<double, double>
#define fir first
#define sec second
#define MAXN 1005
#define mod 998244353

int n, c, l;

namespace dsu
{
  struct rollback
  {
    int u, v, ranku, rankv;
  };

  int num_sets;
  int parent[MAXN];
  int rank[MAXN];
  stack<rollback> op;

  int Find(int i)
  {
    return (parent[i] == i) ? i : Find(parent[i]);
  }
  bool Union(int x, int y)
  {
    int xx = Find(x);
    int yy = Find(y);
    if (xx != yy)
    {
      num_sets--;
      if (rank[xx] > rank[yy])
        swap(xx, yy);
      op.push({xx, yy, rank[xx], rank[yy]});
      parent[xx] = yy;
      if (rank[xx] == rank[yy])
        rank[yy]++;
      return true;
    }
    return false;
  }
  void do_rollback()
  {
    if (op.empty())
      return;
    rollback x = op.top();
    op.pop();
    num_sets++;
    parent[x.v] = x.v;
    rank[x.v] = x.rankv;
    parent[x.u] = x.u;
    rank[x.u] = x.ranku;
  }
  void init(int n)
  {
    for (int i = 0; i < n; i++)
    {
      parent[i] = i;
      rank[i] = 0;
    }
    num_sets = n;
  }
}
namespace seg
{
  struct query
  {
    int v, u, is_bridge;
  };

  vector<vector<query>> t(4 * 2 * MAXN * MAXN);
  int ans[2 * MAXN * MAXN];

  void add(int i, int l, int r, int ql, int qr, query q)
  {
    if (l > r || l > qr || r < ql)
      return;
    if (l >= ql && r <= qr)
    {
      t[i].push_back(q);
      return;
    }
    int mid = (l + r) >> 1;
    add((i << 1), l, mid, ql, qr, q);
    add((i << 1) | 1, mid + 1, r, ql, qr, q);
  }
  void dfs(int i, int l, int r)
  {
    for (query &q : t[i])
      if (dsu::Union(q.v, q.u))
        q.is_bridge = 1;
    if (l == r)
      ans[l] = dsu::Find(n - 1) == dsu::Find(n - 2);
    else
    {
      int mid = (l + r) >> 1;
      dfs((i << 1), l, mid);
      dfs((i << 1) | 1, mid + 1, r);
    }
    for (query q : t[i])
      if (q.is_bridge)
        dsu::do_rollback();
  }
}

const int inf = 1e18;
const double eps = 1e-11;

pd get_inter(pi a, pi b, int c)
{
  int d0 = a.fir - b.fir;
  int dv = a.sec - b.sec;
  if (dv == 0)
    return (abs(d0) < c) ? pd(0, inf) : pd(-1, -1);
  double t1 = (double)(-c - d0) / dv;
  double t2 = (double)(c - d0) / dv;
  double l = min(t1, t2);
  l = max(l, (double)0.0);
  double r = max(t1, t2);
  return (l < r) ? pd(l, r) : pd(-1, -1);
}
signed main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  cin >> n >> c >> l;
  vector<pi> v(n);
  for (int i = 0; i < n; i++)
  {
    cin >> v[i].fir >> v[i].sec;
  }
  v.pb({0, 0});
  v.pb({l, 0});
  n += 2;
  vector<vector<pd>> inter(n, vector<pd>(n));
  vector<double> pts;
  pts.pb(0.0);
  for (int i = 0; i < n; i++)
  {
    for (int j = i + 1; j < n; j++)
    {
      // intervalo em que a distancia entre os dois vai ser < c (se existir)
      // queremos adicionar uma aresta no grafo nesse intervalo de tempo entre os dois
      inter[i][j] = get_inter(v[i], v[j], c);
      if (inter[i][j].fir != -1)
      {
        if (abs(v[i].fir - v[j].fir) >= c)
          pts.pb(inter[i][j].fir + eps);
        pts.pb(inter[i][j].sec - eps);
      }
    }
  }
  sort(pts.begin(), pts.end());
  pts.erase(unique(pts.begin(), pts.end()), pts.end());
  for (int i = 0; i < n; i++)
  {
    for (int j = i + 1; j < n; j++)
    {
      if (inter[i][j].fir != -1)
      {
        int l;
        if (abs(v[i].fir - v[j].fir) < c)
        {
          l = 0;
        }
        else
        {
          l = lower_bound(pts.begin(), pts.end(), inter[i][j].fir + eps) - pts.begin();
        }
        int r = lower_bound(pts.begin(), pts.end(), inter[i][j].sec - eps) - pts.begin();
        seg::add(1, 0, pts.size(), l, r - 1, {i, j, 0});
      }
    }
  }
  dsu::init(n);
  seg::dfs(1, 0, pts.size());
  int q;
  cin >> q;
  int ptr = 0;
  while (q--)
  {
    int t;
    cin >> t;
    while (ptr + 1 < pts.size() && pts[ptr + 1] <= t)
      ptr++;
    (!seg::ans[ptr]) ? cout << "Y\n" : cout << "N\n";
  }
  return 0;
}