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
  double x, y;
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
struct building
{
  // 0 - circulo, 1 - quadrado, 2 - triangulo
  int type, r;
  vector<pt> v;
  building()
  {
    v.clear();
    r = 0;
    type = 0;
  }
  void find_vertices()
  {
    pt a, b;
    double vx = v[1].x - v[0].x;
    double vy = v[1].y - v[0].y;
    a.x = (v[0].x + v[1].x) / 2 + (-vy) / 2;
    a.y = (v[0].y + v[1].y) / 2 + (vx) / 2;
    b.x = (v[0].x + v[1].x) / 2 - (-vy) / 2;
    b.y = (v[0].y + v[1].y) / 2 - (vx) / 2;
    v.pb(a);
    swap(v[1], v[2]);
    v.pb(b);
  }
};

int c, q, t, n;
vector<building> v;
vector<int> vc, vq, vt;

double sarea(pt p, pt q, pt r)
{
  return ((q - p) ^ (r - q)) / 2;
}
double dist(pt p, pt q)
{
  return hypot(p.y - q.y, p.x - q.x);
}
double disttoline(pt p, line r)
{
  return 2 * abs(sarea(p, r.p, r.q)) / dist(r.p, r.q);
}
double disttoseg(pt p, line r)
{
  if ((r.q - r.p) * (p - r.p) < 0)
    return dist(r.p, p);
  if ((r.p - r.q) * (p - r.q) < 0)
    return dist(r.q, p);
  return disttoline(p, r);
}
double dist_circ_seg(pt p1, pt p2, pt p, int r)
{
  double dist = disttoseg(p, line(p2, p1));
  dist -= r;
  return dist;
}
double dist_seg_seg(line a, line b)
{
  double ret = DBL_MAX;
  ret = min(ret, disttoseg(a.p, b));
  ret = min(ret, disttoseg(a.q, b));
  ret = min(ret, disttoseg(b.p, a));
  ret = min(ret, disttoseg(b.q, a));
  return ret;
}
double dist_square_tri(int i, int j)
{
  double ans = DBL_MAX;
  for (int x = 0; x < 4; x++)
  {
    int y = (x + 1) % 4;
    for (int x2 = 0; x2 < 3; x2++)
    {
      int y2 = (x2 + 1) % 3;
      ans = min(ans, dist_seg_seg(line(v[i].v[x], v[i].v[y]), line(v[j].v[x2], v[j].v[y2])));
    }
  }
  return ans;
}
double dist_square_circ(int i, int j)
{
  double ans = DBL_MAX;
  for (int x = 0; x < 4; x++)
  {
    int y = (x + 1) % 4;
    ans = min(ans, dist_circ_seg(v[i].v[x], v[i].v[y], v[j].v[0], v[j].r));
  }
  return ans;
}
double dist_tri_circ(int i, int j)
{
  double ans = DBL_MAX;
  for (int x = 0; x < 3; x++)
  {
    int y = (x + 1) % 3;
    ans = min(ans, dist_circ_seg(v[i].v[x], v[i].v[y], v[j].v[0], v[j].r));
  }
  return ans;
}
double dist_circ_circ(int i, int j)
{
  double dist = (v[i].v[0].x - v[j].v[0].x) * (v[i].v[0].x - v[j].v[0].x);
  dist += (v[i].v[0].y - v[j].v[0].y) * (v[i].v[0].y - v[j].v[0].y);
  dist = sqrtl(dist);
  dist -= (v[i].r + v[j].r);
  return (dist < 0) ? 0 : dist;
}
signed main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  cin >> c >> q >> t;
  int n = c + q + t;
  int id = 0;
  for (int i = 0; i < c; i++)
  {
    int x, y, r;
    cin >> x >> y >> r;
    building b;
    b.v.pb({x, y});
    b.r = r;
    b.type = 0;
    v.pb(b);
    vc.pb(id);
    id++;
  }
  for (int i = 0; i < q; i++)
  {
    building b;
    b.type = 1;
    for (int j = 0; j < 2; j++)
    {
      int x, y;
      cin >> x >> y;
      b.v.pb({x, y});
    }
    b.find_vertices();
    v.pb(b);
    vq.pb(id);
    id++;
  }
  for (int i = 0; i < t; i++)
  {
    building b;
    b.type = 2;
    for (int j = 0; j < 3; j++)
    {
      int x, y;
      cin >> x >> y;
      b.v.pb({x, y});
    }
    v.pb(b);
    vt.pb(id);
    id++;
  }
  vector<vector<pair<double, int>>> adj(n + 2);
  double ans = DBL_MAX;
  for (auto const &i : vq)
  {
    for (auto const &j : vt)
    {
      ans = min(ans, dist_square_tri(i, j));
    }
  }
  for (auto const &i : vq)
  {
    for (auto const &j : vc)
    {
      double curr = dist_square_circ(i, j);
      adj[i].pb({curr, j});
      adj[j].pb({curr, i});
    }
  }
  for (auto const &i : vt)
  {
    for (auto const &j : vc)
    {
      double curr = dist_tri_circ(i, j);
      adj[i].pb({curr, j});
      adj[j].pb({curr, i});
    }
  }
  for (auto const &i : vc)
  {
    for (auto const &j : vc)
    {
      double curr = dist_circ_circ(i, j);
      adj[i].pb({curr, j});
      adj[j].pb({curr, i});
    }
  }
  int src = n, sink = n + 1;
  for (auto const &i : vt)
  {
    adj[src].pb({0, i});
  }
  for (auto const &i : vq)
  {
    adj[i].pb({0, sink});
  }
  vector<double> dist(n + 2, 1e18);
  vector<bool> vis(n + 2, 0);
  dist[src] = 0;
  priority_queue<pair<double, int>, vector<pair<double, int>>, greater<pair<double, int>>> pq;
  pq.push({dist[src], src});
  while (!pq.empty())
  {
    int x = pq.top().sec;
    pq.pop();
    if (vis[x])
      continue;
    vis[x] = 1;
    for (auto [d, y] : adj[x])
    {
      if (dist[y] > dist[x] + d)
      {
        dist[y] = dist[x] + d;
        pq.push({dist[y], y});
      }
    }
  }
  ans = min(ans, dist[sink]);
  cout << fixed << setprecision(15) << ans << endl;
  return 0;
}
// solution for: https://codeforces.com/gym/104603/problem/I