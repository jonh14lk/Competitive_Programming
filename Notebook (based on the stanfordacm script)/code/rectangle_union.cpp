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
#define MAXN 200007

vector<int> x_vals;

struct segtree
{
  vector<int> seg, tag;
  segtree()
  {
    seg.assign(8 * x_vals.size(), 0);
    tag.assign(8 * x_vals.size(), 0);
  }
  void add(int ql, int qr, int x, int v, int l, int r)
  {
    if (qr <= l || r <= ql)
    {
      return;
    }
    if (ql <= l && r <= qr)
    {
      tag[v] += x;
      if (tag[v] == 0)
      {
        if (l != r)
          seg[v] = seg[v << 1] + seg[(v << 1) | 1];
        else
          seg[v] = 0;
      }
      else
      {
        seg[v] = x_vals[r] - x_vals[l];
      }
    }
    else
    {
      int mid = (l + r) >> 1;
      add(ql, qr, x, (v << 1), l, mid);
      add(ql, qr, x, ((v << 1) | 1), mid, r);
      if (tag[v] == 0 && l != r)
        seg[v] = seg[v << 1] + seg[(v << 1) | 1];
    }
  }
  int qry()
  {
    return seg[1];
  }
  void upd(int l, int r, int x)
  {
    add(l, r, x, 1, 0, x_vals.size());
  }
};
struct rect
{
  int x1, y1, x2, y2;
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

const int inf = 1e9;

signed main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  int n;
  cin >> n;
  vector<rect> v(n);
  for (int i = 0; i < n; i++)
  {
    cin >> v[i].x1 >> v[i].y1 >> v[i].x2 >> v[i].y2;
    x_vals.pb(v[i].x1);
    x_vals.pb(v[i].x2);
  }
  // comprime o x
  sort(x_vals.begin(), x_vals.end());
  x_vals.erase(unique(x_vals.begin(), x_vals.end()), x_vals.end());
  vector<event> ev;
  for (int i = 0; i < n; i++)
  {
    v[i].x1 = lower_bound(x_vals.begin(), x_vals.end(), v[i].x1) - x_vals.begin();
    v[i].x2 = lower_bound(x_vals.begin(), x_vals.end(), v[i].x2) - x_vals.begin();
    ev.pb({v[i].y1, v[i].x1, v[i].x2, 0}); // adicao
    ev.pb({v[i].y2, v[i].x1, v[i].x2, 1}); // remocao
  }
  segtree s;
  sort(ev.begin(), ev.end());
  int area = 0, l = -inf;
  for (auto const &i : ev)
  {
    if (l == -inf)
    {
      l = i.time;
      s.upd(i.l, i.r, 1);
    }
    else if (i.type == 1)
    {
      int curr = s.qry();
      s.upd(i.l, i.r, -1);
      if (s.qry() != curr)
      {
        int new_t = (s.qry() == 0) ? -inf : i.time;
        int lo = l, hi = i.time - 1;
        area += ((hi - lo + 1) * curr);
        l = new_t;
      }
    }
    else
    {
      int curr = s.qry();
      s.upd(i.l, i.r, 1);
      if (s.qry() != curr)
      {
        int lo = l, hi = i.time - 1;
        area += ((hi - lo + 1) * curr);
        l = i.time;
      }
    }
  }
  cout << area << endl;
  return 0;
}
// area da uniao de retangulos
// comprime coordenada no x pra montar a segtree dos valores de x
// faz o line sweep pelo y

// testado em dois judges:
// https://cses.fi/problemset/task/1741/
// n <= 10^5
// -10^6 <= x, y <= 10^6

// https://judge.yosupo.jp/problem/area_of_union_of_rectangles
// n <= 5 * 10^5
// 0 <= x, y <= 10^9