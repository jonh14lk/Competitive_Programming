#include <bits/stdc++.h>
using namespace std;

#define int long long int
#define MAXN 100005
#define pi pair<int, int>
#define pii pair<pi, pi>
#define fir first
#define sec second
#define pb push_back

vector<int> dale = {-1, 1};

signed main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  int n, k;
  cin >> n >> k;
  int mxx = -1e18, mnx = 1e18, mny = 1e18, mxy = -1e18;
  vector<pi> v(n);
  if (n == 1)
  {
    cout << 1 << '\n';
    return 0;
  }
  for (int i = 0; i < n; i++)
  {
    int x, y;
    cin >> x >> y;
    v[i] = {x, y};
    mxx = max(mxx, x);
    mnx = min(mnx, x);
    mxy = max(mxy, y);
    mny = min(mny, y);
  }
  vector<int> a, b, c, d;
  for (auto [x, y] : v)
  {
    if (x == mxx)
      a.pb(y);
    if (x == mnx)
      b.pb(y);
    if (y == mxy)
      c.pb(x);
    if (y == mny)
      d.pb(x);
  }
  sort(a.begin(), a.end());
  sort(b.begin(), b.end());
  sort(c.begin(), c.end());
  sort(d.begin(), d.end());
  vector<pii> vecs;
  if (a.size() > 0)
  {
    vecs.pb({{mxx, a.front()}, {1, -1}});
    vecs.pb({{mxx, a.back()}, {1, 1}});
  }
  if (b.size() > 0)
  {
    vecs.pb({{mnx, b.front()}, {-1, -1}});
    vecs.pb({{mnx, b.back()}, {-1, 1}});
  }
  if (c.size() > 0)
  {
    vecs.pb({{c.front(), mxy}, {-1, 1}});
    vecs.pb({{c.back(), mxy}, {1, 1}});
  }
  if (d.size() > 0)
  {
    vecs.pb({{d.front(), mny}, {-1, -1}});
    vecs.pb({{d.back(), mny}, {1, -1}});
  }
  int ans = 1;
  for (int _a = 0; _a < vecs.size(); _a++)
  {
    for (int _b = _a + 1; _b < vecs.size(); _b++)
    {
      for (int i = 0; i <= k; i++)
      {
        auto s = vecs[_a];
        auto s2 = vecs[_b];
        int x1 = s.fir.fir + (s.sec.fir * i);
        int y1 = s.fir.sec + (s.sec.sec * i);
        int x2 = s2.fir.fir + (s2.sec.fir * (k - i));
        int y2 = s2.fir.sec + (s2.sec.sec * (k - i));

        int va = max({mxx, x1, x2});
        int vb = min({mnx, x1, x2});
        int vc = max({mxy, y1, y2});
        int vd = min({mny, y1, y2});

        ans = max(ans, (va - vb + 1) * (vc - vd + 1));
      }
    }
  }
  for (auto [x, y] : v)
  {
    for (auto const &dx : dale)
    {
      for (auto const &dy : dale)
      {
        int a = max(mxx, x + (dx * k));
        int b = min(mnx, x + (dx * k));
        int c = max(mxy, y + (dy * k));
        int d = min(mny, y + (dy * k));
        ans = max(ans, (a - b + 1) * (c - d + 1));
      }
    }
  }
  cout << ans << endl;
}