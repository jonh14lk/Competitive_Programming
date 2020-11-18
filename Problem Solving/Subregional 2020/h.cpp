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
#define DEBUG 0
#define MAXN 52
#define mod 1000000007

int n, f;
vector<int> v;
int dp[MAXN][MAXN];

int comb(int i, int j, int c, int k)
{
  if (i == c)
    return dp[i][j] = (j == k) ? 1 : 0;
  if (dp[i][j] != -1)
    return dp[i][j];
  int ret = 0;
  ret += comb(i + 1, j + 1, c, k);
  ret += comb(i + 1, j, c, k);
  return dp[i][j] = ret;
}
int solve(int i, int j, int k, int rem, int r)
{
  if (i == n || !k)
    return (j <= r && !k) ? 1 : 0;
  int ans = 0;
  if (j + v[i] > r)
  {
    ans += solve(i + 1, j, k, rem - 1, r);
  }
  else
  {
    ans += solve(i + 1, j + v[i], k - 1, rem - 1, r);
    memset(dp, -1, sizeof(dp));
    ans += comb(0, 0, rem, k);
  }
  return ans;
}
signed main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  cin >> n >> f;
  v.resize(n);
  for (int i = 0; i < n; i++)
    cin >> v[i];
  sort(v.rbegin(), v.rend());
  int l, r;
  cin >> l >> r;
  cout << solve(0, 0, f, n - 1, r) - solve(0, 0, f, n - 1, l - 1) << endl;
  return 0;
}
// v[i] * 2 <= v[i + 1]
// podemos descrever o problema como:
// ans = sum[b] - sum[a - 1]
// 1 caso: v[i] > r, apenas ignore
// 2 caso:
// se eu ponho, subtraio o peso do que eu botei
// se eu não ponho, posso adicionar comb(rem, k) a resposta
// pois a soma dos pesos restantes eh menor doq eu ja tenho
// no final fica o(n)