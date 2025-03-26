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
#define MAXN 1000005
#define mod 1000000007
#define double long double

struct pt
{
  int x, y, vx, vy;
  bool operator<(pt o)
  {
    if (x != o.x)
      return x > o.x;
    return vx < o.vx;
  }
};
struct line
{
  mutable double m, b, p;
  bool operator<(const line &o) const
  {
    if (m != o.m)
      return m < o.m;
    return b < o.b;
  }
  bool operator<(const double x) const { return p < x; }
  double eval(double x) const { return m * x + b; }
  double inter(const line &o) const
  {
    double x = b - o.b, y = o.m - m;
    return x / y;
  }
};
struct cht
{
  double INF = 6e18;
  multiset<line, less<>> l;
  void add(double m, double b)
  {
    auto y = l.insert({m, b, INF});
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
        y->p = INF;
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
      double ninter = x->inter(*z);
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
  double qry(double x)
  {
    if (l.empty())
      return 0;
    return l.lower_bound(x)->eval(x);
  }
};

cht x_max, x_min, y_max, y_min;

signed main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  int n;
  cin >> n;
  vector<pt> v(n);
  for (int i = 0; i < n; i++)
  {
    cin >> v[i].x >> v[i].y >> v[i].vx >> v[i].vy;
    x_max.add(v[i].vx, v[i].x);
    x_min.add(-v[i].vx, -v[i].x);
    y_max.add(v[i].vy, v[i].y);
    y_min.add(-v[i].vy, -v[i].y);
  }
  auto get_area = [&](double t)
  {
    return (x_max.qry(t) + x_min.qry(t)) * (y_max.qry(t) + y_min.qry(t));
  };
  double ans = get_area(0);
  for (auto const &i : x_max.l)
  {
    if (i.p >= 0)
      ans = min(ans, get_area(i.p));
  }
  for (auto const &i : x_min.l)
  {
    if (i.p >= 0)
      ans = min(ans, get_area(i.p));
  }
  for (auto const &i : y_max.l)
  {
    if (i.p >= 0)
      ans = min(ans, get_area(i.p));
  }
  for (auto const &i : y_min.l)
  {
    if (i.p >= 0)
      ans = min(ans, get_area(i.p));
  }
  cout << fixed << setprecision(15) << ans << endl;
}
// em algum momento a area do retangulo que cobre todos os pontos vai ser a minima possivel
// qual essa menor area possivel
// no tempo t, o ponto (x, y) vai estar em (x + t * vx, y + t * vy)