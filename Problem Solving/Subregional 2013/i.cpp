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
#define mod 1000000007

int n, c, t1, t2;
vector<int> v;
int dp[MAXN];

int solve(int i)
{
  if (i == n)
    return 0;
  if (dp[i] != -1)
    return dp[i];
  int ret = 1e18;
  {
    int j = i + 1;
    while (j < n && v[j] - v[i] <= t1)
      j++;
    ret = min(ret, t1 + solve(j));
  }
  {
    int j = i + 1;
    while (j < n && v[j] - v[i] <= t2)
      j++;
    ret = min(ret, t2 + solve(j));
  }
  return dp[i] = ret;
}
signed main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  cin >> n >> c >> t1 >> t2;
  v.resize(n);
  for (int i = 0; i < n; i++)
    cin >> v[i];
  sort(v.begin(), v.end());
  memset(dp, -1, sizeof(dp));
  cout << solve(0) << endl;
  return 0;
}