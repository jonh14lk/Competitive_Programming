#include <bits/stdc++.h>
using namespace std;

#define lli long long int
#define endl '\n'
#define pb push_back
#define pi pair<int, int>
#define pii pair<int, pi>
#define fir first
#define sec second
#define MAXN 1000005
#define mod 998244353

const int inf = 2 * 1e9 + 2;

struct segtree
{
  int n;
  vector<int> v;
  vector<pi> seg;
  vector<pi> lazy;

  segtree(int sz)
  {
    n = sz;
    seg.assign(4 * n, {0, 0});
    lazy.assign(4 * n, {-inf, -inf});
  }
  void add(int i, int l, int r, pi x)
  {
    seg[i] = x;
    if (l != r)
    {
      lazy[i << 1] = x;
      lazy[(i << 1) | 1] = x;
    }
    lazy[i] = {-inf, -inf};
  }
  void update(int i, int l, int r, int ql, int qr, pi x)
  {
    if (lazy[i].fir != -inf)
      add(i, l, r, lazy[i]);
    if (l > r || l > qr || r < ql)
      return;
    if (l >= ql && r <= qr)
    {
      add(i, l, r, x);
      return;
    }
    int mid = (l + r) >> 1;
    update(i << 1, l, mid, ql, qr, x);
    update((i << 1) | 1, mid + 1, r, ql, qr, x);
    seg[i] = max(seg[i << 1], seg[(i << 1) | 1]);
  }
  pi query(int l, int r, int ql, int qr, int i)
  {
    if (lazy[i].fir != -inf)
      add(i, l, r, lazy[i]);
    if (l > r || l > qr || r < ql)
      return {-inf, -inf};
    if (l >= ql && r <= qr)
      return seg[i];
    int mid = (l + r) >> 1;
    return max(query(l, mid, ql, qr, i << 1), query(mid + 1, r, ql, qr, (i << 1) | 1));
  }
  void upd(int l, int r, pi x)
  {
    update(1, 0, n - 1, l, r, x);
  }
};
struct dsu
{
  int tot;
  vector<int> parent;
  vector<int> sz;

