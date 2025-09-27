#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace std;
using namespace __gnu_pbds;

template <class T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

// #define int long long int
#define pb push_back
#define pi pair<int, int>
#define pii pair<pi, int>
#define fir first
#define sec second
#define MAXN 100005
#define mod 998244353

int mp[7][7];
pi d[22];
int dp[1 << 21][7];
int ans[1 << 21];

int solve(int mask, int last)
{
  if (mask == 0)
    return 1;
  if (dp[mask][last] != -1)
    return dp[mask][last];
  int ans = 0;
  for (int i = 0; i < 21; i++)
  {
    if (mask & (1 << i))
    {
      if (last == 0)
      {
        ans |= solve((mask ^ (1 << i)), d[i].sec);
        ans |= solve((mask ^ (1 << i)), d[i].fir);
      }
      else if (last == d[i].fir)
      {
        ans |= solve((mask ^ (1 << i)), d[i].sec);
      }
      else if (last == d[i].sec)
      {
        ans |= solve((mask ^ (1 << i)), d[i].fir);
      }
    }
  }
  return dp[mask][last] = ans;
}
signed main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  int id = 0;
  for (int i = 1; i <= 6; i++)
  {
    for (int j = i; j <= 6; j++)
    {
      mp[i][j] = id;
      d[id] = {i, j};
      id++;
    }
  }
  memset(dp, -1, sizeof(dp));
  for (int mask = 1; mask < (1 << 21); mask++)
  {
    ans[mask] = solve(mask, 0);
  }
  for (int i = 0; i < 21; i++)
  {
    for (int mask = 0; mask < (1 << 21); mask++)
    {
      if (mask & (1 << i))
        ans[mask] += ans[mask ^ (1 << i)];
    }
  }
  int q;
  cin >> q;
  while (q--)
  {
    int n;
    cin >> n;
    int mask = 0;
    while (n--)
    {
      int a, b;
      cin >> a >> b;
      mask |= (1ll << mp[a][b]);
    }
    cout << ans[mask] << endl;
  }
  return 0;
}