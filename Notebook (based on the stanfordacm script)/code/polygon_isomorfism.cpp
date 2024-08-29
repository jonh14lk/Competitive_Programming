#include <bits/stdc++.h>
using namespace std;

#define int long long int
#define pb push_back
#define pi pair<int, int>
#define pii pair<int, pi>
#define fir first
#define sec second
#define MAXN 4007
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
int max_suffix(vector<pair<long long, long double>> s, bool mi = false)
{
  s.push_back(*min_element(s.begin(), s.end()));
  s.back().first -= 1;
  s.back().second -= 1;
  int ans = 0;
  for (int i = 1; i < s.size(); i++)
  {
    int j = 0;
    while (ans + j < i and s[i + j] == s[ans + j])
      j++;
    if (s[i + j] > s[ans + j])
    {
      if (!mi or i != s.size() - 2)
        ans = i;
    }
    else if (j)
      i += j - 1;
  }
  return ans;
}
vector<pair<long long, long double>> max_cyclic_shift(vector<pair<long long, long double>> s)
{
  int n = s.size();
  for (int i = 0; i < n; i++)
    s.pb(s[i]);
  int id = max_suffix(s);
  vector<pair<long long, long double>> ans;
  for (int i = 0; i < n; i++)
  {
    ans.pb(s[id]);
    id = (id + 1) % n;
  }
  return ans;
}
int sqr(int x)
{
  return x * x;
}
int dd(pt a, pt b)
{
  return sqr(a.x - b.x) + sqr(a.y - b.y);
}
long long dot(pt a, pt b)
{
  return a.x * b.x + a.y * b.y;
}
vector<pair<long long, long double>> get_sides_and_dots(vector<pt> v)
{
  int n = (int)v.size();
  vector<pair<long long, long double>> ans;
  for (int i = 0; i < n; i++)
  {
    pt prv = v[i ? i - 1 : n - 1];
    pt nxt = v[i + 1 < n ? i + 1 : 0];
    long long dist = dd(v[i], v[(i + 1) % n]);
    long double angle = dot(prv - v[i], nxt - v[i]);
    ans.emplace_back(dist, angle);
  }
  return ans;
}
signed main()
{
  ios::sync_with_stdio(false);
  cin.tie(0);
  int n, m;
  cin >> n >> m;
  vector<pt> a(n);
  for (int i = 0; i < n; i++)
  {
    cin >> a[i].x >> a[i].y;
  }
  auto cha = convex_hull(a);
  auto distsA = get_sides_and_dots(cha);
  vector<pt> b(m);
  for (int i = 0; i < m; i++)
  {
    cin >> b[i].x >> b[i].y;
  }
  auto chb = convex_hull(b);
  auto distsB = get_sides_and_dots(chb);
  vector<pair<long long, long double>> aa = max_cyclic_shift(distsA);
  vector<pair<long long, long double>> bb = max_cyclic_shift(distsB);
  (aa == bb) ? cout << "YES\n" : cout << "NO\n";
  return 0;
}
// https://codeforces.com/problemset/problem/1017/E
// dados dois conjuntos de pontos
// achar o convex hull de cada conjunto
// e em seguida ver se os poligonos sao isomorfos

// podemos checar olhando para o comprimento de cada aresta e o dot product