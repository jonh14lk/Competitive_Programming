#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace std;
using namespace __gnu_pbds;

template <class T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

#define int long long int
#define pb push_back
#define pi pair<int, int>
#define pii pair<int, pi>
#define fir first
#define sec second
#define MAXN 105
#define mod 1000000007

int n;
double dp[MAXN][MAXN][MAXN];

double solve(int i, int j, int k)
{
  if (!i && !j)
    return 0;
  if (dp[i][j][k] != -1)
    return dp[i][j][k];
  double ret = 0;
  if (i)
  {
    double prob = (double)i / (i + j);
    if (k)
      ret += (solve(i - 1, j, k - 1) * prob);
    else
      ret += ((i + solve(i - 1, j, k)) * prob);
  }
  if (j)
  {
    double prob = (double)j / (i + j);
    ret += (solve(i, j - 1, k + 1) * prob);
  }
  return dp[i][j][k] = ret;
}
signed main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  cin >> n;
  for (int i = 0; i <= n; i++)
    for (int j = 0; j <= n; j++)
      for (int k = 0; k <= n; k++)
        dp[i][j][k] = -1;
  cout << fixed << setprecision(6) << solve(n, n, 0) << endl;
  return 0;
}