  dsu(int n)
  {
    parent.resize(n);
    sz.resize(n);
    tot = n;
    for (int i = 0; i < n; i++)
    {
      parent[i] = i;
      sz[i] = 1;
    }
  }
  int find_set(int i)
  {
    return parent[i] = (parent[i] == i) ? i : find_set(parent[i]);
  }
  void make_set(int x, int y)
  {
    x = find_set(x), y = find_set(y);
    if (x != y)
    {
      if (sz[x] > sz[y])
        swap(x, y);
      parent[x] = y;
      sz[y] += sz[x];
      tot--;
    }
  }
};
signed main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  int n;
  cin >> n;
  vector<pii> v(n);
  vector<int> val;
  for (int i = 0; i < n; i++)
  {
    cin >> v[i].fir >> v[i].sec.fir >> v[i].sec.sec;
    val.pb(v[i].sec.fir);
    val.pb(v[i].sec.sec);
    val.pb(v[i].sec.fir - v[i].fir);
    val.pb(v[i].sec.sec - v[i].fir);
    val.pb(v[i].sec.fir + v[i].fir);
    val.pb(v[i].sec.sec + v[i].fir);
  }
  sort(val.begin(), val.end());
  val.erase(unique(val.begin(), val.end()), val.end());
  auto get_id = [&](int x)
  {
    return lower_bound(val.begin(), val.end(), x) - val.begin();
  };
  v.pb({0, {-inf, inf}});
  sort(v.begin(), v.end());
  n = v.size();
  vector<pii> edges;
  segtree s(val.size());
  auto qry = [&](int l, int r)
  {
    return s.query(0, val.size() - 1, get_id(l), get_id(r), 1);
  };
  {
    int i = 1;
    while (i < n)
    {
      int j = i;
      while (j < n && v[j].fir == v[i].fir)
      {
        j++;
      }
      for (int k = i; k < j; k++)
      {
        int h = v[k].fir;
        auto [a, b] = v[k].sec;
        a -= h;
        b -= h;
        pi curr = qry(a, b);
        edges.pb({h - curr.fir, {k, curr.sec}});
        curr = qry(a, a);
        edges.pb({h - curr.fir, {k, curr.sec}});
        curr = qry(b, b);
        edges.pb({h - curr.fir, {k, curr.sec}});
      }
      for (int k = i; k < j; k++)
      {
        int h = v[k].fir;
        auto [a, b] = v[k].sec;
        a -= h;
        b -= h;
        s.upd(get_id(a), get_id(b), {h, k});
      }
      i = j;
    }
  }
  s = segtree(val.size());
  {
    int i = 1;
    while (i < n)
    {
      int j = i;
      while (j < n && v[j].fir == v[i].fir)
      {
        j++;
      }
      for (int k = i; k < j; k++)
      {
        int h = v[k].fir;
        auto [a, b] = v[k].sec;
        a += h;
        b += h;
        pi curr = qry(a, b);
        edges.pb({h - curr.fir, {k, curr.sec}});
        curr = qry(a, a);
        edges.pb({h - curr.fir, {k, curr.sec}});
        curr = qry(b, b);
        edges.pb({h - curr.fir, {k, curr.sec}});
      }
      for (int k = i; k < j; k++)
      {
        int h = v[k].fir;
        auto [a, b] = v[k].sec;
        a += h;
        b += h;
        s.upd(get_id(a), get_id(b), {h, k});
      }
      i = j;
    }
  }
  int aux = -inf + 1;
  s = segtree(val.size());
  s.upd(0, val.size() - 1, {aux, aux});
  {
    int i = n - 1;
    while (i > 0)
    {
      int j = i;
      while (j > 0 && v[j].fir == v[i].fir)
      {
        j--;
      }
      for (int k = i; k > j; k--)
      {
        int h = v[k].fir;
        auto [a, b] = v[k].sec;
        a += h;
        b += h;
        pi curr = qry(a, b);
        if (curr.fir != aux)
          edges.pb({-h - curr.fir, {k, curr.sec}});
        curr = qry(a, a);
        if (curr.fir != aux)
          edges.pb({-h - curr.fir, {k, curr.sec}});
        curr = qry(b, b);
        if (curr.fir != aux)
          edges.pb({-h - curr.fir, {k, curr.sec}});
      }
      for (int k = i; k > j; k--)
      {
        int h = v[k].fir;
        auto [a, b] = v[k].sec;
        a += h;
        b += h;
        s.upd(get_id(a), get_id(b), {-h, k});
      }
      i = j;
    }
  }
  s = segtree(val.size());
  s.upd(0, val.size() - 1, {aux, aux});
  {
    int i = n - 1;
    while (i > 0)
    {
      int j = i;
      while (j > 0 && v[j].fir == v[i].fir)
      {
        j--;
      }
      for (int k = i; k > j; k--)
      {
        int h = v[k].fir;
        auto [a, b] = v[k].sec;
        a -= h;
        b -= h;
        pi curr = qry(a, b);
        if (curr.fir != aux)
          edges.pb({-h - curr.fir, {k, curr.sec}});
        curr = qry(a, a);
        if (curr.fir != aux)
          edges.pb({-h - curr.fir, {k, curr.sec}});
        curr = qry(b, b);
        if (curr.fir != aux)
          edges.pb({-h - curr.fir, {k, curr.sec}});
      }
      for (int k = i; k > j; k--)
      {
        int h = v[k].fir;
        auto [a, b] = v[k].sec;
        a -= h;
        b -= h;
        s.upd(get_id(a), get_id(b), {-h, k});
      }
      i = j;
    }
  }
  sort(edges.begin(), edges.end());
  lli ans = 0;
  dsu d(n);
  for (auto const &i : edges)
  {
    if (d.find_set(i.sec.fir) != d.find_set(i.sec.sec))
    {
      d.make_set(i.sec.fir, i.sec.sec);
      ans += i.fir;
    }
  }
  cout << ans << endl;
  return 0;
}