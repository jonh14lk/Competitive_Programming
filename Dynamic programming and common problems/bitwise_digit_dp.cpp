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
#define MAXN 65
#define mod 1000000007
 
int a, b;
// current bit / i is bigger than l / i is lower than r / j is bigger than l / j is lower than r
int dp[MAXN][2][2][2][2];
 
int solve(int i, int j, int k, int l, int m)
{
  if (i < 0)
    return (j && k && l && m) ? 1 : 0;
  if (dp[i][j][k][l][m] != -1)
    return dp[i][j][k][l][m];
  int ret = 0;
  int ll = a & (1LL << i);
  int rr = b & (1LL << i);
  if ((j || !ll) && (l || !ll))
    ret += solve(i - 1, j, (rr) ? 1 : k, l, (rr) ? 1 : m);
  if ((k || rr) && (l || !ll))
    ret += solve(i - 1, (!ll) ? 1 : j, k, l, (rr) ? 1 : m);
  if ((m || rr) && (j || !ll))
    ret += solve(i - 1, j, (rr) ? 1 : k, (!ll) ? 1 : l, m);
  return dp[i][j][k][l][m] = ret;
}
signed main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  int q;
  cin >> q;
  while (q--)
  {
    cin >> a >> b;
    a--, b++;
    memset(dp, -1, sizeof(dp));
    if (a == -1)
      cout << solve(60, 1, 0, 1, 0) << endl;
    else
      cout << solve(60, 0, 0, 0, 0) << endl;
  }
  return 0;
}
// https://codeforces.com/contest/1245/problem/F
// https://codeforces.com/blog/entry/88064
// count the number of pairs (i, j) which (i & j) == 0
