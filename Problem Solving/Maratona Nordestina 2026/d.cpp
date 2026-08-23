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

signed main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  int n, k, s;
  cin >> n >> k >> s;
  vector<vector<int>> b(n + 1, vector<int>(32));
  for (int i = 0; i <= 31; i++)
  {
    b[0][i] = (s & (1ll << i)) ? 1 : 0;
  }
  for (int i = 1; i <= n; i++)
  {
    for (int j = 0; j <= 31; j++)
    {
      if (j < k)
        b[i][j] = b[i - 1][j];
      else
        b[i][j] = b[i - 1][j] ^ b[i][j - k];
    }
  }
  int ans = 0;
  for (int i = 0; i <= 31; i++)
  {
    if (b[n][i])
      ans |= (1ll << i);
  }
  cout << ans << endl;
  return 0;
}