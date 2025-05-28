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
#define MAXN 1005
#define MAXK 8005

int n;
int v[MAXN];
int dp[MAXN][MAXK][4];

int solve(int i, int j, int k)
{
  if (k == 0)
    return (j == 0);
  if (j < 0 || i == n)
    return 0;
  if (dp[i][j][k] != -1)
    return dp[i][j][k];
  int ans = solve(i + 1, j, k);
  ans += solve(i + 1, j - v[i], k - 1);
  return dp[i][j][k] = ans;
}
signed main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  cin >> n;
  for (int i = 0; i < n; i++)
  {
    cin >> v[i];
    assert(v[i] <= 1000);
    v[i] += 1000;
    assert(v[i] >= 0);
  }
  memset(dp, -1, sizeof(dp));
  int q;
  cin >> q;
  while (q--)
  {
    int x;
    cin >> x;
    x += 4000;
    cout << solve(0, x, 4) << endl;
  }
  return 0;
}
