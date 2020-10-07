#include <bits/stdc++.h>
using namespace std;

#define PI acos(-1)
#define int long long int
#define pb push_back
#define pi pair<int, int>
#define fir first
#define sec second
#define MAXN 100002
#define mod 1000000007

int dp[MAXN][52];
int t, n, m;

int solve(int i, int j)
{
  if (j == t)
    return dp[i][j] = 1;
  if (dp[i][j] != -1)
    return dp[i][j];
  int resp = 0;
  if (i - 1 >= n)
    resp = (resp + solve(i - 1, j + 1)) % mod;
  if (i + 1 <= m)
    resp = (resp + solve(i + 1, j + 1)) % mod;
  return dp[i][j] = resp;
}
signed main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  cin >> t >> n >> m;
  t--;
  memset(dp, -1, sizeof(dp));
  int ans = 0;
  for (int i = n; i <= m; i++)
    ans = (ans + solve(i, 0)) % mod;
  cout << ans << endl;
}
