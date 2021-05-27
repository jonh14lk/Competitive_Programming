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
#define pii pair<pi, pi>
#define fir first
#define sec second
#define MAXN 5005
#define mod 1000000007

int s, b;
int dp[MAXN][MAXN];

int solve(int i, int j)
{
  if (j <= 0 || i < 0)
    return 0;
  if (!i)
    return 1;
  if (j == 1)
    return 1;
  if (dp[i][j] != -1)
    return dp[i][j];
  int ret = 0;
  ret = (ret + solve(i - j, j)) % mod;
  ret = (ret + (2 * solve(i, j - 1))) % mod;
  ret = (ret - solve(i, j - 2) + mod) % mod;
  return dp[i][j] = ret;
}
signed main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  cin >> s >> b;
  memset(dp, -1, sizeof(dp));
  cout << solve(b - s, s) << endl;
  return 0;
}
// dp[s][b] = dp[s - b][b] + (2 * dp[s][b - 1]) - dp[s][b - 2]