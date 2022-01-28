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
#define pii pair<int, pair<int, pi>>
#define fir first
#define sec second
#define MAXN 1000002
#define mod 1000000007

struct segtree
{
  int n;
  vector<pi> seg;

  segtree(int sz)
  {
    n = sz;
    seg.assign(4 * n, {0, 0});
  }
  void merge(int i, int l, int r)
  {
    if (seg[i].fir > 0)
      seg[i].sec = r - l + 1;
    else if (l != r)
      seg[i].sec = seg[i << 1].sec + seg[(i << 1) | 1].sec;
    else
      seg[i].sec = 0;
  }
  void add(int i, int l, int r, int diff)
  {
    seg[i].fir += diff;
    merge(i, l, r);
  }
  void update(int i, int l, int r, int ql, int qr, int diff)
  {
    if (l > r || l > qr || r < ql)
      return;
    if (l >= ql && r <= qr)
    {
      add(i, l, r, diff);
      return;
    }
    int mid = (l + r) >> 1;
    update(i << 1, l, mid, ql, qr, diff);
    update((i << 1) | 1, mid + 1, r, ql, qr, diff);
    merge(i, l, r);
  }
  int query(int l, int r, int ql, int qr, int i)
  {
    if (l > r || l > qr || r < ql)
      return 0;
    if (l >= ql && r <= qr)
      return seg[i].sec;
    int mid = (l + r) >> 1;
    return query(l, mid, ql, qr, i << 1) + query(mid + 1, r, ql, qr, (i << 1) | 1);
  }
  int qry()
  {
    return query(0, n - 1, 0, n - 1, 1);
  }
  void upd(int l, int r, int x)
  {
    update(1, 0, n - 1, l, r, x);
  }
};
struct event
{
  int time, l, r, type;
  bool operator<(const event &b)
  {
    if (time != b.time)
      return time < b.time;
    return type > b.type;
  }
};

int n, p;
vector<pair<pi, pi>> v;
pair<pi, pi> r;

const int lim = 1e5 + 5;

bool can(int mid)
{
  vector<pair<pi, pi>> rects;
  for (auto const &i : v) // pegar a intersecção de cada retangulo com o retangulo main
  {
    pair<pi, pi> curr;
    curr.fir.fir = max(i.fir.fir - mid, r.fir.fir);
    curr.fir.sec = max(i.fir.sec - mid, r.fir.sec);
    curr.sec.fir = min(i.sec.fir + mid, r.sec.fir);
    curr.sec.sec = min(i.sec.sec + mid, r.sec.sec);
    if (curr.fir.fir > curr.sec.fir || curr.fir.sec > curr.sec.sec)
      continue;
    rects.pb(curr);
  }
  vector<event> ev;
  for (auto const &i : rects)
  {
    ev.pb({i.fir.fir, i.fir.sec, i.sec.sec, 0});
    ev.pb({i.sec.fir, i.fir.sec, i.sec.sec, 1});
  }
  sort(ev.begin(), ev.end());
  int total_area = (r.sec.fir - r.fir.fir) * (r.sec.sec - r.fir.sec);
  int area = 0, l = -1;
  segtree s(lim);
  for (auto const &i : ev)
  {
    if (l == -1)
    {
      l = i.time;
      s.upd(i.l, i.r - 1, 1);
    }
    else if (i.type == 1)
    {
      int curr = s.qry();
      s.upd(i.l, i.r - 1, -1);
      if (s.qry() != curr)
      {
        int new_t = (s.qry() == 0) ? -1 : i.time;
        int lo = l, hi = i.time - 1;
        area += ((hi - lo + 1) * curr);
        l = new_t;
      }
    }
    else
    {
      int curr = s.qry();
      s.upd(i.l, i.r - 1, 1);
      if (s.qry() != curr)
      {
        int lo = l, hi = i.time - 1;
        area += ((hi - lo + 1) * curr);
        l = i.time;
      }
    }
  }
  return (area * 100) >= (total_area * p);
}
signed main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  cin >> n;
  v.resize(n);
  for (int i = 0; i < n; i++)
  {
    cin >> v[i].fir.fir >> v[i].fir.sec >> v[i].sec.fir >> v[i].sec.sec;
    if (v[i].fir.fir > v[i].sec.fir || v[i].fir.sec > v[i].sec.sec)
      swap(v[i].fir, v[i].sec);
  }
  cin >> p >> r.fir.fir >> r.fir.sec >> r.sec.fir >> r.sec.sec;
  int l = 1, r = lim;
  while (l < r)
  {
    int mid = (l + r) >> 1;
    (can(mid)) ? r = mid : l = mid + 1;
  }
  cout << l << endl;
  return 0;
}
// busca binaria pelo r da resposta
// dai pra checar uma resposta
// gerar todos os retangulos com os segmentos de reta
// considerar somente a intersecção com o retangulo main
// ver se a intersecção eh pelo menos p%