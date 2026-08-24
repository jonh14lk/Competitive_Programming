#include <bits/stdc++.h>
using namespace std;

#define int long long int
#define pb push_back
#define pi pair<int, int>
#define pii pair<int, pi>
#define fir first
#define sec second
#define MAXN 200005
#define mod 998244353

int n, p;
double dp[2027][2027];
bool vis[2027][2027];

double solve(int i, int j)
{
  if (i == j)
    return 0;
  if (vis[i][j])
    return dp[i][j];
  vis[i][j] = 1;
  double inc_j = (j == 2026) ? 0.0 : ((double)p / 100.0);
  double not_inc_j = 1.0 - inc_j;
  double w = not_inc_j * ((double)i / j);
  double x = inc_j * ((double)i / (j + 1));
  double y = not_inc_j * ((double)(j - i) / j);
  double z = inc_j * ((double)(j + 1 - i) / (j + 1));
  double ans = 1.0;
  ans += y * solve(i + 1, j);
  if (j < 2026)
  {
    ans += x * solve(i, j + 1);
    ans += z * solve(i + 1, j + 1);
  }
  return dp[i][j] = ans / (1 - w);
}
signed main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  cin >> n >> p;
  cout << fixed << setprecision(15) << solve(0, n) << endl;
  return 0;
}
