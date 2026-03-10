#include <bits/stdc++.h>
using namespace std;

#define int long long int
#define pb push_back
#define pi pair<int, int>
#define pii pair<int, pi>
#define fir first
#define sec second
#define MAXN 10005
#define mod 998244353

const double DINF = 1e18;
const double PI = acos(-1);
const double eps = 1e-7;

bool eq(double a, double b)
{
  return abs(a - b) <= eps;
}
bool gt(double a, double b)
{
  return (a - b) > eps;
}
struct pt
{
  double x, y;
  pt(double x_ = 0, double y_ = 0) : x(x_), y(y_) {}
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
  pt operator+(const pt p) const { return pt(x + p.x, y + p.y); }
  pt operator-(const pt p) const { return pt(x - p.x, y - p.y); }
  pt operator*(const double c) const { return pt(x * c, y * c); }
  pt operator/(const double c) const { return pt(x / c, y / c); }
  double operator*(const pt p) const { return x * p.x + y * p.y; }
  double operator^(const pt p) const { return x * p.y - y * p.x; }
};
struct line
{
  pt p, q;
  line() {}
  line(pt p_, pt q_) : p(p_), q(q_) {}
};
double dist(pt p, pt q)
{
  return hypot(p.y - q.y, p.x - q.x);
}
double get_t(pt v, line r)
{
  return (r.p ^ r.q) / ((r.p - r.q) ^ v);
}
pt rotate90(pt p)
{
  return pt(-p.y, p.x);
}
pt inter(line r, line s)
{
  if (eq((r.p - r.q) ^ (s.p - s.q), 0))
    return pt(DINF, DINF);
  r.q = r.q - r.p, s.p = s.p - r.p, s.q = s.q - r.p;
  return r.q * get_t(r.q, s) + r.p;
}
pt getcenter(pt a, pt b, pt c)
{
  b = (a + b) / 2;
  c = (a + c) / 2;
  return inter(line(b, b + rotate90(a - b)),
               line(c, c + rotate90(a - c)));
}
vector<pt> circ_inter(pt a, pt b, double r, double R)
{
  vector<pt> ret;
  double d = dist(a, b);
  if (d > r + R or d + min(r, R) < max(r, R))
    return ret;
  double x = (d * d - R * R + r * r) / (2 * d);
  double y = sqrt(r * r - x * x);
  pt v = (b - a) / d;
  ret.push_back(a + v * x + rotate90(v) * y);
  if (y > 0)
    ret.push_back(a + v * x - rotate90(v) * y);
  return ret;
}
double angle(pt v)
{
  double ang = atan2(v.y, v.x);
  if (ang < 0)
    ang += 2 * PI;
  return ang;
}
struct circle
{
  pt c;
  double r;
};
signed main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  int n;
  cin >> n;
  vector<circle> v(n);
  double ans = 0;
  for (int i = 0; i < n; i++)
  {
    cin >> v[i].c.x >> v[i].c.y >> v[i].r;
    ans = max(ans, v[i].r);
  }
  vector<pt> dale;
  int tot = 0;
  for (int i = 0; i < n; i++)
  {
    for (int j = i + 1; j < n; j++)
    {
      bool valid = 0;
      for (auto const &x : circ_inter(v[i].c, v[j].c, v[i].r, v[j].r))
      {
        bool can = 1;
        for (int k = 0; k < n; k++)
        {
          if (i != k && j != k && gt(v[k].r, dist(x, v[k].c)))
          {
            can = 0;
            break;
          }
        }
        if (can)
        {
          dale.pb(x);
          valid = 1;
        }
      }
      if (valid)
      {
        tot++;
      }
    }
  }
  sort(dale.begin(), dale.end());
  dale.erase(unique(dale.begin(), dale.end()), dale.end());
  auto cmp = [&](pair<double, int> a, pair<double, int> b)
  {
    if (!eq(a.fir, b.fir))
      return gt(b.fir, a.fir);
    return a.sec < b.sec;
  };
  auto solve = [&](pt a, pt b, pt c) -> double
  {
    pt center = getcenter(a, b, c);
    double rad = max({dist(a, center), dist(b, center), dist(c, center)});
    vector<pair<double, int>> ev;
    for (int i = 0; i < n; i++)
    {
      vector<pt> inter = circ_inter(v[i].c, center, v[i].r, rad);
      if (inter.size() == 2)
      {
        double ang1 = angle(inter[0] - center);
        double ang2 = angle(inter[1] - center);
        if (gt(ang1, ang2))
          ang2 += 2 * PI;
        ev.pb({ang1, 0});
        ev.pb({ang2, 1});
      }
    }
    sort(ev.begin(), ev.end(), cmp);
    int delta = 0;
    double ini = 0.0;
    for (auto const &i : ev)
    {
      if (i.sec == 0)
      {
        delta++;
        if (delta == 1)
          ini = i.fir;
      }
      else
      {
        delta--;
      }
      double dist = i.fir - ini;
      if (!gt(2 * PI, dist))
        return rad;
    }
    return -1;
  };
  for (int i = 0; i < dale.size(); i++)
  {
    for (int j = i + 1; j < dale.size(); j++)
    {
      for (int k = j + 1; k < dale.size(); k++)
        ans = max(ans, solve(dale[i], dale[j], dale[k]));
    }
  }
  cout << fixed << setprecision(15) << ans << endl;
  return 0;
}