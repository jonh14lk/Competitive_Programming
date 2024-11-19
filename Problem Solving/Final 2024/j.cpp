#include <bits/stdc++.h>
using namespace std;

#define int long long int
#define pi pair<int, int>
#define fir first
#define sec second
#define pb push_back;
#define PI acos(-1)

signed main()
{
  ios::sync_with_stdio(false);
  cin.tie(NULL);
  int ang, n;
  cin >> ang >> n;
  double a = ang;
  double rad = (a * PI) / 180;
  double tg = tan(rad);
  vector<pi> v(n);
  for (int i = 0; i < n; i++)
    cin >> v[i].fir >> v[i].sec;
  sort(v.rbegin(), v.rend());
  double ans = 0.0;
  vector<pair<double, double>> vec(n);
  for (int i = 0; i < n; i++)
  {
    double x = (double)v[i].sec / tg;
    vec[i] = {v[i].fir, (double)v[i].fir + x};
  }
  sort(vec.begin(), vec.end());
  double ll, rr;
  for (int i = 0; i < n; i++)
  {
    if (i == 0)
    {
      ll = vec[i].fir;
      rr = vec[i].sec;
    }
    else
    {
      if (vec[i].fir > rr)
      {
        ans += (rr - ll);
        ll = vec[i].fir;
        rr = vec[i].sec;
      }
      else
      {
        ll = min(ll, vec[i].fir);
        rr = max(rr, vec[i].sec);
      }
    }
  }
  ans += (rr - ll);
  cout << fixed << setprecision(15) << ans << endl;
}