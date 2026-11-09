#include <bits/stdc++.h>
using namespace std;

#define int long long int
#define MAXN 6005
#define pi pair<int, int>
#define pb push_back
#define fir first
#define sec second
#define mod 998244353

int r, c, u, l;
int dp[MAXN][MAXN];
int dp2[MAXN][MAXN];

int modpow(int a, int b)
{
  int ans = 1;
  while (b)
  {
    if (b & 1)
      ans = (ans * a) % mod;
    a = (a * a) % mod;
    b >>= 1;
  }
  return ans;
}
int ncr(int n, int k)
{
  int num = 1, den = 1;
  for (int i = 1; i <= k; i++)
  {
    num = num * (n - i + 1) % mod;
    den = (den * i) % mod;
  }
  return num * modpow(den, mod - 2) % mod;
}
int solve(int i, int qt)
{
  if (i < 1 || i > r)
    return 0;
  if (qt == 0)
    return (i == r);
  if (dp[i][qt] != -1)
    return dp[i][qt];
  int ans = solve(i + 1, qt - 1);
  ans = (ans + solve(i - 1, qt - 1)) % mod;
  return dp[i][qt] = ans;
}
int solve2(int i, int qt)
{
  if (i < 1 || i > c)
    return 0;
  if (qt == 0)
    return (i == c);
  if (dp2[i][qt] != -1)
    return dp2[i][qt];
  int ans = solve2(i + 1, qt - 1);
  ans = (ans + solve2(i - 1, qt - 1)) % mod;
  return dp2[i][qt] = ans;
}
signed main()
{
  ios::sync_with_stdio(0);
  cin.tie(0);
  cin >> r >> c >> u >> l;
  u = r + (2 * u) - 1;
  l = c + (2 * l) - 1;
  memset(dp, -1, sizeof(dp));
  memset(dp2, -1, sizeof(dp2));
  int ans = solve(1, u);
  ans = (ans * solve2(1, l)) % mod;
  ans = (ans * ncr(u + l, l)) % mod;
  cout << ans << endl;
}
