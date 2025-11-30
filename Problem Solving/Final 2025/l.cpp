#include <bits/stdc++.h>
using namespace std;

#define int long long int
#define double long double
#define pb push_back
#define pi pair<int, int>
#define pii pair<pi, int>
#define fir first
#define sec second
#define MAXN 200005
#define mod 998244353

struct bit2d
{
  vector<int> ord;
  vector<vector<int>> t;
  vector<vector<int>> coord;

  bit2d(vector<pi> &pts)
  {
    sort(pts.begin(), pts.end());
    for (auto const &a : pts)
    {
      if (ord.empty() || a.fir != ord.back())
        ord.pb(a.fir);
    }
    t.resize(ord.size() + 1);
    coord.resize(t.size());
    for (auto &a : pts)
    {
      swap(a.fir, a.sec);
    }
    sort(pts.begin(), pts.end());
    for (auto &a : pts)
    {
      swap(a.fir, a.sec);
      for (int on = upper_bound(ord.begin(), ord.end(), a.fir) - ord.begin(); on < t.size(); on += on & -on)
      {
        if (coord[on].empty() || coord[on].back() != a.sec)
          coord[on].push_back(a.sec);
      }
    }
    for (int i = 0; i < t.size(); i++)
      t[i].assign(coord[i].size() + 1, 0);
  }
  void add(int x, int y, int v)
  {
    for (int xx = upper_bound(ord.begin(), ord.end(), x) - ord.begin(); xx < t.size(); xx += xx & -xx)
    {
      for (int yy = upper_bound(coord[xx].begin(), coord[xx].end(), y) - coord[xx].begin(); yy < t[xx].size(); yy += yy & -yy)
        t[xx][yy] += v;
    }
  }
  int qry(int x, int y)
  {
    int ans = 0;
    for (int xx = upper_bound(ord.begin(), ord.end(), x) - ord.begin(); xx > 0; xx -= xx & -xx)
    {
      for (int yy = upper_bound(coord[xx].begin(), coord[xx].end(), y) - coord[xx].begin(); yy > 0; yy -= yy & -yy)
        ans += t[xx][yy];
    }
    return ans;
  }
  int qry2(int x1, int y1, int x2, int y2)
  {
    if (x1 > x2 || y1 > y2)
      return 0;
    return qry(x2, y2) - qry(x2, y1 - 1) - qry(x1 - 1, y2) + qry(x1 - 1, y1 - 1);
  }
};

const double inf = 1e18;

pair<double, double> solve(int a, int b, int c)
{
  int delta = (b * b) - (4 * a * c);
  if (delta < 0)
    return {inf, inf};
  double s1 = (-b + sqrtl(delta)) / (2 * a);
  double s2 = (-b - sqrtl(delta)) / (2 * a);
  if (s1 > s2)
    swap(s1, s2);
  return {s1, s2};
}
signed main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  int n, a, b;
  cin >> n >> a >> b;
  vector<pair<double, double>> v;
  vector<double> pts;
  while (n--)
  {
    int m, c;
    cin >> m >> c;
    // ax^2 + b = mx + c
    // ax^2 -mx + b - c = 0
    pair<double, double> sol = solve(a, -m, b - c);
    if (sol.fir != inf)
    {
      v.pb(sol);
      pts.pb(sol.fir);
      pts.pb(sol.sec);
    }
  }
  sort(pts.begin(), pts.end());
  pts.erase(unique(pts.begin(), pts.end()), pts.end());
  n = v.size();
  vector<pi> compressed(n);
  vector<int> pref(pts.size(), 0);
  for (int i = 0; i < n; i++)
  {
    int l = lower_bound(pts.begin(), pts.end(), v[i].fir) - pts.begin();
    int r = lower_bound(pts.begin(), pts.end(), v[i].sec) - pts.begin();
    compressed[i] = {l, r};
    pref[l]++;
  }
  for (int i = 1; i < pts.size(); i++)
  {
    pref[i] += pref[i - 1];
  }
  bit2d bt(compressed);
  for (auto [x, y] : compressed)
  {
    bt.add(x, y, 1);
  }
  int ans = 0;
  auto intersection = [&](int l, int r)
  {
    l++;
    r--;
    if (l > r)
      return 0ll;
    int ans = pref[r];
    if (l > 0)
      ans -= pref[l - 1];
    return ans;
  };
  for (auto [x, y] : compressed)
  {
    ans += intersection(x, y);
    ans -= bt.qry2(x + 1, x + 1, y - 1, y);
  }
  cout << ans << endl;
  return 0;
}