#include <bits/stdc++.h>
using namespace std;

#define PI acos(-1)
#define pb push_back
#define int long long int
#define pi pair<int, int>
#define pii pair<pi, int>
#define fir first
#define sec second
#define MAXN 1001
#define mod 1000000007

signed main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  int n, m;
  cin >> n >> m;
  char v[n][m];
  int dp[n][m][2];
  for (int i = 0; i < n; i++)
    for (int j = 0; j < m; j++)
      cin >> v[i][j];
  int ans = 0;
  for (int i = 0; i < n; i++)
  {
    for (int j = 0; j < m; j++)
    {
      if (v[i][j] == 'G')
      {
        dp[i][j][0] = 1;
        dp[i][j][1] = 0;
      }
      else
      {
        dp[i][j][0] = 0;
        dp[i][j][1] = 1;
      }
      if (i && j && dp[i][j][0])
      {
        dp[i][j][0] = max(dp[i][j][0], min({dp[i][j - 1][0], dp[i - 1][j][0], dp[i - 1][j - 1][0]}) + 1);
        dp[i][j][0] = max(dp[i][j][0], min({dp[i][j - 1][0], dp[i - 1][j][1], dp[i - 1][j - 1][1]}) + 1);
      }
      else if (i && j && dp[i][j][1])
      {
        dp[i][j][1] = max(dp[i][j][1], min({dp[i][j - 1][1], dp[i - 1][j][1], dp[i - 1][j - 1][1]}) + 1);
        dp[i][j][1] = max(dp[i][j][1], min({dp[i][j - 1][1], dp[i - 1][j][0], dp[i - 1][j - 1][0]}) + 1);
      }
      ans = max(ans, dp[i][j][0]);
      ans = max(ans, dp[i][j][1]);
    }
  }
  cout << ans * ans << endl;
  return 0;
}
// cada linha pode ser a reversa ou nao
// qual o maior quadrado que pode ser formado
// todos os caras de cada linha devem ser iguais