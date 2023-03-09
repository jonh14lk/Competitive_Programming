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
#define MAXN 100005
#define double long double
#define mod 1000000007

const double eps = 1e-9;

struct pt
{
  double x, y;
  pt operator-(pt p) { return {x - p.x, y - p.y}; }
  bool eq(double a, double b) const
  {
    return abs(a - b) <= eps;
  }
  double operator^(const pt p) const { return x * p.y - y * p.x; }
  bool operator<(const pt p) const
  {
    if (!eq(x, p.x))
      return x < p.x;
    if (!eq(y, p.y))
      return y < p.y;
    return 0;
  }
  bool operator==(const pt p) const
  {
    return eq(x, p.x) and eq(y, p.y);
  }
};
double sarea(pt p, pt q, pt r)
{
  return ((q - p) ^ (r - q)) / 2;
}
bool ccw(pt p, pt q, pt r)
{
  return sarea(p, q, r) > eps;
}
// https://github.com/brunomaletta/Biblioteca/blob/master/Codigo/Problemas/dynamicHull.cpp
struct upper
{
  set<pt> se;
  set<pt>::iterator it;
  // 0 - fora
  // 1 - dentro
  // 2 - na borda
  int is_under(pt p)
  {
    it = se.lower_bound(p);
    if (it == se.end())
      return 0;
    if (it == se.begin())
      return p == *it ? 2 : 0;
    if (ccw(p, *it, *prev(it)))
      return 1;
    return ccw(p, *prev(it), *it) ? 0 : 2;
  }
  void insert(pt p)
  {
    if (is_under(p))
      return;
    if (it != se.end())
      while (next(it) != se.end() and !ccw(*next(it), *it, p))
        it = se.erase(it);
    if (it != se.begin())
      while (--it != se.begin() and !ccw(p, *it, *prev(it)))
        it = se.erase(it);
    se.insert(p);
  }
};
struct dyn_hull
{
  upper U, L;
  int is_inside(pt p)
  {
    int u = U.is_under(p), l = L.is_under({-p.x, -p.y});
    if (!u || !l)
      return 0;
    return max(u, l);
  }
  void insert(pt p)
  {
    U.insert(p);
    L.insert({-p.x, -p.y});
  }
  int size()
  {
    int ans = U.se.size() + L.se.size();
    return ans <= 2 ? ans / 2 : ans - 2;
  }
};
signed main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  return 0;
}
// convex hull dinamico
// problema para usar: https://open.kattis.com/problems/hiringhelp