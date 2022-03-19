
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
#define MAXN 200005
#define mod 1000000007
#define PI acos(-1)

const double EPS = 1e-9;

struct pt
{
  double x, y;
};
struct seg
{
  pt p, q;
  int id;
  double get_y(double x) const
  {
    if (abs(p.x - q.x) < EPS)
      return p.y;
    return p.y + (q.y - p.y) * (x - p.x) / (q.x - p.x);
  }
};
bool intersect1d(double l1, double r1, double l2, double r2)
{
  if (l1 > r1)
    swap(l1, r1);
  if (l2 > r2)
    swap(l2, r2);
  return max(l1, l2) <= min(r1, r2) + EPS;
}
int vec(const pt &a, const pt &b, const pt &c)
{
  double s = (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);
  return abs(s) < EPS ? 0 : s > 0 ? +1
                                  : -1;
}
bool intersect(const seg &a, const seg &b)
{
  return intersect1d(a.p.x, a.q.x, b.p.x, b.q.x) &&
         intersect1d(a.p.y, a.q.y, b.p.y, b.q.y) &&
         vec(a.p, a.q, b.p) * vec(a.p, a.q, b.q) <= 0 &&
         vec(b.p, b.q, a.p) * vec(b.p, b.q, a.q) <= 0;
}
bool operator<(const seg &a, const seg &b)
{
  double x = max(min(a.p.x, a.q.x), min(b.p.x, b.q.x));
  return a.get_y(x) < b.get_y(x) - EPS;
}
struct event
{
  double x;
  int tp, id;
  event() {}
  event(double x, int tp, int id) : x(x), tp(tp), id(id) {}
  bool operator<(const event &e) const
  {
    if (abs(x - e.x) > EPS)
      return x < e.x;
    return tp > e.tp;
  }
};

set<seg> s;

set<seg>::iterator prev(set<seg>::iterator it)
{
  return it == s.begin() ? s.end() : --it;
}
set<seg>::iterator next(set<seg>::iterator it)
{
  return ++it;
}
pi line_sweep(vector<seg> v)
{
  vector<event> e;
  for (int i = 0; i < v.size(); i++)
  {
    e.push_back({min(v[i].p.x, v[i].q.x), 1, i});
    e.push_back({max(v[i].p.x, v[i].q.x), 0, i});
  }
  sort(e.begin(), e.end());
  for (int i = 0; i < e.size(); i++)
  {
    int id = e[i].id;
    if (e[i].tp == 1)
    {
      auto nxt = s.lower_bound(v[id]), prv = prev(nxt);
      if (nxt != s.end() && intersect(*nxt, v[id]))
        return {(*nxt).id, id};
      if (prv != s.end() && intersect(*prv, v[id]))
        return {(*prv).id, id};
      s.insert(nxt, v[id]);
    }
    else
    {
      auto where = s.lower_bound(v[id]);
      auto nxt = next(where), prv = prev(where);
      if (nxt != s.end() && prv != s.end() && intersect(*nxt, *prv))
        return {(*prv).id, (*nxt).id};
      s.erase(where);
    }
  }
  return {-1, -1};
}
signed main()
{
  int n;
  cin >> n;
  vector<seg> v(n);
  for (int i = 0; i < n; i++)
  {
    cin >> v[i].p.x >> v[i].p.y >> v[i].q.x >> v[i].q.y;
    v[i].id = i;
  }
  pi ans = line_sweep(v);
  if (ans.fir == -1)
  {
    cout << "NO\n";
  }
  else
  {
    cout << "YES\n";
    cout << ans.fir + 1 << " " << ans.sec + 1 << endl;
  }
  return 0;
}
// https://cp-algorithms.com/geometry/intersecting_segments.html
// https://acm.timus.ru/problem.aspx?space=1&num=1469
