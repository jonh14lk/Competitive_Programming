#include <bits/stdc++.h>
using namespace std;

#define PI acos(-1)
#define int long long int
#define pb push_back
#define pi pair<int, int>
#define fir first
#define sec second
#define MAXN 300001
#define mod 1000000007

signed main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  int n, h;
  cin >> n >> h;
  int val[n][h];
  int dp[n][h];
  for (int i = 0; i < n; i++)
    for (int j = 0; j < h; j++)
      cin >> val[i][j];
  int ans = 0;
  for (int j = 0; j < h; j++)
  {
    for (int i = 0; i < n; i++)
    {
      dp[i][j] = val[i][j];
      if (i - 1 >= 0 && j - 1 >= 0)
        dp[i][j] = max(dp[i][j], dp[i - 1][j - 1] + val[i][j]);
      if (i + 1 < n && j - 1 >= 0)
        dp[i][j] = max(dp[i][j], dp[i + 1][j - 1] + val[i][j]);
      if (j - 1 >= 0)
        dp[i][j] = max(dp[i][j], dp[i][j - 1] + val[i][j]);
      ans = max(ans, dp[i][j]);
    }
  }
  cout << ans << endl;
}