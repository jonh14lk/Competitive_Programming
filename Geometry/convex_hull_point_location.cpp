#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace std;
using namespace __gnu_pbds;

#define int long long int
#define endl '\n'
#define pb push_back
#define pi pair<int, int>
#define pii pair<int, pi>
#define fir first
#define sec second
#define MAXN 5005
#define mod 998244353

struct pt
{
  int x, y;
  pt operator+(pt p) { return {x + p.x, y + p.y}; }
  pt operator-(pt p) { return {x - p.x, y - p.y}; }
  bool operator==(pt p) { return (x == p.x && y == p.y); }
  int cross(pt p) { return x * p.y - y * p.x; }
  int cross(pt a, pt b) { return (a - *this).cross(b - *this); }
  int dot(pt p) { return x * p.x + y * p.y; }
};
bool cmp_x(pt a, pt b)
{
  if (a.x != b.x)
    return a.x < b.x;
  return a.y < b.y;
}
// acha o convex hull
vector<pt> convex_hull(vector<pt> pts)
{
  if (pts.size() <= 1)
    return pts;
  sort(pts.begin(), pts.end(), cmp_x);
  vector<pt> h(pts.size() + 1);
  int s = 0, t = 0;
  for (int it = 2; it--; s = --t, reverse(pts.begin(), pts.end()))
  {
    for (auto const &p : pts)
    {
      while (t >= s + 2 && h[t - 2].cross(h[t - 1], p) <= 0)
        t--;
      h[t++] = p;
    }
  }
  return {h.begin(), h.begin() + t - (t == 2 && h[0] == h[1])};
}
int sgn(int x)
{
  return (x > 0) - (x < 0);
}
int side_of(pt s, pt e, pt p)
{
  return sgn(s.cross(e, p));
}
bool on_segment(pt s, pt e, pt p)
{
  return p.cross(s, e) == 0 && (s - p).dot(e - p) <= 0;
}
// retorna se o ponto p está dentro ou não do convex hull l
// caso strict = true, então considera true se tiver na borda
// caso strict = false, então considera false se tiver na borda
bool is_hull(vector<pt> &l, pt p, bool strict = true)
{
  int a = 1, b = l.size() - 1, r = !strict;
  if (l.size() < 3)
    return r && on_segment(l[0], l.back(), p);
  if (side_of(l[0], l[a], l[b]) > 0)
    swap(a, b);
  if (side_of(l[0], l[a], p) >= r || side_of(l[0], l[b], p) <= -r)
    return false;
  while (abs(a - b) > 1)
  {
    int c = (a + b) / 2;
    (side_of(l[0], l[c], p) > 0 ? b : a) = c;
  }
  return sgn(l[a].cross(l[b], p)) < r;
}
signed main()
{
  int n;
  cin >> n;
  vector<pt> v(n);
  for (int i = 0; i < n; i++)
  {
    cin >> v[i].x >> v[i].y;
  }
  vector<pt> ans = convex_hull(v);
  for (int i = 0; i < n; i++)
  {
    if (!is_hull(ans, v[i]))
      cout << i + 1 << " ";
  }
  cout << endl;
}
// h da subregional - https://codeforces.com/gym/104555/problem/G