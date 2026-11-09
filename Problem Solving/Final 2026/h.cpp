#include <bits/stdc++.h>
using namespace std;

#define int long long int
#define MAXN 200005
#define pi pair<int, int>
#define pii pair<pi, int>
#define pb push_back
#define fir first
#define sec second

const int inf = 2e18;

struct node
{
  int item, l, r;
  node() {}
  node(int l, int r, int item) : l(l), r(r), item(item) {}
};
struct segtree
{
  vector<node> seg;

  void init()
  {
    seg.resize(1);
  }
  int newleaf(int vv)
  {
    int p = seg.size();
    seg.pb(node(0, 0, vv));
    return p;
  }
  int newpar(int l, int r)
  {
    int p = seg.size();
    seg.pb(node(l, r, seg[l].item + seg[r].item));
    return p;
  }
  int upd(int i, int l, int r, int pos)
  {
    if (l == r)
      return newleaf(seg[i].item + 1);
    int mid = (l + r) >> 1;
    if (pos <= mid)
      return newpar(upd(seg[i].l, l, mid, pos), seg[i].r);
    return newpar(seg[i].l, upd(seg[i].r, mid + 1, r, pos));
  }
  int build(int l, int r)
  {
    if (l == r)
      return newleaf(0);
    int mid = (l + r) >> 1;
    return newpar(build(l, mid), build(mid + 1, r));
  }
  int qry(int l, int r, int ql, int qr, int i)
  {
    if (l > r || l > qr || r < ql)
      return 0;
    if (l >= ql && r <= qr)
      return seg[i].item;
    int mid = (l + r) >> 1;
    return qry(l, mid, ql, qr, seg[i].l) + qry(mid + 1, r, ql, qr, seg[i].r);
  }
};
signed main()
{
  ios::sync_with_stdio(0);
  cin.tie(0);
  int n;
  cin >> n;
  vector<pi> v(n);
  vector<int> all;
  vector<int> yy;
  for (int i = 0; i < n; i++)
  {
    int y, h;
    cin >> y >> h;
    h -= y; // tempo 0
    v[i] = {y, h};
    all.pb(h);
    yy.pb(h);
  }
  sort(yy.begin(), yy.end());
  yy.erase(unique(yy.begin(), yy.end()), yy.end());
  sort(all.begin(), all.end());
  sort(v.begin(), v.end());
  segtree st;
  st.init(); // segtree persistente pelo h ordenado
  int m = yy.size();
  vector<pi> roots;
  roots.pb({-inf, st.build(0, m - 1)});
  for (auto [x, y] : v)
  {
    int id = lower_bound(yy.begin(), yy.end(), y) - yy.begin();
    roots.pb({x, st.upd(roots.back().sec, 0, m - 1, id)});
  }
  int q;
  cin >> q;
  while (q--)
  {
    int k, v;
    cin >> k >> v;
    auto can = [&](int y)
    {
      // entao sao elementos >= v - y
      auto it = lower_bound(yy.begin(), yy.end(), v - y);
      if (it == yy.end())
      {
        return (0 >= k);
      }
      int hue = upper_bound(roots.begin(), roots.end(), pi(y + 1, -1)) - roots.begin();
      hue--;
      int qt = st.qry(0, m - 1, it - yy.begin(), m - 1, roots[hue].sec);
      return (qt >= k);
    };
    int l = 0, r = (int)2e18;
    while (l < r)
    {
      int mid = (l + r) >> 1;
      can(mid) ? r = mid : l = mid + 1;
    }
    cout << l << endl;
  }
}
