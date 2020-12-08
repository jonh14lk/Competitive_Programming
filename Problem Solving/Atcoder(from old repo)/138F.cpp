// https://atcoder.jp/contests/abc138/submissions/18635869
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
#define DEBUG 0
#define MAXN 65
#define mod 1000000007

// posicao / sou maior q o l / sou menor que o r / se o msb ja apareceu
int dp[MAXN][2][2][2];
int bl[MAXN];
int br[MAXN];

int sum(int a, int b)
{
  return (a + b) % mod;
}
int solve(int i, int j, int k, int first_bit)
{
  if (i == -1)
  {
    return (j && k && first_bit);
  }
  if (dp[i][j][k][first_bit] != -1)
  {
    return dp[i][j][k][first_bit];
  }
  int ans = 0;
  if (j || !bl[i])
  {
    int kk = (br[i]) ? 1 : k;
    ans = sum(ans, solve(i - 1, j, kk, first_bit));
  }
  if (k || br[i])
  {
    int jj = (!bl[i]) ? 1 : j;
    ans = sum(ans, solve(i - 1, jj, k, 1));
  }
  if (first_bit && (j || !bl[i]) && (k || br[i]))
  {
    ans = sum(ans, solve(i - 1, j, k, 1));
  }
  return dp[i][j][k][first_bit] = ans;
}
signed main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  int l, r;
  cin >> l >> r;
  l--, r++;
  for (int i = 0; l > 0; i++)
  {
    bl[i] = (l & 1);
    l = l >> 1;
  }
  for (int i = 0; r > 0; i++)
  {
    br[i] = (r & 1);
    r = r >> 1;
  }
  memset(dp, -1, sizeof(dp));
  cout << solve(63, 0, 0, 0) << endl;
  return 0;
}
// quantidade de pares (a, b)
// tal que:
// 1 - a >= b
// 2 - o bit mais a esquerda é igual em ambos
// 3 - para um bit ser = 1 em b, esse msm bit em a precisa ser = 1
