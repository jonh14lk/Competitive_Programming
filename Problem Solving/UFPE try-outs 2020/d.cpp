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
#define eps 0.000000001
#define MAXN 100005
#define mod 1000000007

struct point
{
  double x, y, r;
};

int n, x, y;
vector<point> v;

double dist(double x1, double y1, double x2, double y2)
{
  return sqrt(((x2 - x1) * (x2 - x1)) + ((y2 - y1) * (y2 - y1)));
}
bool can(double r)
{
  for (int i = 0; i < n; i++)
  {
    double d = dist(v[i].x, v[i].y, x, y);
    d -= v[i].r;
    d = max(d, (double)0);
    if (d - r < eps)
      r += v[i].r;
    else
      return false;
  }
  return true;
}
bool cmp(point a, point b)
{
  double da = dist(a.x, a.y, x, y);
  da -= a.r;
  da = max(da, (double)0);
  double db = dist(b.x, b.y, x, y);
  db -= b.r;
  db = max(db, (double)0);
  return da < db;
}
signed main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  cin >> n >> x >> y;
  v.resize(n);
  for (int i = 0; i < n; i++)
    cin >> v[i].x >> v[i].y >> v[i].r;
  sort(v.begin(), v.end(), cmp);
  double l = 0, r = 3 * 1e9;
  for (int i = 0; i < 300; i++)
  {
    double mid = (l + r) / 2.0;
    (can(mid)) ? r = mid : l = mid;
  }
  cout << setprecision(15) << fixed << l << endl;
  return 0;
}