#include <bits/stdc++.h>
using namespace std;

#define int long long int
#define MAXN 100005
#define pi pair<int, int>
#define pii pair<pi, pi>
#define fir first
#define sec second
#define pb push_back
#define mod 998244353

int dp[2005][2005]; // (i, soma i * j)

signed main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  int n, k;
  cin >> n >> k;
  n = min(n, k);
  for (int i = 1; i <= k; i++)
  {
    dp[1][i] = 1;
  }
  for (int i = 1; i < k; i++)
  {
    for (int j = 1; j <= k; j++)
    {
      int sum = (j * i);
      int nxt = sum;
      int rem = nxt % (i + 1);
      if (rem > 0)
      {
        nxt -= rem;
        nxt += (i + 1);
      }
      while (1)
      {
        int diff = nxt - sum;
        if (diff > k)
          break;
        if (diff >= 1 && diff <= k)
        {
          dp[i + 1][nxt / (i + 1)] += dp[i][j];
          dp[i + 1][nxt / (i + 1)] %= mod;
        }
        nxt += (i + 1);
      }
    }
  }
  int ans = 0;
  for (int i = 0; i <= k; i++)
  {
    ans += dp[n][i];
    ans %= mod;
  }
  cout << ans << endl;
  return 0;
}