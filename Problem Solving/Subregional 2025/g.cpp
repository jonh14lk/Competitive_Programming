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

int n;
vector<int> v, curr;
int dp[4098][1 << 7];

signed main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  cin >> n;
  v.resize(n);
  string s;
  cin >> s;
  bool all_zero = 1;
  for (int i = 0; i < n; i++)
  {
    v[i] = s[i] - '0';
    all_zero &= (v[i] == 0);
  }
  if (all_zero)
  {
    cout << "00000000 0" << endl;
    return 0;
  }
  pi ans = {1e9, 1e9};
  curr.resize(8);
  for (int x = 1; x < (1 << 8); x++)
  {
    for (int i = 0; i < 8; i++)
    {
      curr[7 - i] = (x & (1 << i)) ? 1 : 0;
    }
    for (int i = 0; i <= n; i++)
    {
      for (int mask = 0; mask < (1 << 7); mask++)
      {
        dp[i][mask] = 1e9;
      }
    }
    for (int mask = 0; mask < (1 << 7); mask++)
    {
      dp[0][mask] = __builtin_popcount(mask);
    }
    for (int i = 0; i < n; i++)
    {
      for (int mask = 0; mask < (1 << 7); mask++)
      {
        int val = 0;
        for (int b = 0; b < 7; b++)
        {
          if (mask & (1 << b))
          {
            val ^= curr[b + 1];
          }
        }
        int new_mask = mask;
        if (new_mask & (1 << 6))
        {
          new_mask ^= (1 << 6);
        }
        new_mask <<= 1;
        if (val == v[i])
        {
          dp[i + 1][new_mask] = min(dp[i + 1][new_mask], dp[i][mask]);
        }
        if ((val ^ curr[0]) == v[i])
        {
          new_mask ^= 1;
          dp[i + 1][new_mask] = min(dp[i + 1][new_mask], 1 + dp[i][mask]);
        }
      }
    }
    int ops = 1e9;
    for (int mask = 0; mask < (1 << 7); mask++)
    {
      ops = min(ops, dp[n][mask]);
    }
    ans = min(ans, pi(ops, x));
  }
  for (int i = 0; i < 8; i++)
  {
    curr[7 - i] = (ans.sec & (1 << i)) ? 1 : 0;
  }
  for (auto const &i : curr)
  {
    cout << i;
  }
  cout << " " << ans.fir << endl;
  return 0;
}