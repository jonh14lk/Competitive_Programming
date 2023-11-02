#include <bits/stdc++.h>
using namespace std;

#define int long long int
#define endl '\n'
#define pb push_back
#define pi pair<int, int>
#define pii pair<int, pi>
#define fir first
#define sec second
#define MAX 205
#define mod 998244353
#define PI acos(-1)
#define EPS 1e-9

struct pt
{
  double x, y;
  bool operator==(const pt &p) const
  {
    return abs(x - p.x) < EPS && abs(y - p.y) < EPS;
  }
  bool operator<(const pt &p) const
  {
    return x < p.x - EPS || (abs(x - p.x) < EPS && y < p.y - EPS);
  }
};
struct line
{
  double a, b, c;

  line() {}
  line(pt p, pt q)
  {
    a = p.y - q.y;
    b = q.x - p.x;
    c = -a * p.x - b * p.y;
    norm();
  }

  void norm()
  {
    double z = sqrt(a * a + b * b);
    if (abs(z) > EPS)
      a /= z, b /= z, c /= z;
  }

  double dist(pt p) const { return a * p.x + b * p.y + c; }
};

double det(double a, double b, double c, double d)
{
  return a * d - b * c;
}

inline bool betw(double l, double r, double x)
{
  return min(l, r) <= x + EPS && x <= max(l, r) + EPS;
}

inline bool intersect_1d(double a, double b, double c, double d)
{
  if (a > b)
    swap(a, b);
  if (c > d)
    swap(c, d);
  return max(a, c) <= min(b, d) + EPS;
}

bool intersect(pt a, pt b, pt c, pt d, pt &left, pt &right)
{
  if (!intersect_1d(a.x, b.x, c.x, d.x) || !intersect_1d(a.y, b.y, c.y, d.y))
    return false;
  line m(a, b);
  line n(c, d);
  double zn = det(m.a, m.b, n.a, n.b);
  if (abs(zn) < EPS)
  {
    if (abs(m.dist(c)) > EPS || abs(n.dist(a)) > EPS)
      return false;
    if (b < a)
      swap(a, b);
    if (d < c)
      swap(c, d);
    left = max(a, c);
    right = min(b, d);
    return true;
  }
  else
  {
    left.x = right.x = -det(m.c, m.b, n.c, n.b) / zn;
    left.y = right.y = -det(m.a, m.c, n.a, n.c) / zn;
    return betw(a.x, b.x, left.x) && betw(a.y, b.y, left.y) &&
           betw(c.x, d.x, left.x) && betw(c.y, d.y, left.y);
  }
}
pt rotate(pt p, double a)
{
  a = (a * PI) / 180;
  double xx = (cos(a) * p.x) + ((sin(a) * -1) * p.y);
  double yy = (sin(a) * p.x) + (cos(a) * p.y);
  pt ans = {xx, yy};
  return ans;
}
signed main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  int n;
  cin >> n;
  auto get_segs = [&](double x, double y, int dist)
  {
    vector<pair<pt, pt>> ans;
    pt a = rotate({x, y + dist}, 45);
    pt b = rotate({x + dist, y}, 45);
    pt c = rotate({x, y - dist}, 45);
    pt d = rotate({x - dist, y}, 45);
    ans.pb({a, b});
    ans.pb({b, c});
    ans.pb({c, d});
    ans.pb({d, a});
    return ans;
  };
  vector<pair<pt, pt>> segs;
  for (int i = 0; i < n; i++)
  {
    int x, y, d;
    cin >> x >> y >> d;
    vector<pair<pt, pt>> curr = get_segs(x, y, d);
    if (i == 0)
    {
      segs = curr;
      continue;
    }
    vector<pair<pt, pt>> inter;
    for (auto const &a : segs)
    {
      for (auto const &b : curr)
      {
        pt l, r;
        if (intersect(a.fir, a.sec, b.fir, b.sec, l, r))
          inter.pb({l, r});
      }
    }
    swap(inter, segs);
    sort(segs.begin(), segs.end());
    segs.erase(unique(segs.begin(), segs.end()), segs.end());
  }
  set<pt> ans;
  for (auto [a, b] : segs)
  {
    pt aa = rotate(a, 315);
    pt bb = rotate(b, 315);
    int xa = round(aa.x), ya = round(aa.y);
    int xb = round(bb.x), yb = round(bb.y);
    int dx = abs(xa - xb);
    int dy = abs(ya - yb);
    int sx = (xa < xb) ? 1 : -1;
    int sy = (ya < yb) ? 1 : -1;
    int x = xa, y = ya;
    int decision = dx - dy;
    while (x != xb || y != yb)
    {
      ans.insert({x, y});
      int decision2 = 2 * decision;
      if (decision2 > -dy)
      {
        decision -= dy;
        x += sx;
      }
      if (decision2 < dx)
      {
        decision += dx;
        y += sy;
      }
    }
    ans.insert({xb, yb});
  }
  for (auto const &i : ans)
    cout << i.x << " " << i.y << endl;
}