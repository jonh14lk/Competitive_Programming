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
//#define pi pair<double, double>
#define double long double
#define pii pair<int, pi>
#define fir first
#define sec second
#define MAXN 500001
#define mod 1000000007

struct pt
{
  double x, y;
  pt operator+(pt p) { return {x + p.x, y + p.y}; } // soma de pontos
  pt operator-(pt p) { return {x - p.x, y - p.y}; } // subtração de pontos
  pt operator*(double d) { return {x * d, y * d}; } // multiplicação por um double
  pt operator/(double d) { return {x / d, y / d}; } // divisão por um double
};
struct circle
{
  pt c;
  double r;
};

bool inside(circle c, pt p)
{
  double dist = (c.c.x - p.x) * (c.c.x - p.x) + (c.c.y - p.y) * (c.c.y - p.y);
  return dist <= c.r;
}
circle get_circle(pt a, pt b)
{
  pt c = {(a.x + b.x) / 2.0, (a.y + b.y) / 2.0};
  double dist = sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
  dist /= 2.0;
  dist *= dist;
  return {c, dist};
}
pt get_center(pt b, pt c)
{
  double bb = b.x * b.x + b.y * b.y;
  double cc = c.x * c.x + c.y * c.y;
  double dd = b.x * c.y - b.y * c.x;
  return {(c.y * bb - b.y * cc) / (2 * dd), (b.x * cc - c.x * bb) / (2 * dd)};
}
circle get_circle(pt a, pt b, pt c)
{
  b = b - a;
  c = c - a;
  pt p = get_center(b, c);
  p = p + a;
  double dist = (a.x - p.x) * (a.x - p.x) + (a.y - p.y) * (a.y - p.y);
  return {p, dist};
}
circle solve2(vector<pt> &v)
{
  if (v.empty())
    return {{0, 0}, 0};
  if (v.size() == 1)
    return {v[0], 0};
  if (v.size() == 2)
    return get_circle(v[0], v[1]);
  for (int i = 0; i < 3; i++)
  {
    for (int j = i + 1; j < 3; j++)
    {
      circle c = get_circle(v[i], v[j]);
      bool ok = 1;
      for (auto const &k : v)
        ok &= inside(c, k);
      if (ok)
        return c;
    }
  }
  return get_circle(v[0], v[1], v[2]);
}
circle solve(vector<pt> &v, vector<pt> r, int n)
{
  if (n == 0 || r.size() == 3)
    return solve2(r);
  int idx = rand() % n;
  pt p = v[idx];
  swap(v[idx], v[n - 1]);
  circle c = solve(v, r, n - 1);
  if (inside(c, p))
    return c;
  r.pb(p);
  return solve(v, r, n - 1);
}
circle welzl(vector<pt> v)
{
  random_shuffle(v.begin(), v.end());
  return solve(v, {}, v.size());
}
signed main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  srand(time(NULL));
  int n;
  cin >> n;
  vector<pt> v(n);
  for (int i = 0; i < n; i++)
    cin >> v[i].x >> v[i].y;
  circle ans = welzl(v);
  cout << fixed << setprecision(3) << ans.c.x << " " << ans.c.y << endl;
  cout << fixed << setprecision(3) << sqrt(ans.r) << endl;
  return 0;
}
// acmicpc.net/problem/2626
// achar uma circuferencia
// minimizando o raio
// que cobre todos os pontos dela
// ai oq tem q printar eh o centro dessa circuferencia e o raio
// Minimum enclosing circle
// Welzl's algorithm
// complexidade O(n)