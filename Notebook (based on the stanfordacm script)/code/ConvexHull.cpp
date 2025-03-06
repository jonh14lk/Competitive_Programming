#include <bits/stdc++.h>

using namespace std;

#define int long long int
#define pb push_back
#define pi pair<int, int>
#define MAXN 100005

struct point
{
  int x, y, id;
  point(int x, int y, int id) : x(x), y(y), id(id) {}
  point() {}
  point operator-(point const &o) const { return {x - o.x, y - o.y, -1}; }
  bool operator<(point const &o) const
  {
    if (x == o.x)
      return y < o.y;
    return x < o.x;
  }
  int operator^(point const &o) const { return x * o.y - y * o.x; }
};
int ccw(point const &a, point const &b, point const &x)
{
  auto p = (b - a) ^ (x - a);
  return (p > 0) - (p < 0);
}
vector<point> convex_hull(vector<point> P) // sem colineares
{
  sort(P.begin(), P.end());
  vector<point> L, U;
  for (auto p : P)
  {
    while (L.size() >= 2 && ccw(L.end()[-2], L.end()[-1], p) == -1)
      L.pop_back();
    L.push_back(p);
  }
  reverse(P.begin(), P.end());
  for (auto p : P)
  {
    while (U.size() >= 2 && ccw(U.end()[-2], U.end()[-1], p) == -1)
      U.pop_back();
    U.push_back(p);
  }
  L.insert(L.end(), U.begin(), U.end() - 1);
  return L;
}
vector<point> convex_hull_no_collinears(vector<point> P) // com colineares
{
  sort(P.begin(), P.end());
  vector<point> L, U;
  for (auto p : P)
  {
    while (L.size() >= 2 && ccw(L.end()[-2], L.end()[-1], p) <= 0)
      L.pop_back();
    L.push_back(p);
  }
  reverse(P.begin(), P.end());
  for (auto p : P)
  {
    while (U.size() >= 2 && ccw(U.end()[-2], U.end()[-1], p) <= 0)
      U.pop_back();
    U.push_back(p);
  }
  L.insert(L.end(), U.begin(), U.end() - 1);
  return L;
}
signed main()
{
  // int n;
  // cin >> n;
  // vector<point> v(n);
  // for (int i = 0; i < n; i++)
  // {
  //   cin >> v[i].x >> v[i].y;
  //   v[i].id = i;
  // }
  // vector<point> ans = convex_hull(v);
  // vector<int> ids;
  // for (auto const &i : ans)
  // {
  //   ids.pb(i.id);
  // }
  // sort(ids.begin(), ids.end());
  // ids.erase(unique(ids.begin(), ids.end()), ids.end());
  // for (auto const &i : ids)
  //   cout << i + 1 << " ";
  // cout << endl;
  int n;
  while (cin >> n)
  {
    if (n == 0)
      break;
    vector<point> v(n);
    for (int i = 0; i < n; i++)
    {
      cin >> v[i].x >> v[i].y;
      v[i].id = i;
    }
    vector<point> ans = convex_hull_no_collinears(v);
    vector<pi> resp;
    for (auto const &i : ans)
    {
      if (!resp.size() || (pi(i.x, i.y) != resp.back()))
        resp.pb({i.x, i.y});
    }
    cout << resp.size() << endl;
    for (auto [x, y] : resp)
      cout << x << " " << y << endl;
  }
}
// https://codeforces.com/gym/104555/problem/G
// https://open.kattis.com/problems/convexhull (sem colinear)