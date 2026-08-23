#include <bits/stdc++.h>
using namespace std;

#define int long long int
#define pb push_back
#define pi pair<int, int>
#define pii pair<int, pi>
#define fir first
#define sec second
#define MAXN 200005
#define mod 1000000007

double d[1005][1005];

signed main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  int n, h;
  cin >> n >> h;
  vector<int> x(n);
  vector<int> y(n);
  vector<int> r(n);
  for (int i = 0; i < n; i++)
  {
    cin >> x[i] >> y[i] >> r[i];
  }
  for (int i = 0; i < n; i++)
  {
    d[n][i] = d[i][n] = max(0ll, y[i] - r[i]);
    d[n + 1][i] = d[i][n + 1] = max(0ll, h - y[i] - r[i]);
    for (int j = i + 1; j < n; j++)
      d[i][j] = d[j][i] = max((long double)0, sqrtl((x[i] - x[j]) * (x[i] - x[j]) + (y[i] - y[j]) * (y[i] - y[j])) - (r[i] + r[j]));
  }
  d[n][n + 1] = d[n + 1][n] = h;
  vector<double> dist(n + 2, 1e18);
  vector<bool> vis(n + 2);
  dist[n] = 0;
  for (int it = 0; it < n + 2; it++)
  {
    int u = -1;
    for (int i = 0; i < n + 2; i++)
    {
      if (!vis[i] && (u == -1 || dist[i] < dist[u]))
        u = i;
    }
    vis[u] = 1;
    for (int v = 0; v < n + 2; v++)
    {
      if (u == v)
        continue;
      double nd = dist[u] + d[u][v];
      if (nd < dist[v])
        dist[v] = nd;
    }
  }
  cout << fixed << setprecision(15) << dist[n + 1] << endl;
  return 0;
}
