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
#define MAXN 100005
#define mod 1000000007

int n, k;
int a[101];
int dp[101][100005];
int sum[101][100005];

int solve(int i, int j);

void calc(int i)
{
  sum[i][0] = solve(i, 0);
  for (int j = 1; j <= k; j++)
    sum[i][j] = (sum[i][j - 1] + solve(i, j)) % mod;
}
int solve(int i, int j)
{
  if (i == n)
    return (j == 0) ? 1 : 0;
  if (dp[i][j] != -1)
    return dp[i][j];
  int ans = 0, limit = min(j, a[i]);
  if (sum[i + 1][j] == -1)
    calc(i + 1);
  ans = (ans + sum[i + 1][j]) % mod;
  if (j - limit - 1 >= 0)
    ans = (ans - sum[i + 1][j - limit - 1] + mod) % mod;
  return dp[i][j] = ans;
}
signed main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  cin >> n >> k;
  for (int i = 0; i < n; i++)
    cin >> a[i];
  memset(dp, -1, sizeof(dp));
  memset(sum, -1, sizeof(sum));
  cout << solve(0, k) << endl;
  return 0;
}
// uma dp que tem uma recorrencia do tipo:
// dp[i][j] = dp[i + 1][l] + dp[i + 1][l + 1] + ... + dp[i + 1][r]
// o jeito de fazer isso com soma de sufixo sem ter que codar a dp iterativa :)