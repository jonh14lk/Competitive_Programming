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
#define MAXN 3000001
#define mod 1000000007

double dp[MAXN];
double suf[MAXN];

signed main()
{
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  int n, l, r;
  cin >> n >> l >> r;
  for (int i = 0; i < MAXN; i++)
  {
    dp[i] = 1.0;
    suf[i] = 0.0;
  }
  for (int i = n - 1; i >= 0; i--)
  {
    int len = len = (r - l + 1);
    int len2 = (l == 0) ? len - 1 : len;
    double prob0 = (l == 0) ? (double)1 / len : 0;
    double probother = 1.0 - prob0;
    double ev = 1 / probother;
    double prob = (double)1 / len2;
    dp[i] = ev + ((suf[i + max(l, 1ll)] - suf[i + r + 1]) * prob);
    suf[i] = suf[i + 1] + dp[i];
  }
  cout << setprecision(15) << dp[0] << endl;
  return 0;
}
// pacotes no intervalo [l, r]