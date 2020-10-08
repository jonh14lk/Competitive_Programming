#include <bits/stdc++.h>
using namespace std;

#define PI acos(-1)
#define int long long int
#define pb push_back
#define pi pair<int, int>
#define fir first
#define sec second
#define MAXN 101
#define mod 1000000007

int a, b, c;
vector<int> kappa;
int dp[MAXN][MAXN][MAXN][15];
int v[3], f[3];

int solve(int i, int j, int k, int l)
{
  if (l == kappa.size() || (i == a && j == b && k == c))
    return dp[i][j][k][l] = (i == a && j == b && k == c) ? 1 : 0;
  if (dp[i][j][k][l] != -1)
    return dp[i][j][k][l];
  if (solve(i, j, k, l + 1))
    return dp[i][j][k][l] = 1;
  if (i + kappa[l] <= a && solve(i + kappa[l], j, k, l + 1))
    return dp[i][j][k][l] = 1;
  if (j + kappa[l] <= b && solve(i, j + kappa[l], k, l + 1))
    return dp[i][j][k][l] = 1;
  if (k + kappa[l] <= c && solve(i, j, k + kappa[l], l + 1))
    return dp[i][j][k][l] = 1;
  return dp[i][j][k][l] = 0;
}
signed main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  int q;
  cin >> q;
  while (q--)
  {
    cin >> a >> b >> c;
    kappa.clear();
    for (int i = 0; i < 3; i++)
    {
      cin >> f[i] >> v[i];
      for (int k = 0; k < f[i]; k++)
        kappa.pb(v[i]);
    }
    for (int i = 0; i <= a; i++)
      for (int j = 0; j <= b; j++)
        for (int k = 0; k <= c; k++)
          for (int l = 0; l <= kappa.size(); l++)
            dp[i][j][k][l] = -1;
    (solve(0, 0, 0, 0)) ? cout << "Yes\n" : cout << "No\n";
  }
}