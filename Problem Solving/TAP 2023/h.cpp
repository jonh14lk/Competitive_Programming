#include <bits/stdc++.h>
using namespace std;

#define int long long int
#define endl '\n'
#define pb push_back
#define pi pair<int, int>
#define pii pair<int, pi>
#define fir first
#define sec second
#define MAXN 1005
#define mod 998244353

int n;
int v[MAXN][MAXN];
pi pos[1000005];
int dp[MAXN][MAXN][2];
int dp_col[MAXN];
int dp_row[MAXN];

signed main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  cin >> n;
  for (int i = 0; i < n; i++)
  {
    for (int j = 0; j < n; j++)
    {
      cin >> v[i][j];
      pos[v[i][j]] = {i, j};
    }
  }
  for (int i = 0; i < n; i++)
  {
    dp_col[i] = -1e18;
    dp_row[i] = -1e18;
  }
  int sz = n * n;
  int ans = 0;
  for (int i = 1; i <= sz; i++)
  {
    int x = pos[i].fir;
    int y = pos[i].sec;
    for (int d = 0; d < 2; d++)
    {
      if (d == 0)
        dp[x][y][d] = max(0ll, dp_col[y]);
      else
        dp[x][y][d] = max(0ll, dp_row[x]);
      ans = max(ans, dp[x][y][d]);
    }
    for (int d = 0; d < 2; d++)
    {
      if (d == 0)
        dp_row[x] = max(dp_row[x], dp[x][y][d] + 1);
      else
        dp_col[y] = max(dp_col[y], dp[x][y][d] + 1);
    }
  }
  ans++;
  cout << ans << endl;
  return 0;
}