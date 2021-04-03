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
#define pii pair<pi, int>
#define fir first
#define sec second
#define MAXN 4005
#define mod 998244353

int n, k;
int v[MAXN][MAXN];
int pref[MAXN][MAXN];
int cost[MAXN][MAXN];
int dp[805][MAXN];

/* O(k * n^2) solution
int dp[MAXN][805];

int solve(int i, int j) 
{
  if (j == k)
    return (i == n) ? 0 : INT_MAX;
  if (i == n)
    return INT_MAX;
  if (dp[i][j] != -1)
    return dp[i][j];
  int ret = INT_MAX, sum = 0;
  for (int q = i; q < n; q++)
  {
    sum += pref[q][q + 1];
    sum -= pref[q][i];
    ret = min(ret, sum + solve(q + 1, j + 1));
  }
  return dp[i][j] = ret;
}*/

void compute(int l, int r, int optl, int optr, int i)
{
  if (l > r)
    return;
  int mid = (l + r) / 2;
  pi ans = {INT_MAX, -1}; // dp, k
  for (int q = optl; q <= min(mid, optr); q++)
  {
    if (q > 0)
      ans = min(ans, {dp[i - 1][q - 1] + cost[mid][q], q});
    else
      ans = min(ans, {cost[mid][q], q});
  }
  dp[i][mid] = ans.fir;
  compute(l, mid - 1, optl, ans.sec, i);
  compute(mid + 1, r, ans.sec, optr, i);
}
signed main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  cin >> n >> k;
  for (int i = 0; i < n; i++)
    for (int j = 0; j < n; j++)
      cin >> v[i][j];
  for (int i = 0; i < n; i++)
  {
    pref[i][0] = 0;
    for (int j = 1; j <= n; j++)
      pref[i][j] = pref[i][j - 1] + v[i][j - 1];
  }
  for (int i = 0; i <= k; i++)
    for (int j = 0; j <= n; j++)
      dp[i][j] = INT_MAX;
  for (int i = 0; i < n; i++)
    for (int j = 0; j < i; j++)
      cost[i][j] = cost[i - 1][j] + pref[i][i + 1] - pref[i][j];
  for (int i = 0; i < k; i++)
    compute(0, n - 1, 0, n - 1, i + 1);
  cout << dp[k][n - 1] << endl;
  return 0;
}
// https://codeforces.com/contest/321/problem/E

// ideias mais faceis:
// ou O(k * n^3) sem soma de prefixo
// O(k * n^2) usando uma soma de prefixo
// dp[i][j], mlhr q eu posso fazer sabendo que:
// ja aloquei os i primeiros e usei j gondolas
// dp[i][j] = min(dp[k][j - 1] + c(k, i)), para algum k < i

// otimizacao de dp usando divide and conquer
// para dps do tipo:
// dp[i][j] = min(dp[i - 1][k] + c(k, j)), para algum k <= j
// considerando opt(i, j) o menor valor de k que minimiza dp[i][j]
// podemos calcular opt(i, j) usando divide and conquer
// isso diminuiria a complexidade para O(k * n * log(n))
