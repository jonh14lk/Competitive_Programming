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
#define MAXN 15
#define mod 1000000007

struct pt
{
  int x, y;
  bool operator<(pt ot)
  {
    if (x != ot.x)
      return x < ot.x;
    return y < ot.y;
  }
  void operator=(pt p) { x = p.x, y = p.y; }
  bool operator==(pt p) { return (x == p.x && y == p.y); }
  bool operator!=(pt p) { return (x != p.x || y != p.y); }
  pt operator+(const pt &p) { return {x + p.x, y + p.y}; }
  pt operator-(const pt &p) { return {x - p.x, y - p.y}; }
  pt operator*(int d) { return {x * d, y * d}; }
  pt operator/(int d) { return {x / d, y / d}; }
  int cross(pt ot) const { return x * ot.y - y * ot.x; }
  int cross(pt a, pt b) const { return (a - *this).cross(b - *this); }
};
enum type
{
  outside,
  inside,
  boundary
};
int cross(pt v, pt w)
{
  return v.x * w.y - v.y * w.x;
}
bool ccw(pt a, pt b, pt c)
{
  return cross(b - a, c - b) > 0;
}
void radial_sort(vector<pt> &a)
{
  pt pivot = *min_element(a.begin(), a.end());
  auto cmp = [&](pt p, pt q)
  {
    if (p == pivot || q == pivot)
      return q != pivot;
    return ccw(pivot, p, q) > 0;
  };
  sort(a.begin(), a.end(), cmp);
}
vector<pt> trata(vector<pt> p)
{
  vector<pt> ans;
  for (int i = 0; i < p.size(); i++)
  {
    while (ans.size() >= 2 && ans.back().cross(p[i], ans.end()[-2]) == 0)
      ans.pop_back();
    ans.pb(p[i]);
  }
  if (ans.size() > 2 && ans.back().cross(p[0], ans.end()[-2]) == 0)
    ans.pop_back();
  return ans;
}
void prepare(vector<pt> &p)
{
  radial_sort(p); // sort points in counter-clockwise order
  p = trata(p);   // and the polygon dont have 3 colinear points
}
int sgn(int val)
{
  if (val > 0)
    return 1;
  else if (val < 0)
    return -1;
  return 0;
}
bool in_seg(pt p, pt a, pt b)
{
  // check if point p is in the line segment formed by a and b
  if (a.cross(b, p) == 0)
    return (p.x >= min(a.x, b.x) && p.x <= max(a.x, b.x) && p.y >= min(a.y, b.y) && p.y <= max(a.y, b.y));
  return 0;
}
bool in_tri(pt p, pt a, pt b, pt c)
{
  // check if point p is in the triangle formed by a, b and c
  int a1 = abs(a.cross(b, c));
  int a2 = abs(p.cross(a, b)) + abs(p.cross(a, c)) + abs(p.cross(b, c));
  return a1 == a2;
}
int in_polygon(vector<pt> &poly, pt p)
{
  int n = poly.size();
  if (n == 1)
    return (p == poly[0]) ? type::boundary : type::outside;
  if (n == 2)
    return (in_seg(p, poly[0], poly[1])) ? type::boundary : type::outside;
  if (poly[0].cross(poly[1], p) != 0 && sgn(poly[0].cross(poly[1], p)) != sgn(poly[0].cross(poly[1], poly[n - 1])))
    return type::outside;
  if (poly[0].cross(p, poly[n - 1]) != 0 && sgn(poly[0].cross(p, poly[n - 1])) != sgn(poly[0].cross(poly[1], poly[n - 1])))
    return type::outside;
  int l = 2, r = n - 1;
  if (poly[0].cross(poly[l], p) > 0)
  {
    while (l < r)
    {
      int mid = (l + r) >> 1;
      (poly[0].cross(poly[mid], p) <= 0) ? r = mid : l = mid + 1;
    }
  }
  if (!in_tri(p, poly[0], poly[l - 1], poly[l]))
    return type::outside;
  if (in_seg(p, poly[l - 1], poly[l]))
    return type::boundary;
  if (in_seg(p, poly[0], poly[1]))
    return type::boundary;
  if (in_seg(p, poly[0], poly[n - 1]))
    return type::boundary;
  return type::inside;
}
vector<pt> minkowski(vector<pt> a, vector<pt> b)
{
  prepare(a);
  prepare(b);
  a.push_back(a[0]);
  a.push_back(a[1]);
  b.push_back(b[0]);
  b.push_back(b[1]);
  vector<pt> ans;
  int i = 0, j = 0;
  while (i < a.size() - 2 || j < b.size() - 2)
  {
    ans.pb(a[i] + b[j]);
    auto c = cross(a[i + 1] - a[i], b[j + 1] - b[j]);
    if (c >= 0)
      i++;
    if (c <= 0)
      j++;
  }
  return ans;
}
signed main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  vector<pt> v;
  for (int _ = 0; _ < 3; _++)
  {
    int n;
    cin >> n;
    vector<pt> p(n);
    for (int i = 0; i < n; i++)
      cin >> p[i].x >> p[i].y;
    if (_ == 0)
      v = p;
    else
      v = minkowski(v, p);
  }
  prepare(v);
  int q;
  cin >> q;
  while (q--)
  {
    pt p;
    cin >> p.x >> p.y;
    p.x *= 3, p.y *= 3;
    // ve se o ponto (3x, 3y) está na bora, dentro ou fora do poligono v
    (in_polygon(v, p) != type::outside) ? cout << "YES\n" : cout << "NO\n";
  }
  return 0;
}
// problema exemplo:
// https://codeforces.com/contest/87/problem/E
