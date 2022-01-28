#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace std;
using namespace __gnu_pbds;

template <class T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

#define int long long int
#define endl '\n'
#define pb push_back
#define pi pair<int, int>
#define pii pair<int, pi>
#define fir first
#define sec second
#define MAXN 200005
#define mod 1000000007

int s[8005];
int dp[3005][8005];

int cost(int l, int r)
{
  return (s[r + 1] - s[l]) * (r - l + 1);
}
void compute(int l, int r, int optl, int optr, int i)
{
  if (l > r)
    return;
  int mid = (l + r) >> 1;
  pair<int, int> ans = {1e18, -1}; // dp, k
  for (int q = optl; q <= min(mid, optr); q++)
  {
    if (q > 0)
      ans = min(ans, {dp[i - 1][q - 1] + cost(q, mid), q});
    else
      ans = min(ans, {cost(q, mid), q});
  }
  dp[i][mid] = ans.fir;
  compute(l, mid - 1, optl, ans.sec, i);
  compute(mid + 1, r, ans.sec, optr, i);
}
signed main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  int n, g;
  cin >> n >> g;
  for (int i = 1; i <= n; i++)
  {
    cin >> s[i];
    s[i] += s[i - 1];
  }
  for (int i = 0; i <= g; i++)
  {
    for (int j = 0; j <= n; j++)
      dp[i][j] = 1e18;
  }
  for (int i = 1; i <= g; i++)
    compute(0, n - 1, 0, n - 1, i);
  cout << dp[g][n - 1] << endl;
  return 0;
}
// https://codeforces.com/gym/103536/problem/A
// https://codeforces.com/contest/321/problem/E

// otimizacao de dp usando divide and conquer
// para dps do tipo:
// dp[i][j] = min(dp[i - 1][k] + c(k, j)), para algum k <= j
// considerando opt(i, j) o menor valor de k que minimiza dp[i][j]
// podemos calcular opt(i, j) usando divide and conquer
// isso diminuiria a complexidade para O(k * n * log(n))
