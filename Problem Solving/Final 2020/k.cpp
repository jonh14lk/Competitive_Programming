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
#define MAXN 751
#define mod 1000000007

int k, l, n;
int v[10001];
int dp[MAXN][10001];
int suf[MAXN][10001];
vector<int> t[MAXN];

signed main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  cin >> k >> l;
  for (int i = 0; i < k; i++)
  {
    t[i].resize(k);
    for (int j = 0; j < k; j++)
      cin >> t[i][j];
  }
  cin >> n;
  n--;
  for (int i = 0; i < n; i++)
    cin >> v[i];
  for (int i = 0; i < k; i++)
    dp[i][n] = 1;
  int sum = 0;
  for (int i = 0; i < k; i++)
    sum = (sum + dp[i][n]) % mod, suf[i][n] = sum;
  for (int j = n - 1; j >= 0; j--)
  {
    for (int i = 0; i < k; i++)
    {
      int lo = lower_bound(t[i].begin(), t[i].end(), v[j] - l) - t[i].begin();
      int hi = lower_bound(t[i].begin(), t[i].end(), v[j] + l + 1) - t[i].begin();
      if (hi)
        dp[i][j] = (dp[i][j] + suf[hi - 1][j + 1]) % mod;
      if (lo)
        dp[i][j] = (dp[i][j] - suf[lo - 1][j + 1] + mod) % mod;
    }
    sum = 0;
    for (int i = 0; i < k; i++)
      sum = (sum + dp[i][j]) % mod, suf[i][j] = sum;
  }
  int ans = 0;
  for (int i = 0; i < k; i++)
    ans = (ans + dp[i][0]) % mod;
  cout << ans << endl;
  return 0;
}