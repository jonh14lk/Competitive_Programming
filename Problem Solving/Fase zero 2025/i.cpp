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
#define MAXN 200005

const int inf = 1e18;

int n, t, l, r;
int c[10004][102];
int dp[102][10004];
pi best[102][102][3];

int solve(int i, int last)
{
  if (i == t)
    return 0;
  if (dp[i][last] != -1)
    return dp[i][last];
  int ans = -inf;
  for (int j = l; j <= r; j++)
  {
    int k = i + j - 1;
    if (k >= t)
      break;
    for (int op = 0; op < 3; op++)
    {
      if (best[i][k][op].sec != -1 && best[i][k][op].sec != last)
        ans = max(ans, best[i][k][op].fir + solve(k + 1, best[i][k][op].sec));
    }
  }
  return dp[i][last] = ans;
}
signed main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  cin >> n >> t;
  for (int i = 0; i < n; i++)
  {
    for (int j = 0; j < t; j++)
      cin >> c[i][j];
  }
  cin >> l >> r;
  for (int a = 0; a < t; a++)
  {
    vector<int> sum(n, 0);
    for (int b = a; b < t; b++)
    {
      for (int i = 0; i < n; i++)
      {
        sum[i] += c[i][b];
      }
      for (int j = 0; j < 3; j++)
      {
        best[a][b][j] = {-inf, -1};
      }
      for (int i = 0; i < n; i++)
      {
        for (int j = 0; j < 3; j++)
        {
          if (sum[i] > best[a][b][j].fir)
          {
            for (int k = 2; k > j; k--)
              best[a][b][k] = best[a][b][k - 1];
            best[a][b][j] = {sum[i], i};
            break;
          }
        }
      }
    }
  }
  memset(dp, -1, sizeof(dp));
  int ans = solve(0, n);
  if (ans < 0)
    cout << "-1\n";
  else
    cout << ans << endl;
  return 0;
}